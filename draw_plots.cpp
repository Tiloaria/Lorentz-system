#ifndef DRAW_PLOTS
#define DRAW_PLOTS

#include "plots.cpp"
#include "plots_3d.cpp"
#include "data_stuctures.h"
#include <functional>
#include <algorithm>
#include <vector>
#include <string>

Point get_mianx_component(Point const & a, Point const & b, std::function <long double (long double, long double)> f)
{
    return 
    {
        f(a.x, b.x),
        f(a.y, b.y),
        f(a.z, b.z),
        f(a.t, b.t)
    };
}

Point get_min_component(Point const & a, Point const & b)
{
    return get_mianx_component(a, b, [] (long double a, long double b) -> long double {return std::min(a, b);});
}

Point get_max_component(Point const & a, Point const & b)
{
    return get_mianx_component(a, b, [] (long double a, long double b) -> long double {return std::max(a, b);});
}

std::pair <Point, Point> get_min_max(std::vector <Point> const & values)
{
    Point min_value = values[0], max_value = values[0];
    
    for (Point const & a : values)
    {
        min_value = get_min_component(min_value, a);
        max_value = get_max_component(max_value, a);
    }

    return {min_value, max_value};
}

struct draw
{
    draw
    (
        std::vector <std::string> const & _names = {"x(t)", "y(t)", "z(t)", "xyz"},
        std::pair <double, double> _rotate = {120, 60},
        Point const & _min_value = {0., 0., 0., 0.},
        Point const & _max_value = {0., 0., 0., 0.},
        bool _draw_legend = 1,
        double _legend_x = -0.5,
        double _legend_y = 1.6
    ) :
        min_value(_min_value),
        max_value(_max_value),
        valuess(),
        names(_names),
        rotate(_rotate),
        draw_legend(_draw_legend),
        legend_x(_legend_x),
        legend_y(_legend_y)
    {}
    
    draw & add
    (
        std::vector <Point> const & values,
        std::string legend = ""
    )
    {   
        valuess.push_back(values);
        legends.push_back(legend);
        return *this;
    }
    
    ~draw ()
    {
        min_value = valuess[0][0];
        max_value = valuess[0][0];
        for (auto const & a : valuess)
        {
            std::pair <Point, Point> cur_min_max = get_min_max(a);
            min_value = get_min_component(min_value, cur_min_max.first);
            max_value = get_max_component(max_value, cur_min_max.second);
        }

        make_plot plot_xt(names[0], {min_value.t, max_value.t}, {min_value.x, max_value.x}, "t", "x", draw_legend, legend_x, legend_y);
        make_plot plot_yt(names[1], {min_value.t, max_value.t}, {min_value.y, max_value.y}, "t", "y", draw_legend, legend_x, legend_y);
        make_plot plot_zt(names[2], {min_value.t, max_value.t}, {min_value.z, max_value.z}, "t", "z", draw_legend, legend_x, legend_y);
        make_plot_3d plot_xyz(names[3], {{min_value.x, max_value.x}, {min_value.y, max_value.y}, {min_value.z, max_value.z}}, rotate, {"X", "Y", "Z"}, draw_legend, legend_x, legend_y);

        for (size_t i = 0; i != valuess.size(); ++i)
        {
            std::vector <Point> const & values = valuess[i];
            std::vector <double> x;
            std::vector <double> y;
            std::vector <double> z;
            std::vector <double> t;
            
            for (Point const & a : values)
            {
                x.push_back(a.x);
                y.push_back(a.y);
                z.push_back(a.z);
                t.push_back(a.t);
            }

            plot_xt.add(t, x, plots_color[i % plots_color.size()], legends[i]);
            plot_yt.add(t, y, plots_color[i % plots_color.size()], legends[i]);
            plot_zt.add(t, z, plots_color[i % plots_color.size()], legends[i]);
            plot_xyz.add(x, y, z, plots_color[i % plots_color.size()], legends[i]);
        }
    }
    
private:
    Point min_value;
    Point max_value;
    std::vector <std::vector <Point> > valuess;
    std::vector <std::string> legends;
    std::vector <std::string> names = {"x(t)", "y(t)", "z(t)", "xyz"};
    std::pair <double, double> rotate = {120, 60};
    static std::vector <std::string> plots_color;
    bool draw_legend;
    double legend_x;
    double legend_y;
};

std::vector <std::string> draw::plots_color = {"b", "g", "r", "E", "c", "m", "q", "p", "k"};

#endif

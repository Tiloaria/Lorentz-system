#ifndef PLOTS_3D
#define PLOTS_3D

#include <mgl2/mgl.h>
#include <iostream>
#include <algorithm>

template <typename T>
struct thrid
{
    thrid (T _x = 0, T _y = 0, T _z = 0) :
        x(_x),
        y(_y),
        z(_z)
    {}
    
    T x, y, z;
};

struct make_plot_3d
{
    make_plot_3d
    (
        std::string _name, 
        thrid <std::pair <double, double> > range, 
        std::pair <double, double> rotate = {50, 60},
        thrid <std::string> _axis = {"X", "Y", "Z"},
        bool _has_legend = 1,
        double _legend_x = 1.0,
        double _legend_y = 0.5,
        size_t size_picture_x = 1920,
        size_t size_picture_y = 1080
    ) :
        gr(),
        name(_name),
        axis(_axis),
        has_legend(_has_legend),
        legend_x(_legend_x),
        legend_y(_legend_y)
    {
        gr.SetSize(size_picture_x, size_picture_y);
        gr.SetFontSize(3.0);
        gr.Title(name.c_str());
        gr.SetFontSize(2.0);

        gr.SetRange('x', range.x.first, range.x.second);
        gr.SetRange('y', range.y.first, range.y.second);
        gr.SetRange('z', range.z.first, range.z.second);
        
        gr.Rotate(rotate.first, rotate.second);
        gr.Box();

        gr.Adjust();
        gr.Axis("xyz6f");

    }
     
    void add
    (
        std::vector <thrid <double> > const & values,
        std::string const & plot_color = "b",
        std::string const & legend_f_name = ""
    )
    {
        if (legend_f_name != "")
        {
            legend.push_back({plot_color, legend_f_name});
        }
        plot_from_dots(values, plot_color);
    }
     
    void add
    (
        std::vector <double> const & x,
        std::vector <double> const & y,
        std::vector <double> const & z,
        std::string const & plot_color = "b",
        std::string const & legend_f_name = ""
    )
    {
        if (legend_f_name != "")
        {
            legend.push_back({plot_color, legend_f_name});
        }
        plot_from_dots(x, y, z, plot_color);
    }
    
    ~make_plot_3d ()
    {
        gr.SetFunc("", "");
        gr.SetFontSize(4.0);

        if (has_legend)
        {
            for (size_t i = 0; i != legend.size(); ++i)
            {
                gr.AddLegend(legend[i].second.c_str(), legend[i].first.c_str());
            }
            gr.Legend(legend_x, legend_y);
        }
      
        gr.Label('x', axis.x.c_str());
        gr.Label('y', axis.y.c_str());
        gr.Label('z', axis.z.c_str());

        gr.WriteFrame((name + ".png").c_str());
    }

    void plot_from_dots
    (
        std::vector <thrid <double> > const & values,
        std::string color = "r"
    )
    {
        mglData points_a(values.size()), points_b(values.size()), points_c(values.size());
        for (size_t i = 0; i != values.size(); ++i)
        {
            points_a.a[i] = values[i].x;
            points_b.a[i] = values[i].y;
            points_c.a[i] = values[i].z;
        }
        gr.Plot(points_a, points_b, points_c, color.c_str());
        gr.Dots(points_a, points_b, points_c, color.c_str());
    }

    void plot_from_dots
    (
        std::vector <double> const & a,
        std::vector <double> const & b,
        std::vector <double> const & c,
        std::string color = "r"
    )
    {
        mglData points_a(a.size()), points_b(a.size()), points_c(a.size());
        for (size_t i = 0; i != a.size(); ++i)
        {
            points_a.a[i] = a[i];
            points_b.a[i] = b[i];
            points_c.a[i] = c[i];
        }
        gr.Plot(points_a, points_b, points_c, color.c_str());
        gr.Dots(points_a, points_b, points_c, color.c_str());
    }

private:
    mglGraph gr;
    std::string name;
    static std::vector <std::string> plots_color;
    thrid <std::string> axis;
    bool has_legend = 1;
    double legend_x = 1.0;
    double legend_y = 0.5;
    std::vector <std::pair <std::string, std::string> > legend; //color name
};

std::vector <std::string> make_plot_3d::plots_color = {"b", "g", "r", "E", "c", "m", "q", "p", "k"};

#endif

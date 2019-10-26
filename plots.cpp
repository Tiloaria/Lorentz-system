#ifndef PLOTS
#define PLOTS

#include <mgl2/mgl.h>
#include <iostream>
#include <algorithm>

struct make_plot
{
    make_plot
    (
        std::string _name, 
        std::pair <double, double> range_x, 
        std::pair <double, double> range_y,
        std::string _axis_x = "X",
        std::string _axis_y = "Y",
        bool _has_legend = 1,
        double _legend_x = 1.0,
        double _legend_y = 0.5,
        size_t size_picture_x = 1920,
        size_t size_picture_y = 1080
    ) :
        gr(),
        name(_name),
        axis_x(_axis_x),
        axis_y(_axis_y),
        has_legend(_has_legend),
        legend_x(_legend_x),
        legend_y(_legend_y)
    {
        gr.SetSize(size_picture_x, size_picture_y);
        gr.SetFontSize(3.0);
        gr.Title(name.c_str());
        gr.SetFontSize(2.0);

        gr.SetRange('x', range_x.first, range_x.second);
        gr.SetRange('y', range_y.first, range_y.second);
        
        gr.Adjust();
        gr.Axis("xy6f");

    }
     
    void add
    (
        std::vector <std::pair <double, double> > const & values,
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
        std::string const & plot_color = "b",
        std::string const & legend_f_name = ""
    )
    {
        if (legend_f_name != "")
        {
            legend.push_back({plot_color, legend_f_name});
        }
        plot_from_dots(x, y, plot_color);
    }
    
    void add
    (
        std::vector <double> const & x,
        std::vector <std::vector <double> > const & y,
        std::vector <std::string> const & plot_color = plots_color,
        std::vector <std::string> const & legend_f_name = {}
    )
    {   
        for (size_t i = 0; i != y.size(); ++i)
        {
            std::string cur_color = (i < plot_color.size())? plot_color[i] : "b";
            if (i < legend_f_name.size())
            {
                legend.push_back({cur_color, legend_f_name[i]});
            }
        }
        plot_from_dots(x, y, plots_color);
    }
     
    ~make_plot ()
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
      
        gr.Label('x', axis_x.c_str());
        gr.Label('y', axis_y.c_str());

        gr.WriteFrame((name + ".png").c_str());
    }

    void plot_from_dots
    (
        std::vector <std::pair <double, double> > const & values,
        std::string color = "r"
    )
    {
        mglData points_a(values.size()), points_b(values.size()), points_c(values.size());
        for (size_t i = 0; i != values.size(); ++i)
        {
            points_a.a[i] = values[i].first;
            points_b.a[i] = values[i].second;
        }
        gr.Plot(points_a, points_b, points_c, color.c_str());
        gr.Dots(points_a, points_b, points_c, color.c_str());
    }

    void plot_from_dots
    (
        std::vector <double> const & a,
        std::vector <double> const & b,
        std::string color = "r"
    )
    {
        mglData points_a(a.size()), points_b(a.size()), points_c(a.size());
        for (size_t i = 0; i != a.size(); ++i)
        {
            points_a.a[i] = a[i];
            points_b.a[i] = b[i];
        }
        gr.Plot(points_a, points_b, points_c, color.c_str());
        gr.Dots(points_a, points_b, points_c, color.c_str());
    }

    void plot_from_dots 
    (
        std::vector <std::vector <std::pair <double, double> > > const & values,
        std::vector <std::string> color = {}
    )
    {
        if (color.size() < values.size())
        {
            color.resize(values.size(), "r");
        }

        for (size_t j = 0; j != values.size(); ++j)
        {
            mglData points_a(values[j].size()), points_b(values[j].size()), points_c(values[j].size());
            for (size_t i = 0; i != values[j].size(); ++i)
            {
                points_a.a[i] = values[j][i].first;
                points_b.a[i] = values[j][i].second;
            }
            gr.Plot(points_a, points_b, points_c, color[j].c_str());
            gr.Dots(points_a, points_b, points_c, color[j].c_str());
        }
    }

    void plot_from_dots 
    (
        std::vector <double> const & a,
        std::vector <std::vector <double> > const & b,
        std::vector <std::string> color = {}
    )
    {
        if (color.size() < b.size())
        {
            color.resize(b.size(), "r");
        }

        for (size_t j = 0; j != b.size(); ++j)
        {
            mglData points_a(b[j].size()), points_b(b[j].size()), points_c(b[j].size());
            for (size_t i = 0; i != b[j].size(); ++i)
            {
                points_a.a[i] = a[i];
                points_b.a[i] = b[j][i];
            }
            gr.Plot(points_a, points_b, points_c, color[j].c_str());
            gr.Dots(points_a, points_b, points_c, color[j].c_str());
        }
    }

    void plot_from_dots 
    (
        std::vector <std::vector <double> > const & a,
        std::vector <std::vector <double> > const & b,
        std::vector <std::string> color = {}
    )
    {
        if (color.size() < a.size())
        {
            color.resize(a.size(), "r");
        }

        for (size_t j = 0; j != a.size(); ++j)
        {
            mglData points_a(a[j].size()), points_b(a[j].size()), points_c(a[j].size());
            for (size_t i = 0; i != a[j].size(); ++i)
            {
                points_a.a[i] = a[j][i];
                points_b.a[i] = b[j][i];
            }
            gr.Plot(points_a, points_b, points_c, color[j].c_str());
            gr.Dots(points_a, points_b, points_c, color[j].c_str());
        }
    }

private:
    mglGraph gr;
    std::string name;
    static std::vector <std::string> plots_color;
    std::string axis_x;
    std::string axis_y;
    bool has_legend = 1;
    double legend_x = 1.0;
    double legend_y = 0.5;
    std::vector <std::pair <std::string, std::string> > legend; //color name
};

std::vector <std::string> make_plot::plots_color = {"b", "g", "r", "E", "c", "m", "q", "p", "k"};

#endif

#include "methods.h"
#include "draw_plots.cpp"

int main ()
{
    const long double delta = 10,
    b = 10.0 / 3,
    r = 20,
    delta_t = 0.01,
    x0 = 10,
    y0 = 12,
    z0 = r + 5,
    t0 = 0,
    max_t = 2;

    draw all_plots;
    
    all_plots.add
    (
        explicit_method_euler
        (
            r, 
            b,
            delta, 
            delta_t,      
            x0,
            y0,
            z0,
            t0,
            max_t
        ),
        "explicit\\_method\\_euler"
    );

    all_plots.add
    (
        implicit_method_euler
        (
            r, 
            b,
            delta, 
            delta_t,      
            x0,
            y0,
            z0,
            t0,
            max_t
        ),
        "implicit\\_method\\_euler"
    );
    
    all_plots.add
    (
        runge_kutta
        (
            r, 
            b,
            delta, 
            delta_t,      
            x0,
            y0,
            z0,
            t0,
            max_t
        ),
        "runge\\_kutta"
    );
    
    all_plots.add
    (
        adams_4
        (
            r, 
            b,
            delta, 
            delta_t,      
            x0,
            y0,
            z0,
            t0,
            max_t
        ),
        "adams"
    );
}

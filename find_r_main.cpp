#include "find_r.cpp"
#include "methods.h"


int main (int argc, char ** argv)
{
    //double r = 20.;
    double b = 10. / 3.;
    double delta = 10.;
    double delta_t = 0.001;
    double x0 = 10.;
    double y0 = 120.;
    double z0 = 50.;
    double t0 = 0.;
    double max_t = 2000.;

    double left_r = 0.;
    double right_r = 100.;
    size_t last_n = 10;
    double eps_near = 1e-6;
    double eps_search = 1e-4;

    double r1 = find_r
    (
        implicit_method_euler, 
        R_1, 
        left_r, 
        right_r,
        last_n, 
        eps_near, 
        eps_search,
        b,
        delta, 
        delta_t,      
        x0,
        y0,
        z0,
        t0,
        max_t
    );
    std::cout << "r* = " << r1 << "\n";

    double r2 = find_r
    (
        implicit_method_euler, 
        R_2, 
        left_r, 
        right_r,
        last_n, 
        eps_near, 
        eps_search,
        b,
        delta, 
        delta_t,      
        x0,
        y0,
        z0,
        t0,
        max_t
    );
    std::cout << "r** = " << r2 << "\n";
}

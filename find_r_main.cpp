#include "find_r.cpp"
#include "methods.h"


int main (int argc, char ** argv)
{
    //double r = 20.;
    double b = 10. / 3.;
    double delta = 10.;
    double delta_t = 0.0001;
    double x0 = 10.;
    double y0 = 12.;
    double z0 = 25.;
    double t0 = 0.;
    double max_t = 2000.;

    double left_r = 0.;
    double right_r = 100.;
    size_t last_n = 100;
    double eps_near = 1e-7;
    double eps_search = 1e-4;

    double r1 = find_r
    (
        runge_kutta, 
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

    double r2_im_eu = find_r
    (
        explicit_method_euler, 
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
    std::cout << "r** (explicit euler) = " << r2_im_eu << "\n";

    double r2_ex_eu = find_r
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
    std::cout << "r** (implicit euler) = " << r2_ex_eu << "\n";

    double r2_runge = find_r
    (
        runge_kutta, 
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
    std::cout << "r** (  runge kutta ) = " << r2_runge << "\n";

    double r2_adams = find_r
    (
        adams_4, 
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
    std::cout << "r** (     adams    ) = " << r2_adams << "\n";
}

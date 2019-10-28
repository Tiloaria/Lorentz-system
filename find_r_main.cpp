#include "find_r.cpp"
#include "methods.h"

typedef
std::vector<Point> (* method_type)
(
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double,
    double
);


int main (int argc, char ** argv)
{
    //double r = 20.;
    double b = 10. / 3.;
    double delta = 10.;
    double delta_t = 0.001;
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

    auto f_bind = std::bind
    (
        find_r <method_type, double &, double &, double &, double &, double &, double &, double &>, 
        std::placeholders::_1, 
        std::placeholders::_2,
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

    double r1 = f_bind
    (
        runge_kutta, 
        R_1
    );
    std::cout << "r* = " << r1 << "\n";

    double r2_im_eu = f_bind
    (
        explicit_method_euler, 
        R_2
    );
    std::cout << "r** (explicit euler) = " << r2_im_eu << "\n";

    double r2_ex_eu = f_bind
    (
        implicit_method_euler, 
        R_2 
    );
    std::cout << "r** (implicit euler) = " << r2_ex_eu << "\n";

    double r2_runge = f_bind
    (
        runge_kutta, 
        R_2
    );
    std::cout << "r** (  runge kutta ) = " << r2_runge << "\n";

    double r2_adams = f_bind
    (
        adams_4, 
        R_2
    );
    std::cout << "r** (     adams    ) = " << r2_adams << "\n";
}

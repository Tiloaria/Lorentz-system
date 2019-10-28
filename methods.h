#ifndef METHODS
#define METHODS

#include "data_stuctures.h"

std::vector<Point> explicit_method_euler 
(
    double r = 20.,
    double b = 10. / 3.,
    double delta = 10.,
    double delta_t = 0.01,
    double x0 = 0.,
    double y0 = 0.,
    double z0 = 50.,
    double t0 = 0.,
    double max_t = 2.
) 
{
    Point a(x0, y0, z0, t0);
    std::vector<Point> ps;
    ps.push_back(a);
    while (a.t < max_t) {
        long double new_x = a.x + delta_t * delta * (a.y - a.x),
                new_y = a.y + delta_t * (-a.x * a.z + r * a.x - a.y),
                new_z = a.z + delta_t * (a.x * a.y - b * a.z),
                new_t = a.t + delta_t;
        a = Point(new_x, new_y, new_z, new_t);
        ps.push_back(a);
    }
    return ps;
}

std::vector<Point> runge_kutta
(
    double r = 20.,
    double b = 10. / 3.,
    double delta = 10.,
    double delta_t = 0.01,
    double x0 = 0.,
    double y0 = 0.,
    double z0 = 50.,
    double t0 = 0.,
    double max_t = 2.
) 
{
        Point a(x0, y0, z0, t0);
        std::vector<Point> ps;
        ps.push_back(a);
        while (a.t < max_t) {
                long double dt_div_2 = delta_t / 2;
                vec3 k0 = f(a.t, a.xyz(), delta, r, b);
                vec3 k1 = f(a.t + dt_div_2, a.xyz() + dt_div_2 * k0, delta, r, b);
                vec3 k2 = f(a.t + dt_div_2, a.xyz() + dt_div_2 * k1, delta, r, b);
                vec3 k3 = f(a.t + delta_t, delta_t * k2, delta, r, b);
                vec3 k = (k0 + 2 * k1 + 2 * k2 + k3) / 5;
                a = Point(a.t + delta_t, a.xyz() + delta_t * k);
                ps.push_back(a);
        }
        return ps;
}

std::vector<Point> implicit_method_euler 
(
    double r = 20.,
    double b = 10. / 3.,
    double delta = 10.,
    double delta_t = 0.01,
    double x0 = 0.,
    double y0 = 0.,
    double z0 = 50.,
    double t0 = 0.,
    double max_t = 2.
) 
{
    Point a(x0, y0, z0, t0);
    std::vector<Point> ps;
    ps.push_back(a);
    while (a.t < max_t) {
        long double new_x = a.x + delta_t * delta * (a.y - a.x),
                new_y = a.y + delta_t * (-a.x * a.z + r * a.x - a.y),
                new_z = a.z + delta_t * (a.x * a.y - b * a.z),
                new_t = a.t + delta_t;
        long double n_x = a.x + delta_t / 2 * (delta * (a.y - a.x) + delta * (new_y - new_x)),
                n_y = a.y + delta_t / 2 * ((-a.x * a.z + r * a.x - a.y) + (-new_x * new_z + r * new_x - new_y)),
                n_z = a.z + delta_t / 2 * ((a.x * a.y - b * a.z) + (new_x * new_y - b * new_z));
        a = Point (n_x, n_y, n_z, new_t);
        ps.push_back(a);
    }
    return ps;
}

std::vector <Point> adams_4
(
    double r = 20.,
    double b = 10. / 3.,
    double delta = 10.,
    double delta_t = 0.01,
    double x0 = 0.,
    double y0 = 0.,
    double z0 = 50.,
    double t0 = 0.,
    double max_t = 2.
) 
{
    size_t correct_times = 2;
    std::vector <Point> answer = runge_kutta(r, b, delta, delta_t, x0, y0, z0, t0, t0 + 5. * delta_t);
    auto f_ = [r, b, delta, delta_t] (Point value) -> Point 
    {
        return Point
        (
            delta_t * delta * (value.y - value.x),
            delta_t * (-value.x * value.z + r * value.x - value.y),
            delta_t * (value.x * value.y - b * value.z),
            delta_t
        );
    };
    
    while (answer.back().t < max_t)
    {
        size_t i = answer.size();
        Point predict = answer.back() + 
            ( 55./24.) * f_(answer[i - 1]) + 
            (-59./24.) * f_(answer[i - 2]) + 
            ( 37./24.) * f_(answer[i - 3]) +
            ( -9./24.) * f_(answer[i - 4]);

        Point correct = predict;

        for (size_t times = 0; times != correct_times; ++times)
        {
            correct = answer.back() + 
                ( 251./720.) * f_(correct) +
                ( 646./720.) * f_(answer[i - 1]) + 
                (-264./720.) * f_(answer[i - 2]) + 
                ( 106./720.) * f_(answer[i - 3]) +
                ( -19./720.) * f_(answer[i - 4]);

            correct.t = answer.back().t + delta_t;
        }

        answer.push_back(correct);
    }
    
    return answer;
}

#endif

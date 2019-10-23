#include <iostream>
#include <vector>

struct Point {
    long double x, y, z, t;

    Point (): x(0), y(0), z(0), t(0) {
    }

    Point (long double x0, long double y0, long double z0, long double t0): x(x0), y(y0), z(z0), t(t0) {
    }
};

const long double delta = 0,
b = 0,
r = 0,
delta_t = 0,
x0 = 0,
y0 = 0,
z0 = 0,
t0 = 0,
max_t = 0;

std::vector<Point> explicit_method_euler () {
    Point a(x0, y0, z0, t0);
    std::vector<Point> ps;
    ps.push_back(a);
    while (a.t < max_t) {
        long double new_x = a.x + delta_t * delta * (a.y - a.x),
        new_y = a.y + delta_t * (-a.x * a.z + r * a.x + a.y),
        new_z = a.z + delta_t * (-a.x * a.y - b * a.z),
        new_t = a.t + delta_t;
        a = Point(new_x, new_y, new_z, new_t);
        ps.push_back(a);
    }
    return ps;
}

std::vector<Point> implicit_method_euler () {
    Point a(x0, y0, z0, t0);
    std::vector<Point> ps;
    ps.push_back(a);
    while (a.t < max_t) {
        long double new_x = a.x + delta_t * delta * (a.y - a.x),
                new_y = a.y + delta_t * (-a.x * a.z + r * a.x + a.y),
                new_z = a.z + delta_t * (-a.x * a.y - b * a.z),
                new_t = a.t + delta_t;
        long double n_x = a.x + delta_t / 2 * (delta * (a.y - a.x) + delta * (new_y - new_x)),
        n_y = a.y + delta_t / 2 * ((-a.x * a.z + r * a.x + a.y) + (-new_x * new_z + r * new_x + new_y)),
        n_z = a.z + delta_t / 2 * ((-a.x * a.y - b * a.z) + (-new_x * new_y - b * new_z));
        a = Point (n_x, n_y, n_z, new_t);
        ps.push_back(a);
    }
    return ps;
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
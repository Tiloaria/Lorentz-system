#include <iostream>

struct Point {
    long double x, y, z, t;

    Point (): x(0), y(0), z(0), t(0) {
    }

    Point (long double x0, long double y0, long double z0, long double t0): x(x0), y(y0), z(z0), t(t0) {
    }
};

const long double delta, b, r, delta_t, x0, y0, z0, t0, max_t;

Point explicit_method_eiler () {
    Point a(x0, y0, z0, t0);
    while (a.t < max_t) {
        long double new_x = a.x + delta_t * delta * (a.y - a.x),
        new_y = a.y + delta_t * (-a.x * a.z + r * a.x + a.y),
        new_z = a.z + delta_t * (-a.x * a.y - b * a.z),
        new_t = t + delta_t;
        a = Point(new_x, new_y, new_z, new_t);
    }
    return a;
}

Point 

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
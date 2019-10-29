#include <iostream>
#include <vector>
#include <mgl2/mgl.h>
#include <string>
#include <math.h>

#define y0 double_y0

using std::vector;
using std::string;
using std::min;
using std::max;
using std::cout;

struct vec3 {
        long double x, y, z;

        vec3(long double x, long double y, long double z)
                : x(x)
                , y(y)
                , z(z)
        {}

        vec3 operator+(vec3 const& rhs) const {
                return {x + rhs.x, y + rhs.y, z + rhs.z};
        }

        vec3 operator/(long double k) const {
                return {x / k, y / k, z / k};
        }
};

vec3 operator*(long double k, vec3 const& rhs) {
        return {k * rhs.x, k * rhs.y, k * rhs.z};
}

struct Point {
    long double x, y, z, t;

    Point (): x(0), y(0), z(0), t(0) {
    }

    Point (long double x0, long double y0, long double z0, long double t0): x(x0), y(y0), z(z0), t(t0) {
    }

        Point (long double t, vec3 const& p)
                : x(p.x)
                , y(p.y)
                , z(p.z)
                , t(t)
        {}

        vec3 xyz() const {
                return {x, y, z};
    }
};

const long double delta = 10,
b = 8.0 / 3,
r = 20,
delta_t = 0.01,
x0 = 0,
y0 = 0,
z0 = r + 5,
t0 = 0,
max_t = 2;

std::vector<Point> explicit_method_euler () {
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

vec3 f(long double t, vec3 const& p) {
        return {
                delta * (p.y - p.x),
                -p.x * p.z + r * p.x + p.y,
                -p.x * p.y - b * p.z
        };
}

std::vector<Point> runge_kutta() {
        Point a(x0, y0, z0, t0);
        std::vector<Point> ps;
        ps.push_back(a);
        while (a.t < max_t) {
                long double dt_div_2 = delta_t / 2;
                vec3 k0 = f(a.t, a.xyz());
                vec3 k1 = f(a.t + dt_div_2, a.xyz() + dt_div_2 * k0);
                vec3 k2 = f(a.t + delta_t, a.xyz() + dt_div_2 * k1);
                vec3 k3 = f(a.t + delta_t, delta_t * k2);
                vec3 k = (k0 + 2 * k1 + 2 * k2 + k3) / 6;
                a = Point(a.t + delta_t, a.xyz() + delta_t * k);
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

const int num_of_dots = 100;
int scale_to_int(long double max_val, long double min_val, long double x) {
    long double step = (max_val - min_val) / num_of_dots;
    cout << round((x - min_val) / step) << " - rounded\n";
    return round((x - min_val) / step);

}

void visualisation(const vector<Point> & points, string name) {
    cout << "size " << points.size() << "\n";
    mglGraph gr;
    long double max_val = -100000.0, min_val = -100000.0;
    long double max_val_x = max_val, min_val_x = min_val;
    long double max_val_y = max_val, min_val_y = min_val;
    long double max_val_z = max_val, min_val_z = min_val;
    for (Point p: points) {
        max_val = max(max_val, p.t);
        min_val = min(min_val, p.t);
        max_val_x = max(max_val_x, p.x);
        min_val_x = min(min_val_x, p.x);
        max_val_y = max(max_val_y, p.y);
        min_val_y = min(min_val_y, p.y);
        max_val_z = max(max_val_z, p.z);
        min_val_z = min(min_val_z, p.z);
    }
    const long double Eps = (max_val - min_val) / 10;
    max_val += Eps;
    min_val -= Eps;
    cout << "min_val " << min_val << " max_val = " << max_val << "\n";
    mglData dat_x(scale_to_int(max_val, min_val, min_val), scale_to_int(max_val, min_val, min_val));
    mglData dat_y(scale_to_int(max_val, min_val, min_val), scale_to_int(max_val, min_val, min_val));
    mglData dat_z(scale_to_int(max_val, min_val, min_val), scale_to_int(max_val, min_val, min_val));
    for (Point p: points) {
        dat_x.a[scale_to_int(max_val, min_val, p.t)] = scale_to_int(max_val_x, min_val_x, p.x);
        dat_y.a[scale_to_int(max_val, min_val, p.t)] = scale_to_int(max_val_y, min_val_y, p.y);
        dat_z.a[scale_to_int(max_val, min_val, p.t)] = scale_to_int(max_val_z, min_val_z, p.z);
    }
    gr.Light(true);
    gr.Surf(dat_x);
    gr.Cont(dat_x, "b");
    gr.Axis();
    gr.WriteFrame((name + "_x" + ".png").c_str());
    gr.Light(true);
    gr.Surf(dat_y);
    gr.Cont(dat_y, "b");
    gr.Axis();
    gr.WriteFrame((name + "_y" + ".png").c_str());
    gr.Light(true);
    gr.Surf(dat_z);
    gr.Cont(dat_z, "b");
    gr.Axis();
    gr.WriteFrame((name + "_z" + ".png").c_str());
}

void print(std::vector<Point> const& ps) {
        for (auto const& p : ps) {
                std::cout << p.t << ' ' << p.x << ' ' << p.y << ' ' << p.z << std::endl;
        }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    visualisation(implicit_method_euler(), "Implicit Euler");
    visualisation(explicit_method_euler(), "Explicit Euler");
    std::cout << "explicit euler:" << std::endl;
    print(explicit_method_euler());
    std::cout << "implicit euler:" << std::endl;
    print(implicit_method_euler());
    std::cout << "runge_kutta: " << std::endl;
    print(runge_kutta());
    return 0;
}

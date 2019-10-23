#include <iostream>
#include <vector>
#define y0 yy0

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

/*const long double delta = 0,
b = 0,
r = 0,
delta_t = 0,
x0 = 0,
y0 = 0,
z0 = 0,
t0 = 0,
max_t = 2;*/

const long double delta = 10,
b = 10.0 / 3,
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
        new_y = a.y + delta_t * (-a.x * a.z + r * a.x + a.y),
        new_z = a.z + delta_t * (-a.x * a.y - b * a.z),
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

void print(std::vector<Point> const& ps) {
	for (auto const& p : ps) {
		std::cout << p.t << ' ' << p.x << ' ' << p.y << ' ' << p.z << std::endl;
	}
}

int main() {
	std::cout << "explicit euler:" << std::endl;
	print(explicit_method_euler());
	std::cout << "implicit euler:" << std::endl;
	print(implicit_method_euler());
	std::cout << "runge_kutta: " << std::endl;
	print(runge_kutta());
    return 0;
}
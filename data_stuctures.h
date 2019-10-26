#ifndef DATA_STRUCTURES
#define DATA_STRUCTURES

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
    
    Point operator + (Point const & rhs) const
    {
        return Point(x + rhs.x, y + rhs.y, z + rhs.z, t + rhs.t);
    }

    Point operator * (double a) const 
    {
        return Point(x * a, y * a, z * a, t * a);
    }
};

Point operator * (double lhs, Point const & rhs)
{
    return rhs * lhs;
}

vec3 f(long double t, vec3 const& p, double delta, double r, double b) {
        return {
                delta * (p.y - p.x),
                -p.x * p.z + r * p.x - p.y,
                +p.x * p.y - b * p.z
        };
}

std::ostream & operator << (std::ostream & s, Point const & a)
{
    s << a.x << " " << a.y << " " << a.z << " " << a.t;
    return s;
}

template <typename T> 
std::ostream & operator << (std::ostream & s, std::vector <T> const & a)
{
    for (auto const & i : a)
    {
        s << i << "\n";
    }
    return s;
}

#endif

#ifndef FIND_R
#define FIND_R

#include <algorithm>
#include <type_traits>
#include <functional>

template <typename ... T>
double bin_search (double left, double right, double eps, std::function <bool (double, T ...)> comparator, T && ... args) // comparator : 1 1 1 1 0 0 0 0
{
    while (right - left > eps)
    {
        double middle = (left + right) / 2.;

        if (comparator(middle, std::forward <T &&> (args) ...))
        {
            left = middle;
        }
        else
        {
            right = middle;
        }
    }
    return left;
}

bool near (Point const & a, Point const & b, double eps)
{
    return (std::fabs(a.x - b.x) + std::fabs(a.y - b.y) + std::fabs(a.z - b.z)) < eps;
}

bool R_1 (std::vector <Point> const & values, size_t last_n, double eps, double, double)
{
    Point etalon = {0., 0., 0., 0.};
    for (size_t i = values.size() - std::min(last_n, values.size()); i < values.size(); ++i)
    {
        if (!near(values[i], etalon, eps))
        {
            return 0;
        }
    }
    return 1;
}

bool R_2 (std::vector <Point> const & values, size_t last_n, double eps, double b, double r)
{
    double sbr1 =  std::sqrt(std::fabs(b * (r - 1.)));
    Point etalon_0 = {0., 0., 0., 0.};
    Point etalon_1 = { sbr1,  sbr1, r - 1., 0.};
    Point etalon_2 = {-sbr1, -sbr1, r - 1., 0.};

    bool answer_1 = 1, answer_2 = 1, answer_0 = 1;
    for (size_t i = values.size() - std::min(last_n, values.size()); i < values.size(); ++i)
    {
        if (!near(values[i], etalon_1, eps))
        {
            answer_1 = 0;
        }
        if (!near(values[i], etalon_2, eps))
        {
            answer_2 = 0;
        }
        if (!near(values[i], etalon_0, eps))
        {
            answer_0 = 0;
        }
    }
    return answer_0 || answer_1 || answer_2;
}



struct comparator
{
    comparator 
    (
        std::function
        <
            std::vector <Point> (double r)
        > _f,
        std::function 
        <
            bool
            (
                std::vector <Point> const & values, 
                size_t last_n, 
                double eps, 
                double b, 
                double r
            )
        > _r_srec_comp,
        size_t _last_n, 
        double _eps, 
        double _b
    ) :
        f(_f),
        r_spec_comp(_r_srec_comp),
        last_n(_last_n),
        eps(_eps),
        b(_b)
    {}

    bool operator () (double r)
    {
        return r_spec_comp(f(r), last_n, eps, b, r);
    }

private:
    std::function
    <
        std::vector <Point> (double r)
    > f;
    std::function 
    <
        bool
        (
            std::vector <Point> const & values, 
            size_t last_n, 
            double eps, 
            double b, 
            double r
        )
    > r_spec_comp;
    size_t last_n;
    double eps;
    double b;
};

template <typename F, typename ... T>
double find_r 
(
    F method, //std::vector <Point> (r, b, args ...)
    
    std::function 
    <
        bool
        (
            std::vector <Point> const & values, 
            size_t last_n, 
            double eps, 
            double b, 
            double r
        )
    > r_spec_comp,
    
    double left_r,
    double right_r,
    size_t last_n,
    double eps,
    double b,
    T && ... args
)
{
    return bin_search
    (
        left_r, 
        right_r, 
        eps, 
        std::function
        <
            bool (double r)
        >
        (
            comparator
            (
                std::bind(method, std::placeholders::_1, b, std::ref(args) ...), 
                r_spec_comp, 
                last_n, 
                eps, 
                b
            )
        )
    );
}


#endif

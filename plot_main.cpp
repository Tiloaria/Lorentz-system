#include "methods.h"
#include "draw_plots.cpp"

template <typename F, typename ... T>
struct apply_function
{
    apply_function (T && ... _args) :
        args(std::forward <T &&> (_args) ...)
    {}
    
    template <size_t ... n>
    typename std::result_of <F(T && ...)> :: type apply (F f, std::integer_sequence <size_t, n ...>)
    {
        return f(std::forward <T &&> (std::get <n> (args)) ...);
    }
    
    typename std::result_of <F(T && ...)> :: type operator () (F f)
    {
        return apply(f, std::make_index_sequence <sizeof ... (T)>());
    }
    
private:
    std::tuple <T ...> args;
};

int main ()
{
    const long double delta = 10,
    b = 10.0 / 3,
    r = 30,
    delta_t = 0.0001,
    x0 = 10,
    y0 = 12,
    z0 = r + 5,
    t0 = 0,
    max_t = 50;

    draw all_plots;

    auto f_apply = apply_function <method_type, double, double, double, double, double, double, double, double, double>
    (
            r, 
            b,
            delta, 
            delta_t,      
            x0,
            y0,
            z0,
            t0,
            max_t
    );

    all_plots.add(f_apply(explicit_method_euler), "explicit\\_method\\_euler");

    all_plots.add(f_apply(implicit_method_euler), "implicit\\_method\\_euler");
    
    all_plots.add(f_apply(runge_kutta), "runge\\_kutta");
    
    all_plots.add(f_apply(adams_4), "adams");
}

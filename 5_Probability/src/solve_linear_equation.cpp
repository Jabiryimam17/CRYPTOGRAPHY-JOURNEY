//
// Created by Jabir on 1/19/2026.
//

#include  "../include/solve_linear_equation.h"



ull solve_linear_equation(ull u, ull v, ull g, ull h, ull p)
{
    ull d=std::gcd(v, p-1);
    if (u%d!=0) return ULLONG_MAX;
    long long s_l = extended_euclidean_algorithm(p-1,v).second;
    ull s = (s_l+p-1)%(p-1);
    ull w = u*s%(p-1);
    ull x=(w/d);
    ull len=(p-1)/d;
    for (int k=0; k < d; k++)
    {
        if (h==fast_exponentiation(g, x, p)) return x;
        x = (x+len)%(p-1);
    }
    return ULLONG_MAX;
}

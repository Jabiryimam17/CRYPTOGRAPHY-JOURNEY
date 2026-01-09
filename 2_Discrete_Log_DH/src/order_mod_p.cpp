//
// Created by Jabir on 1/9/2026.
//
#include "../include/order_mod_p.h"

#include <vector>

ull order_mod_p(ull g, ull p)
{
    ull n = p - 1;
    ull ord = n;
    std::vector<ull> factors;

    for (ull f = 2; f * f <= n; ++f)
    {
        if (n % f == 0)
        {
            factors.push_back(f);
            while (n % f == 0)
                n /= f;
        }
    }

    if (n > 1) factors.push_back(n);

    for (ull q : factors)
    {
        while (ord % q == 0 &&
               fast_exponentiation(g, ord / q, p) == 1)
        {
            ord /= q;
        }
    }

    return ord;
}

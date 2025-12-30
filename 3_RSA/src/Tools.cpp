//
// Created by Jabir on 12/29/2025.
//

#include "../include/Tools.h"

#include <cmath>
#include <numbers>
#include <numeric>

ull miller_rabin_test::random_prime_generator(unsigned int k)
{
    ull r_p = 0;
    bool prime=false;
    while (!prime)
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(r_p), sizeof(r_p));
        if (r_p%2==0) continue;
        ull witness = 0;
        prime=true;
        for (int i=0; i < k; i++)
        {
            RAND_bytes(reinterpret_cast<unsigned char*>(witness), sizeof(witness));
            if (is_composite(r_p, witness)) {prime=false; break;}
        }
    };
    return r_p;
}

bool miller_rabin_test::is_composite(ull n, ull a)
{
    ull d = n - 1;
    ull s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    ull x = fast_exponentiation(a, d, n);
    if (x == 1 || x == n - 1)
        return false;

    for (ull i = 1; i < s; i++) {
        x = (x * x) % n;
        if (x == n - 1)
            return false;
    }

    return true;
}

ull miller_rabin_test::riemann_based_random_prime_generator() // conjecture based not theory based
{
    ull r_p = 0;
    bool prime=false;
    while (!prime)
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(r_p), sizeof(r_p));
        if (r_p%2==0) continue;
        ull r_root=log(r_p)/log(std::numbers::e);
        ull r=2*(r_root*r_root);
        prime=true;
        for (int w=3; w < r; w+=2)
        {
            if (is_composite(r_p, w)) {prime=false; break;}
        }
    };
    return r_p;
}

//
// Created by Jabir on 1/8/2026.
//



#include "../include//GENERATE_ROOT.h"
ull generate_root(ull p)
{
    std::vector<ull> primes=prime_factorize(p-1);
    ull g;
    bool g_found=false;
    while (!g_found)
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&g), sizeof(g));
        g%=p;
        if (g < 2) continue;
        g_found=true;
        for (auto& q:primes)
        {
            if (fast_exponentiation(g, (p-1)/q, p)==1)
            {
                g_found=false;
                break;
            }
        }
    }
    return g;
}

std::vector<ull> prime_factorize(ull n)
{
    std::vector<ull> primes;
    for (ull p = 2; p * p <= n; ++p)
    {
        if (n % p == 0)
        {
            primes.push_back(p);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) primes.push_back(n); // remaining prime
    return primes;
}
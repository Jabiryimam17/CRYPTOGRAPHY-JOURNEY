//
// Created by Jabir on 1/11/2026.
//


#include  "../include/QUADRATIC_SIEVE.h"


QS::QS(ull B, ull N) : B(B), N(N)
{
    build_prime_base();
}

void QS::build_prime_base()
{
    std::vector is_prime(B + 1, true);
    is_prime[0] = is_prime[1] = false;
    for (ull p = 2; p * p <= B; p++)
    {
        if (!is_prime[p]) continue;
        for (ull n = p + p; n <= B; n += p) is_prime[n] = false;
        ull sol = calc_sqrt_sol(p, N);
        if (sol != -1) prime_bases.emplace_back(p, sol);
    }
    if (is_prime[B])
    {
        ull sol = calc_sqrt_sol(B, N);
        if (sol != -1) prime_bases.emplace_back(B, sol);
    }
}

ull QS::calc_sqrt_sol(ull p, ull n)
{
    if (p == 2) return n % p;

    if (fast_exponentiation(n, (p - 1) / 2, p) != 1) return -1; // no root

    if (p % 4 == 3) return fast_exponentiation(n, (p + 1) / 4, p);
    return tonelli_shanks(n, p);
}

void QS::sieve_potentials(std::vector<ull>& candidates, ull a)
{

    for (auto [p, s] : prime_bases)
    {
        sieve_potentials_p(candidates, a, p, s);
        sieve_potentials_p(candidates, a, p, p - s);
    }
}


void QS::sieve_potentials_p(std::vector<ull>& candidates, ull a, ull p, ull s)
{
    ull f = calc_start(p, a, s);
    for (size_t i = f - a; i < candidates.size(); i += p)
    {
        while (candidates[i] % p == 0) candidates[i] /= p;
    }
    // the index may be confisuing but since all elemtns are like a, a+1, a+2, a+3 results this is ok
}

void QS::sieve_b_smooths(std::vector<ull>& b_smooths, std::vector<int> where, std::vector<std::bitset<S>>& m, ull a)
{
    for (size_t i=0; i < prime_bases.size(); i++)
    {
        auto [p, s]=prime_bases[i];
        sieve_b_smooths_p(b_smooths,where, m, a, p, s, i);
        sieve_b_smooths_p(b_smooths, where, m,a,p, p - s, i);
    }
}
void QS::sieve_b_smooths_p(std::vector<ull>& b_smooths,std::vector<int> where, std::vector<std::bitset<S>>& m,
                           ull a, ull p, ull s, size_t r)
{
    ull f = calc_start(p, a, s);
    for (size_t i=f-a; i < b_smooths.size(); i+=p)
    {
        if (where[i]==-1) continue;
        ull e_mod=0;
        while (b_smooths[i]%p==0) b_smooths[i]/=p, e_mod ^=1;
        m[r][where[i]]=e_mod;
    }
}

ull QS::calc_start(ull p, ull a, ull s)
{
    ull d = (a > s) ? (a - s + p - 1) / p : 0;
    return d * p + s;
}

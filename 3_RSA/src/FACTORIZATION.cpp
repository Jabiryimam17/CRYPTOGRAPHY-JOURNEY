//
// Created by Jabir on 1/12/2026.
//


#include "../include/FACTORIZATION.h"

#include <numeric>

ull RSA_FACTORIZATION::factorize(ull N)
{
    ull B=calc_B(N);
    ull a=static_cast<ull>(sqrt(N))+1;
    size_t n=B*B;
    std::vector<ull> candidates(n);

    for (size_t i=0; i < n; i++)
    {
        ull x=a+i;
        candidates[i]=x*x-N;// can i replace tis with nums[i] = x*x%N
    }
    QS qua_sieve=QS(B, N);
    qua_sieve.sieve_potentials(candidates, a);
    int m=0;
    std::vector<int> where(candidates.size(), -1);
    std::vector<ull> b_smooths(candidates.size(), 1), bs;
    for (size_t i=0; i < candidates.size(); i++)
    {
        ull c=candidates[i];
        if (c==1) where[i]=m++, b_smooths[i]=(i+a)*(i+a)-N, bs.push_back(i+a);
    }
    std::vector<std::bitset<N_P>> u(m);
    qua_sieve.sieve_b_smooths(b_smooths, where, u, a);
    std::vector<std::bitset<N_B>> ans;
    gauss_bit_qs(u, m, qua_sieve.prime_bases.size(), ans);
    for (auto& v:ans)
    {
        ull a_pro=1, b_pro=1;
        for (size_t i=0; i < m; i++)
        {
            if (v[i]) a_pro *= bs[i], b_pro*=bs[i]*bs[i]-N;
        }
        b_pro = static_cast<ull>(sqrt(b_pro));
        ull g = std::gcd(N, a_pro-b_pro);
        if (g!=1 && g!=N) return g;
    }
    return 0;
}

ull RSA_FACTORIZATION::calc_B(ull N)
{
    double ln_n=log(N);
    double double_ln_n=log(ln_n);
    double exp = sqrt(double_ln_n*ln_n*0.5);
    double B = pow(std::numbers::e, exp);
    return static_cast<ull>(B);
}




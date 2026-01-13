//
// Created by Jabir on 1/12/2026.
//


#include "../include/FACTORIZATION.h"

RSA_FACTORIZATION::RSA_FACTORIZATION(ull N):N(N)
{
    this->B=calc_B(N);
    this->a=sqrt(N)+1;
    size_t n=3*B;
    candidates.resize(n);
    for (size_t i=0; i < n; i++)
    {
        ull x=a+i;
        candidates[i]=x*x-N;// can i replace tis with nums[i] = x*x%N
    }
    QS qua_sieve=QS(B, N);
    qua_sieve.sieve_potentials(candidates, a);
    int m=0;
    std::vector<int> where(candidates.size(), -1);
    std::vector<ull> b_smooths(candidates.size(), 1);
    for (size_t i=0; i < candidates.size(); i++)
    {
        ull c=candidates[i];
        if (c==1) where[i]=m++, b_smooths[i]=(i+a)*(i+a)-N;
    }
    std::vector<std::bitset<S>> u(qua_sieve.prime_bases.size());
    qua_sieve.sieve_b_smooths(b_smooths, where, u, a);

}

ull RSA_FACTORIZATION::calc_B(ull N)
{
    double ln_n=log(N);
    double double_ln_n=log(ln_n);
    double exp = sqrt(double_ln_n*ln_n*0.5);
    double B = pow(std::numbers::e, exp);
    return static_cast<ull>(B);
}




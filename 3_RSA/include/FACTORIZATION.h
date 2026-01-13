//
// Created by Jabir on 1/12/2026.
//

#ifndef CRYPTOGRAPHY_FACTORIZATION_H
#define CRYPTOGRAPHY_FACTORIZATION_H
#include "QUADRATIC_SIEVE.h"
#include "Tools.h"
class RSA_FACTORIZATION
{
public:
    ull N;
    ull B;
    ull a;
    std::vector<ull> candidates;
    RSA_FACTORIZATION(ull N);
    double calc_B(ull N);
    void solve_linear_eq();
};
#endif //CRYPTOGRAPHY_FACTORIZATION_H
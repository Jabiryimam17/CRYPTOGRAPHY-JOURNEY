//
// Created by Jabir on 1/12/2026.
//

#ifndef CRYPTOGRAPHY_FACTORIZATION_H
#define CRYPTOGRAPHY_FACTORIZATION_H
#include "QUADRATIC_SIEVE.h"
class RSA_FACTORIZATION
{
public:

    ull factorize(ull N);
    ull calc_B(ull N);
    // void solve_linear_eq();
};
#endif //CRYPTOGRAPHY_FACTORIZATION_H
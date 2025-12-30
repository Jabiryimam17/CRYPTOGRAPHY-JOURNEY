//
// Created by Jabir on 12/29/2025.
//

#include "../include//RSA_CUSTOM.h"

#include <numeric>
#include "../../1_An_Introduction_To_Cryptography//include//EEA.h"
#include "../../1_An_Introduction_To_Cryptography//include//Tools.h"


RSA_CUSTOM::RSA_CUSTOM()
{
    p = random_prime_generator(5);
    do
    {
        q = random_prime_generator(5);
    } while (p==q);
    N = p*q;
    ull pro_pq=(p-1)*(q-1);
    do
    {
        e = random_prime_generator(5);
    } while (e >= pro_pq && std::gcd(e, pro_pq)!=1);
    d = (extended_euclidean_algorithm(pro_pq, e).second%pro_pq+pro_pq)%pro_pq;
}

ull RSA_CUSTOM::encrypt(ull m, ull o_N, ull o_e)
{
    if (m >= o_N) throw;
    return fast_exponentiation(m, o_e, o_N);
}

ull RSA_CUSTOM::decrypt(ull c) const
{
    return fast_exponentiation(c, d, N);
}

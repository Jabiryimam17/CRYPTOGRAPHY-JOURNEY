//
// Created by Jabir on 1/8/2026.
//

#include "../include//ELGAMAL_SIGNATURE.h"

#include <numeric>


ELGAMAL_SIGNATURE::ELGAMAL_SIGNATURE(ull _p)
{
    p = _p;
    g = generate_root(p);
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&a), sizeof(a));
        a %= p;
    } while (a==0);
}

SIGNED_MESSAGE ELGAMAL_SIGNATURE::sign_message(ull m)
{
    ull k;
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&k), sizeof(k));
        k%=p;
    } while (std::gcd(k, p-1)!=1);
    ull s_f=fast_exponentiation(g, k, p);
    ull k_in=extended_euclidean_algorithm(p-1, k).second;
    ull s_l=(m+p-1-a*s_f%(p-1))*k_in%(p-1);
    return {m, {s_f, s_l}};
}


bool ELGAMAL_SIGNATURE::verify_message(SIGNED_MESSAGE s_m, ull g, ull A, ull p)
{
    ull r = s_m.s.first;
    ull s = s_m.s.second;
    ull m = s_m.m;

    ull lhs = mod_mul(fast_exponentiation(A, r, p),
                      fast_exponentiation(r, s, p),
                      p);

    ull rhs = fast_exponentiation(g, m, p);
    return lhs == rhs;
}


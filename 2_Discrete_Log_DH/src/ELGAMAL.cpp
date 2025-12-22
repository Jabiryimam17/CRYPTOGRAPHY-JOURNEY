//
// Created by Jabir on 12/22/2025.
//
#include "../include//ELGAMAL.h"
#include "../../1_An_Introduction_To_Cryptography//include//Tools.h"

ELGAMAL::ELGAMAL(ull _g, ull _p)
{
    build_keys(_g, _p);
}

void ELGAMAL::build_keys(ull _g, ull _p)
{
    p = _p;
    g = _g%p;
    private_key = gen_rand_num();
    public_key = fast_exponentiation(g, private_key, p);
}

std::pair<ull, ull> ELGAMAL::encrypt(ull m, ull o_public_key) const
{
    ull k=gen_rand_num();
    ull c=fast_exponentiation(g, k, p);
    ull d=m*fast_exponentiation(o_public_key, k, p)%p;
    return {c, d};
}

ull ELGAMAL::gen_rand_num() const
{
    ull new_k=0;
    ull limit=UINT64_MAX-UINT64_MAX%p;
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&new_k), sizeof(new_k));
    } while (new_k >= limit);
    return new_k%p;
}

ull ELGAMAL::decrypt(ull c, ull d) const
{
    return d*fast_exponentiation(c, p-private_key-1, p)%p; // this assumes p is prime if not use extended euclidean algorithim
}

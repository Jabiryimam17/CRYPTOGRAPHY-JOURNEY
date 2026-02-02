//
// Created by Jabir on 2/2/2026.
//

#include "../include//Elliptic_DSA.h"

#include <openssl/rand.h>


SIGNED_MESSAGE E_DSA::sign_message(Point G, E_Group E, ull q, ull m)
{
    ull a;
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&a), sizeof(a));
        a %= q;
    }
    while (a == 0);
    Point A = E.scalar_mul_NAF(G, a);

    ull k;
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&k), sizeof(k));
        k %= q;
    }
    while (k == 0);

    ull k_in = fast_exponentiation(k, q - 2, q);

    ull r = E.scalar_mul_NAF(G, k).x % q;

    ull s = mod_mul((m + mod_mul(a, r, q)) % q, k_in, q);

    if (r == 0 || s == 0)
        return sign_message(G, E, q, m);

    return {m, r, s, A, G, q, E};
}


bool E_DSA::verify_signature(SIGNED_MESSAGE sig)
{
    auto [m, r, s, A, G, q, E] = sig;
    if (r == 0 || s == 0) return false;
    m %= q;
    ull s_in = fast_exponentiation(s, q - 2, q);
    ull v_f = m * s_in % q;
    ull v_l = r * s_in % q;
    Point left = E.scalar_mul_NAF(G, v_f);
    Point right = E.scalar_mul_NAF(A, v_l);
    ull calc_r = E.add_point(left, right).x;
    return calc_r % q == r;
};

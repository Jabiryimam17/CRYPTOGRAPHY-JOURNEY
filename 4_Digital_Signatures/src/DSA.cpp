//
// Created by Jabir on 1/8/2026.
//

#include "../include/DSA.h"

#include <iostream>

DSA_CUSTOM::DSA_CUSTOM(ull _p, ull _q, ull _a, ull _g):p(_p), q(_q), a(_a), g(_g)
{

}

SIGNED_MESSAGE DSA_CUSTOM::sign_message(ull m)
{
    ull k;
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&k), sizeof(k));
        k%=q;
    } while (k==0);

    ull r=fast_exponentiation(g, k, p)%q;
    ull k_in=fast_exponentiation(k, q-2, q);
    ull s=(m+a*r)%q*k_in%q;
    std::cout << "k: " << k << std::endl;
    std::cout << "k inverse: " << k_in << std::endl;
    std::cout << "r: " << r << std::endl;
    std::cout << "s: " << s << std::endl;
    return {m, r, s};
}

bool DSA_CUSTOM::verify_message(SIGNED_MESSAGE s_m, ull g, ull A, ull q, ull p)
{

    auto [m, r,s]=s_m;
    ull s_in=fast_exponentiation(s, q-2, q);
    ull v_f=(m*s_in)%q;
    ull v_l=r*s_in%q;
    ull lhs=mod_mul(fast_exponentiation(g, v_f, p), fast_exponentiation(A, v_l, p), p)%q;
    std::cout << "s inverse: " << s_in << std::endl;
    std::cout << "v_f: " << v_f << std::endl;
    std::cout << "v_l: " << v_l << std::endl;
    std::cout << "lhs: " << lhs << "==" << r << std::endl;
    return lhs==r;

}

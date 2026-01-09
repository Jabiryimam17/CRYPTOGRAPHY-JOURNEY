//
// Created by Jabir on 1/8/2026.
//

#include "../include/DSA.h"

#include <iostream>

DSA_CUSTOM::DSA_CUSTOM()
{
    q = miller_rabin_test::random_prime_generator(15);
    bool found=false;
    while (!found)
    {
        ull k=0;
        RAND_bytes(reinterpret_cast<unsigned char*>(&k), 2);
        p = k*q+1;
        found=true;
        ull witness=0;
        for (size_t t=0; t < 15; t++)
        {
            RAND_bytes(reinterpret_cast<unsigned char*>(&witness), 4);
            witness %= p;
            if (miller_rabin_test::is_composite(p, witness))
            {
                found=false;
                break;
            }
        }
    };
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&a),sizeof(a));
        a %= q;
    } while (a==0);
    ull g_o = generate_root(p);
    g = fast_exponentiation(g_o, (p-1)/q, p);

}

SIGNED_MESSAGE DSA_CUSTOM::sign_message(ull m)
{
    m %= q;
    ull k;
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&k), sizeof(k));
        k%=q;
    } while (k==0);

    ull r=fast_exponentiation(g, k, p)%q;
    ull k_in=fast_exponentiation(k, q-2, q);
    ull s = mod_mul((m + mod_mul(a, r, q)) % q, k_in, q);

    return {m, r, s};
}

bool DSA_CUSTOM::verify_message(SIGNED_MESSAGE s_m, ull g, ull A, ull q, ull p)
{

    auto [m, r,s]=s_m;
    m %= q;
    ull s_in=fast_exponentiation(s, q-2, q);
    ull v_f=(m*s_in)%q;
    ull v_l=r*s_in%q;
    ull lhs=mod_mul(fast_exponentiation(g, v_f, p), fast_exponentiation(A, v_l, p), p)%q;
    // std::cout << "s inverse: " << s_in << std::endl;
    // std::cout << "v_f: " << v_f << std::endl;
    // std::cout << "v_l: " << v_l << std::endl;
    // std::cout << "lhs: " << lhs << "==" << r << std::endl;
    return lhs==r;

}

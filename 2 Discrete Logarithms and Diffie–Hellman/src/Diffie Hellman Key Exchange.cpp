//
// Created by Jabir on 12/22/2025.
//

#include "../include//Diffie Hellman Key Exchange.h"

DIFFIE_HELLMAN_KEY_EXCHANGE::DIFFIE_HELLMAN_KEY_EXCHANGE(ull _g, ull _p)
{
    build_keys(_g, _p);
}

ull DIFFIE_HELLMAN_KEY_EXCHANGE::rand_gen_private_key() const
{
    ull new_private_key = 0;
    unsigned long long limit=UINT64_MAX- UINT64_MAX %p;
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&new_private_key), sizeof(new_private_key)); // This will update the new private keywhile (new_private_key >= limit);
    } while (new_private_key >= limit);
    return new_private_key%p;

}

void DIFFIE_HELLMAN_KEY_EXCHANGE::build_keys(ull _g, ull _p)
{
    p = _p;
    g = _g %p;
    private_key = rand_gen_private_key();
    public_key = fast_exponentiation(g, private_key, p);
}

void DIFFIE_HELLMAN_KEY_EXCHANGE::calc_shared_secret(ull o_public_key)
{
    shared_secret=fast_exponentiation(o_public_key, private_key, p);
}

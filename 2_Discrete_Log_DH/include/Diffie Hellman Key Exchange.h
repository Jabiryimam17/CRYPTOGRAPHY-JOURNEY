//
// Created by Jabir on 12/22/2025.
//

#ifndef CRYPTOGRAPHY_DIFFIE_HELLMAN_KEY_EXCHANGE_H
#define CRYPTOGRAPHY_DIFFIE_HELLMAN_KEY_EXCHANGE_H
#include <openssl/rand.h>
using ull = unsigned long long;
class DIFFIE_HELLMAN_KEY_EXCHANGE
{
    ull shared_secret{};
    ull private_key{};
public:
    ull public_key{};
    ull g{};
    ull p{};
    DIFFIE_HELLMAN_KEY_EXCHANGE(ull _g, ull _p);
    void build_keys(ull _g, ull _p);
    [[nodiscard]] ull rand_gen_private_key() const;
    void calc_shared_secret(ull o_public_key);
};
#endif //CRYPTOGRAPHY_DIFFIE_HELLMAN_KEY_EXCHANGE_H
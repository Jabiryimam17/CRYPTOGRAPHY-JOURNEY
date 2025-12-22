//
// Created by Jabir on 12/22/2025.
//

#ifndef CRYPTOGRAPHY_ELGAMAL_H
#define CRYPTOGRAPHY_ELGAMAL_H
#include <utility>
#include <openssl/rand.h>
using ull=unsigned long long;
class ELGAMAL
{
private:
    ull private_key;
public:
    ull public_key;
    ull g;
    ull p;
    ELGAMAL(ull _g, ull _p);
    void build_keys(ull _g, ull _p);
    std::pair<ull,ull> encrypt(ull m, ull o_public_key) const;
    ull gen_rand_num() const;
    ull decrypt(ull c, ull d) const;

};
#endif //CRYPTOGRAPHY_ELGAMAL_H
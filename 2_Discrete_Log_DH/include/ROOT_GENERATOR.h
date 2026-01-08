//
// Created by Jabir on 1/8/2026.
//

#ifndef CRYPTOGRAPHY_ROOT_GENERATOR_H
#define CRYPTOGRAPHY_ROOT_GENERATOR_H
#include <vector>
#include <openssl/rand.h>
#include  "../../1_An_Introduction_To_Cryptography//include//Tools.h"
using ull = unsigned long long;
ull generate_root(ull p);
std::vector<ull> prime_factorize(ull n);
#endif //CRYPTOGRAPHY_ROOT_GENERATOR_H
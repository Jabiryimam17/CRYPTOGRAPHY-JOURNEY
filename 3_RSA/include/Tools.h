//
// Created by Jabir on 12/29/2025.
//

#ifndef CRYPTOGRAPHY_TOOLS_H
#define CRYPTOGRAPHY_TOOLS_H
#include <openssl/rand.h>
#include  "../../1_An_Introduction_To_Cryptography/include/Tools.h"
using ull=unsigned long long;
class miller_rabin_test
{
public:
    static ull random_prime_generator(unsigned int k);
    static bool is_composite(ull n, ull witness);
    static ull riemann_based_random_prime_generator();
};
#endif //CRYPTOGRAPHY_TOOLS_H
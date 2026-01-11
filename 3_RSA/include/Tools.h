//
// Created by Jabir on 12/29/2025.
//

#ifndef CRYPTOGRAPHY_TOOLS_H
#define CRYPTOGRAPHY_TOOLS_H
#include <vector>
#include <openssl/rand.h>
#include  "../../1_An_Introduction_To_Cryptography/include/Tools.h"
using ull=unsigned long long;
const double EPS=1e-9;
const int INF = 1e9+7;
class miller_rabin_test
{
public:
    static ull random_prime_generator(unsigned int k);
    static bool test_witness(unsigned int k, ull p);
    static bool is_composite(ull n, ull witness);
    static ull riemann_based_random_prime_generator();
};

int gauss(std::vector<std::vector<double>>& a, std::vector<double>& ans);
#endif //CRYPTOGRAPHY_TOOLS_H
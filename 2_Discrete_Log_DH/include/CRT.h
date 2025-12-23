//
// Created by Jabir on 12/23/2025.
//

#ifndef CRYPTOGRAPHY_CRT_H
#define CRYPTOGRAPHY_CRT_H
#include <vector>

using ull=unsigned long long;
struct Eq
{
    ull a;
    ull m;
};

ull crt(const std::vector<Eq>& equations);

#endif //CRYPTOGRAPHY_CRT_H
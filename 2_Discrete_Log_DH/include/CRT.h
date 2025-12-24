//
// Created by Jabir on 12/23/2025.
//

#ifndef CRYPTOGRAPHY_CRT_H
#define CRYPTOGRAPHY_CRT_H
#include <vector>
using ll=long long;
struct Eq
{
    ll a;
    ll m;
};

ll crt(const std::vector<Eq>& equations);

#endif //CRYPTOGRAPHY_CRT_H
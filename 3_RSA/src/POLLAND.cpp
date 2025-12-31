//
// Created by Jabir on 12/31/2025.
//

#include "../include//POLLAND.h"

#include <numeric>

#include "../../1_An_Introduction_To_Cryptography/include/Tools.h"
std::pair<bool, std::pair<ull, ull>> break_rsa_polland(ull N, ull a, int n)
{
    for (int i=2; i <= n; i++)
    {
        a = fast_exponentiation(a, i, N);
        ull d = std::gcd(a-1, N);
        if (d==N) return {false, {0,0}};
        if (d!=1) return {true, {d, N/d}};
    }
    return {false, {0,0}};
};
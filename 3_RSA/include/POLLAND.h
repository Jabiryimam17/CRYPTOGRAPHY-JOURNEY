//
// Created by Jabir on 12/31/2025.
//

#ifndef CRYPTOGRAPHY_POLLAND_H
#define CRYPTOGRAPHY_POLLAND_H
#include <utility>
using ull=unsigned long long;

std::pair<bool, std::pair<ull, ull>> break_rsa_polland(ull N, ull A, int n);
#endif //CRYPTOGRAPHY_POLLAND_H
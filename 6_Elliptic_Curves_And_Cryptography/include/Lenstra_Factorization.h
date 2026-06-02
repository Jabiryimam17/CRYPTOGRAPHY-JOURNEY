//
// Created by Jabir on 2/2/2026.
//

#ifndef CRYPTOGRAPHY_LENSTRA_FACTORIZATION_H
#define CRYPTOGRAPHY_LENSTRA_FACTORIZATION_H
#include <utility>

#include "Elliptic_Curve_Group.h"
#include <openssl/rand.h>
std::pair<ull,ull> lenstra_factorization(ull N);
ull fill_random(ull p);
std::pair<bool, Point> add_point(Point P, Point Q, E_Group E);
#endif //CRYPTOGRAPHY_LENSTRA_FACTORIZATION_H
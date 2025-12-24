//
// Created by Jabir on 12/23/2025.
//

#ifndef CRYPTOGRAPHY_SHANK_ALGORITHM_H
#define CRYPTOGRAPHY_SHANK_ALGORITHM_H
#include <vector>
#include "../../Data_Structures//include/Group.h"
#include "../../1_An_Introduction_To_Cryptography//include/Tools.h"
using ull=unsigned long long;

class SHANK // general shank bruteforce for any group
{
    public:
    G p;

    std::vector<std::pair<ull,G>> g_subgroup, h_coset_g_inverse;
    SHANK(G _p);
    ull solve_dhp(G g, G h, unsigned long long N);

};

class POHLIG_HELLMAN_SHANK /// specialized for pohlig hellman breaker since it reused g many times
{
public:
    G p;
    G g;
    G u_i;
    ull q{},e{};
    ull N;
    std::vector<std::pair<ull, G>> g_subgroup, h_coset_g_inverse;
    POHLIG_HELLMAN_SHANK();
    void prepare(G _g, G _p, ull _q, ull _e);
    void update(G h);
    ull solve_dhp(G h);

};

#endif //CRYPTOGRAPHY_SHANK_ALGORITHM_H
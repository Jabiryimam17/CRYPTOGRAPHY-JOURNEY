//
// Created by Jabir on 1/19/2026.
//

#ifndef CRYPTOGRAPHY_POLLARDS_ALGORITHM_H
#define CRYPTOGRAPHY_POLLARDS_ALGORITHM_H
#include "../include//solve_linear_equation.h"
ull pollard_algorithm(ull g, ull h, ull p);
std::pair<ull, ull> find_match(ull g, ull h, ull p);

std::tuple<ull, ull, ull> travel_orbit(ull x, ull g, ull h, ull p, ull e_g, ull e_h);
#endif //CRYPTOGRAPHY_POLLARDS_ALGORITHM_H
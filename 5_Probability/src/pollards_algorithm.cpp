//
// Created by Jabir on 1/19/2026.
//


#include "../include/pollards_algorithm.h"

#include <tuple>

ull pollard_algorithm(ull g, ull h, ull p)
{
    auto [u,v] = find_match(g, h, p);
    ull x = solve_linear_equation(u, v, g, h, p);
    return x;
}

std::pair<ull, ull> find_match(ull g, ull h, ull p)
{
    ull g_s = 0, g_d = 0, h_s = 0, h_d = 0;
    ull x = 1, y = 1;
    do
    {
        std::tie(x, g_s, h_s) = travel_orbit(x, g, h, p, g_s, h_s);
        std::tie(y, g_d, h_d) = travel_orbit(y, g, h, p, g_d, h_d);
        std::tie(y, g_d, h_d) = travel_orbit(y, g, h, p, g_d, h_d);
    }
    while (x != y);
    return {(g_s - g_d + p - 1) % (p - 1), (h_d - h_s + p - 1) % (p - 1)};
};


std::tuple<ull, ull, ull> travel_orbit(ull x, ull g, ull h, ull p, ull e_g, ull e_h)
{
    if (x < p / 3) x = x * g % p, e_g = (e_g + 1) % (p - 1);
    else if (x >= 2 * p / 3) x = x * h % p, e_h = (e_h + 1) % (p - 1);
    else x = x * x % p, e_h = e_h * 2 % (p - 1), e_g = e_g * 2 % (p - 1);
    return {x, e_g, e_h};
}

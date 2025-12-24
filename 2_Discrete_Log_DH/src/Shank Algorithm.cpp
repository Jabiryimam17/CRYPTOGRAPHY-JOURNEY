//
// Created by Jabir on 12/23/2025.
//

#include "../include//Shank Algorithm.h"
#include <cmath>
#include <algorithm>
#include <iostream>



using ull=unsigned long long;
SHANK::SHANK(G _p) : p(_p) {}

ull SHANK::solve_dhp(G g, G h, ull N)
{
    g_subgroup.clear();
    h_coset_g_inverse.clear();
    ull n=static_cast<ull>(sqrt(N))+1;
    g_subgroup.emplace_back(0,g);
    h_coset_g_inverse.emplace_back(0,h);

    G u = G::mod_pow(g, G(p.v - 1 - n), p); // p must be prime here otherwise use extended euclidian algorithm

    g_subgroup.reserve(n+1), h_coset_g_inverse.reserve(n+1);
    for (ull i=1; i <= n; i++)
    {
        g_subgroup.emplace_back(i,g_subgroup[i-1].second*g%p);
        h_coset_g_inverse.emplace_back(i, h_coset_g_inverse[i-1].second*u%p);
    }
    std::sort(g_subgroup.begin(), g_subgroup.end(),[](const auto& a, const auto& b)
    {
        if (!(a.second==b.second)) return a.second < b.second;
        return a.first < b.first;
    });
    std::sort(h_coset_g_inverse.begin(), h_coset_g_inverse.end(),[](const auto& a, const auto& b)
    {
        if (!(a.second==b.second)) return a.second < b.second;
        return a.first < b.first;
    });
    int i=0,j=0;
    while (i <= n && j <= n)
    {
        if (g_subgroup[i].second==h_coset_g_inverse[j].second) return g_subgroup[i].first+1+(h_coset_g_inverse[j].first*n);
        if (g_subgroup[i].second < h_coset_g_inverse[j].second) i++;
        else j++;
    }
    return 0;
}


POHLIG_HELLMAN_SHANK::POHLIG_HELLMAN_SHANK():p(0), g(0), N(0), u_i(0)
{

}

void POHLIG_HELLMAN_SHANK::prepare(G _g, G _p, ull _q, ull _e)
{
    g = _g,p = _p,q = _q,e = _e;

    u_i = G::mod_pow(g, G(q-N), p);
    g_subgroup.clear(), h_coset_g_inverse.clear();
    N=static_cast<ull>(sqrt(static_cast<double>(_q)));
    g_subgroup.reserve(N+1), h_coset_g_inverse.reserve(N+1);
    g_subgroup.emplace_back(0,_g);
    for (ull i=1; i <= N; i++) g_subgroup.emplace_back(i,g_subgroup[i-1].second*_g%p);
    std::sort(g_subgroup.begin(), g_subgroup.end(),[](const auto& a, const auto& b)
    {
        if (!(a.second==b.second)) return a.second < b.second;
        return a.first < b.first;
    });
}

void POHLIG_HELLMAN_SHANK::update(G h)
{
    h_coset_g_inverse.emplace_back(0, h);

    for (ull i=1; i <= N; i++) h_coset_g_inverse.emplace_back(i, h_coset_g_inverse[i-1].second*u_i%p);
    std::sort(h_coset_g_inverse.begin(), h_coset_g_inverse.end(),[](const auto& a, const auto& b)
    {
        if (!(a.second==b.second)) return a.second < b.second;
        return a.first < b.first;
    });
}

ull POHLIG_HELLMAN_SHANK::solve_dhp(G h)
{
    update(h);
    int i=0,j=0;
    while (i <= N && j <= N)
    {
        if (g_subgroup[i].second==h_coset_g_inverse[j].second) return g_subgroup[i].first+1+(h_coset_g_inverse[j].first*N);
        if (g_subgroup[i].second < h_coset_g_inverse[j].second) i++;
        else j++;
    }
    return p.v+1;
}





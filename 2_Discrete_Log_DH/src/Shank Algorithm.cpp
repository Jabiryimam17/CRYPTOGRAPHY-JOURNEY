//
// Created by Jabir on 12/23/2025.
//

#include "../include//Shank Algorithm.h"
#include <cmath>
#include <algorithm>
#include <iostream>

G::G() : v(0) {}
G::G(ull v):v(v){}

G G::operator*(G r) const
{
    return G(v*r.v);
}
bool G::operator>(G r) const
{
    return v > r.v;
}

bool G::operator<(G r) const
{
    return v < r.v;
}

G G::operator&(G r) const {
    return G(v & r.v);
}

G G::operator>>(G r) const
{
    return G(v >> r.v);
}

G G::operator%(G r) const
{
    return G(v%r.v);
}

bool G::operator==(G r) const
{
    return v == r.v;
}

using ull=unsigned long long;
SHANK::SHANK(G _p) : p(_p) {}

ull SHANK::solve_dhp(G g, G h, ull N)
{
    g_generated.clear();
    h_g_inverse_generated.clear();
    ull n=static_cast<ull>(sqrt(N))+1;
    g_generated.emplace_back(0,g);
    h_g_inverse_generated.emplace_back(0,h);

    G u = mod_pow(g, G(p.v - 1 - n), p);

    g_generated.reserve(n+1), h_g_inverse_generated.reserve(n+1);
    for (ull i=1; i <= n; i++)
    {
        g_generated.emplace_back(i,g_generated[i-1].second*g%p);
        h_g_inverse_generated.emplace_back(i, h_g_inverse_generated[i-1].second*u%p);
    }
    std::sort(g_generated.begin(), g_generated.end(),[](const auto& a, const auto& b)
    {
        if (!(a.second==b.second)) return a.second < b.second;
        return a.first < b.first;
    });
    std::sort(h_g_inverse_generated.begin(), h_g_inverse_generated.end(),[](const auto& a, const auto& b)
    {
        if (!(a.second==b.second)) return a.second < b.second;
        return a.first < b.first;
    });
    int i=0,j=0;
    while (i <= n && j <= n)
    {
        if (g_generated[i].second==h_g_inverse_generated[j].second) return g_generated[i].first+1+(h_g_inverse_generated[j].first*n);
        if (g_generated[i].second < h_g_inverse_generated[j].second) i++;
        else j++;
    }
    return 0;
}

G SHANK::mod_pow(G b, G e, G mod)
{
    G res(1);

    while (e > G(0))
    {
        if ((e & G(1))==G(1)) res = (res * b) % mod;

        b = (b * b) % mod;
        e = e >> G(1);
    }
    return res;
}


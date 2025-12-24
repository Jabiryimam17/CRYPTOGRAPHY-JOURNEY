//
// Created by Jabir on 12/24/2025.
//
#include "../include//Group.h"
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
G G::mod_pow(G b, G e, G mod)
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
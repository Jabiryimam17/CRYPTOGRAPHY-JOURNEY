//
// Created by Jabir on 12/22/2025.
//
#include "../include//Tools.h"
using ull=unsigned long long;
ull fast_exponentiation(ull b, ull e, ull MOD)
{
    ull res=1;
    b %=MOD;
    while (e != 0)
    {
        if (e&1) res = (res*b)%MOD;
        b = (b*b)%MOD;
        e >>=1;
    }
    return res;
}

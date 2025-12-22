//
// Created by Jabir on 12/22/2025.
//
#include "../include//Tools.h"

unsigned long long fast_exponentiation(unsigned long long b, unsigned long long e, unsigned long long MOD)
{
    unsigned long long res=1;
    b %=MOD;
    while (e != 0)
    {
        if (e&1) res = (res*b)%MOD;
        b = (b*b)%MOD;
        e >>=1;
    }
    return res;
}

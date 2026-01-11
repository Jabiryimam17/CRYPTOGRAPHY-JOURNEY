//
// Created by Jabir on 1/11/2026.
//


#include "../include/TONELLI_SHANKS.h"

ull tonelli_shanks(ull n, ull p)
{
    ull z;
    do {
        RAND_bytes(reinterpret_cast<unsigned char*>(&z), sizeof(z));
        z %= p;
    } while (z == 0 || fast_exponentiation(z, (p - 1) / 2, p) != p - 1);
    ull q = p - 1, s = 0;
    while (q % 2 == 0) s++, q /= 2;
    ull r = fast_exponentiation(n, (q + 1) / 2, p);
    ull t = fast_exponentiation(n, q, p);
    ull c=fast_exponentiation(z, q, p);
    ull m= s;
    while (m!=1)
    {
        int i=determine_order_pow(t, m, p);
        ull exp = 1;
        exp <<= (m - i - 1);
        ull b = fast_exponentiation(c, exp, p);
        r = r*b%p;
        c = b*b%p;
        t = t*c%p;
        m=i;
    }
    return r;
}

ull determine_order_pow(ull t, ull m, ull p)
{
    for (int i=1; i<m; i++)
    {
        t = (t*t)%p;
        if (t==1) return i;
    }
    return -1;
}

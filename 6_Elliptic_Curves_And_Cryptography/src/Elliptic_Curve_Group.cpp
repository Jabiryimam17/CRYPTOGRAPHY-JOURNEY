//
// Created by Jabir on 2/1/2026.
//


#include "../include/Elliptic_Curve_Group.h"
#include <stdexcept>


/* ---------- helpers ---------- */

static ull mod_mul(ull a, ull b, ull p)
{
    __int128 r = (__int128)a * b;
    return (ull)(r % p);
}

// static ull mod_pow(ull a, ull e, ull p)
// {
//     ull res = 1 % p;
//     a %= p;
//     while (e)
//     {
//         if (e & 1) res = mod_mul(res, a, p);
//         a = mod_mul(a, a, p);
//         e >>= 1;
//     }
//     return res;
// }


E_Group::E_Group(ull A, ull B, ull p)
    : A((A+p) % p), B((B+p) % p), p(p), O(INF, INF)
{
    // short Weierstrass form requires char(F) != 2,3
    if (p <= 3)
        throw std::invalid_argument("Invalid field characteristic");


    ull disc =
        (mod_mul(4, mod_mul(A, mod_mul(A, A, p), p), p) +
         mod_mul(27, mod_mul(B, B, p), p)) % p;

    if (disc == 0)
        throw std::invalid_argument("Singular curve");
}


Point E_Group::add_point(Point P, Point Q) const
{
    if (!check_sol(P) || !check_sol(Q))
        throw std::invalid_argument("Point not on curve");

    if (P == O) return Q;
    if (Q == O) return P;

    // P + (-P) = O
    if (P.x == Q.x && (P.y + Q.y) % p == 0)
        return O;

    ull m;

    if (P == Q)
    {
        if (P.y == 0)
            return O;

        ull num = (mod_mul(3, mod_mul(P.x, P.x, p), p) + A) % p;
        ull den = (extended_euclidean_algorithm((long long)p, (long long)((2*P.y)%p)).second+p)%p;
        // ull den = mod_pow((2 * P.y) % p, p - 2, p);
        m = mod_mul(num, den, p);
    }
    else
    {
        ull num = (Q.y + p - P.y) % p;
        ull den = (Q.x + p - P.x) % p;
        ull inv = (extended_euclidean_algorithm((long long)p, (long long)den).second+p)%p;
        // ull inv = mod_pow(den, p - 2, p);
        m = mod_mul(num, inv, p);
    }

    ull x = (mod_mul(m, m, p) + p - P.x + p - Q.x) % p;
    ull y = (mod_mul(m, (P.x + p - x) % p, p) + p - P.y) % p;

    return {x, y};
}

Point E_Group::sub_point(Point P, Point Q) const
{
    if (Q!=O) Q.y = (p-Q.y)%p;
    return add_point(P, Q);
}

bool E_Group::check_sol(const Point& P) const
{
    if (P == O) return true;

    ull x = P.x % p;
    ull y = P.y % p;

    ull left  = mod_mul(y, y, p);
    ull right = (mod_mul(x, mod_mul(x, x, p), p) + mod_mul(A, x, p) + B) % p;

    return left == right;
}


Point E_Group::scalar_mul(Point P, ull e) const
{
    Point res=O;
    while (e)
    {
        if (e&1) res = add_point(res, P);
        P = add_point(P,P);
        e >>=1;
    }
    return res;
}

Point E_Group::scalar_mul_NAF(Point P, ull e) const
{
    if (!check_sol(P)) throw std::invalid_argument("Point not on curve");
    Point res=O;
    ull acc=0;
    Point S=P;
    while (e || acc)
    {
        if (e&1) acc = (acc << 1)+1;
        else if (acc%2==1)
        {
            if (acc==1) res = add_point(res, S);
            else
            {
                if (S!=O) S.y = (p-S.y)%p;
                res = add_point(add_point(res,P),S);
            }
        }
        P = add_point(P, P);
        if ((e&1)==0)  S=P, acc=0;
        e >>= 1;
    }
    return res;
}






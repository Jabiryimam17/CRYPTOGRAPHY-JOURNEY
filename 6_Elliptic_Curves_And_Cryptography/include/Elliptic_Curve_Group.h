//
// Created by Jabir on 2/1/2026.
//

#ifndef CRYPTOGRAPHY_ELLIPTIC_CURVE_GROUP_H
#define CRYPTOGRAPHY_ELLIPTIC_CURVE_GROUP_H
#include <limits.h>
using ull= long long;
const ull INF=LLONG_MAX;
struct Point
{
    ull x;
    ull y;
    bool operator==(const Point&p) const
    {
        return x==p.x && y==p.y;
    }
};
class E_Group
{
public:
    ull A;
    ull B;
    ull p;
    Point O;
    E_Group(ull A, ull B, ull p);
    Point add_point(Point P, Point Q) const;
    bool check_sol(const Point& P) const;

    Point scalar_mul(Point P, ull e) const;
    Point scalar_mul_NAF(Point P, ull e) const;
};
#endif //CRYPTOGRAPHY_ELLIPTIC_CURVE_GROUP_H
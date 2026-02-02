//
// Created by Jabir on 2/2/2026.
//


#include "../include/Elliptic_ELGAMAL.h"

#include <stdexcept>

ELGAMAL::ELGAMAL(E_Group E, Point P):E(E), P(P)
{
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(& a), sizeof(a));
        a %= E.p;
    } while (a==0);
    Q_A = E.scalar_mul_NAF(P, a);
}

std::pair<Point, Point> ELGAMAL::encrypt(Point M, Point Q)
{
    if (!E.check_sol(Q) || Q == E.O)
        throw std::invalid_argument("Invalid public key");
    ull k;
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&k), sizeof(k));
        k %= E.p;
    } while (k==0);
    Point S=E.scalar_mul_NAF(P, k);
    Point R=E.add_point(M, E.scalar_mul_NAF(Q, k));
    return {S, R};
}

Point ELGAMAL::decrypt(Point S, Point R)
{
    if (!E.check_sol(S) || S == E.O)
        throw std::invalid_argument("Invalid ciphertext");
    return E.sub_point(R, E.scalar_mul_NAF(S, a));
}




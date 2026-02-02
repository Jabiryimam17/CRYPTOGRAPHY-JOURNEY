//
// Created by Jabir on 2/2/2026.
//

#ifndef CRYPTOGRAPHY_ELLIPTIC_ELGAMAL_H
#define CRYPTOGRAPHY_ELLIPTIC_ELGAMAL_H
#include <utility>

#include "../include/Elliptic_Curve_Group.h"
#include <openssl/rand.h>
class ELGAMAL
{
public:
    E_Group E;
    Point P;
    ull a;
    Point Q_A;
    ELGAMAL(E_Group E, Point P);
    std::pair<Point,Point> encrypt(Point M, Point Q);
    Point decrypt(Point S, Point R);



};
#endif //CRYPTOGRAPHY_ELLIPTIC_ELGAMAL_H
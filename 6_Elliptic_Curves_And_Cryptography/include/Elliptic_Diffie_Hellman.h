//
// Created by Jabir on 2/2/2026.
//

#ifndef CRYPTOGRAPHY_ELLIPTIC_DIFFIE_HELLMAN_H
#define CRYPTOGRAPHY_ELLIPTIC_DIFFIE_HELLMAN_H
#include "Elliptic_Curve_Group.h"
#include  <openssl/rand.h>

class CS_DH
{
public:
    Point P;
    E_Group E;
    ull a;
    CS_DH(E_Group E, Point P);
    Point compute_public_key();
    Point compute_private_key(Point Q_B) const;
};
#endif //CRYPTOGRAPHY_ELLIPTIC_DIFFIE_HELLMAN_H
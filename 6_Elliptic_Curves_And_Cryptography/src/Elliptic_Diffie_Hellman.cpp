//
// Created by Jabir on 2/2/2026.
//

#include "../include/Elliptic_Diffie_Hellman.h"

#include <iostream>
#include <stdexcept>


CS_DH::CS_DH(E_Group E, Point P):E(E), P(P), a(0)
{

}

Point CS_DH::compute_public_key()
{
    do
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&a),sizeof(a));
        a %= E.p;
    } while (a==0);
    return E.scalar_mul_NAF(P, a);
}

Point CS_DH::compute_private_key(Point Q_B) const
{
    if (!E.check_sol(Q_B) || Q_B == E.O) throw std::invalid_argument("Invalid public key");
    return E.scalar_mul_NAF(Q_B, a);
}



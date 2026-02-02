//
// Created by Jabir on 2/2/2026.
//

#ifndef CRYPTOGRAPHY_ELLIPTIC_DSA_H
#define CRYPTOGRAPHY_ELLIPTIC_DSA_H
#include "Elliptic_Curve_Group.h"
#include "../../1_An_Introduction_To_Cryptography//include/Tools.h"
struct SIGNED_MESSAGE
{
    ull m;
    ull r;
    ull s;
    Point A;
    Point G;
    ull q;
    E_Group E;
};
class E_DSA
{
public:
    static SIGNED_MESSAGE sign_message(Point G, E_Group E, ull q, ull m);
    static bool verify_signature(SIGNED_MESSAGE sig);
};
#endif //CRYPTOGRAPHY_ELLIPTIC_DSA_H
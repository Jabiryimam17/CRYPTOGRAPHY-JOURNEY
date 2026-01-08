//
// Created by Jabir on 1/8/2026.
//

#ifndef CRYPTOGRAPHY_ELGAMAL_SIGNATURE_H
#define CRYPTOGRAPHY_ELGAMAL_SIGNATURE_H
#include <utility>
#include <openssl/rand.h>
#include  "../../2_Discrete_Log_DH/include/GENERATE_ROOT.h"
#include <cmath>
#include "../../1_An_Introduction_To_Cryptography//include/EEA.h"
using ull = unsigned long long;

struct SIGNED_MESSAGE
{
    ull m;
    std::pair<ull,ull> s;
};
class ELGAMAL_SIGNATURE
{
public:
    ull a;
    ull g;
    ull p;
    ELGAMAL_SIGNATURE(ull _p);
    SIGNED_MESSAGE sign_message(ull m);
    bool verify_message(SIGNED_MESSAGE s_m, ull g, ull A, ull p);

};
#endif //CRYPTOGRAPHY_ELGAMAL_SIGNATURE_H
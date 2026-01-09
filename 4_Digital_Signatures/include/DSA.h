//
// Created by Jabir on 1/8/2026.
//

#ifndef CRYPTOGRAPHY_DSA_H
#define CRYPTOGRAPHY_DSA_H
#include <openssl/rand.h>
#include "../../1_An_Introduction_To_Cryptography/include/Tools.h"
#include "../../1_An_Introduction_To_Cryptography/include/EEA.h"
#include "../../3_RSA/include/Tools.h"
#include "../../2_Discrete_Log_DH/include/GENERATE_ROOT.h"
using ull=unsigned long long;
struct SIGNED_MESSAGE
{
    ull m;
    ull r;
    ull s;
};
class DSA_CUSTOM
{
public:
    ull p;
    ull q;
    ull a;
    ull g;
    DSA_CUSTOM();
    SIGNED_MESSAGE sign_message(ull m);
    bool verify_message(SIGNED_MESSAGE s_m, ull g, ull A, ull q, ull p);

};
#endif //CRYPTOGRAPHY_DSA_H
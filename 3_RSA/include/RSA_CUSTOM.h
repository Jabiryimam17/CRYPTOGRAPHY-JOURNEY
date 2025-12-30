//
// Created by Jabir on 12/29/2025.
//

#ifndef CRYPTOGRAPHY_RSA_H
#define CRYPTOGRAPHY_RSA_H
#include ".//Tools.h"


using ull=unsigned long long;
class RSA_CUSTOM: public miller_rabin_test
{
    public:
    ull p,q,N, e, d;
    RSA_CUSTOM();
    static ull encrypt(ull m, ull o_N, ull o_e);
    ull decrypt(ull c) const;
};
#endif //CRYPTOGRAPHY_RSA_H
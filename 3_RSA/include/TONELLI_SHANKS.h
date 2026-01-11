//
// Created by Jabir on 1/11/2026.
//

#ifndef CRYPTOGRAPHY_TONELLI_SHANKS_H
#define CRYPTOGRAPHY_TONELLI_SHANKS_H
#include  <openssl/rand.h>
#include "../../1_An_Introduction_To_Cryptography/include/Tools.h"
ull tonelli_shanks(ull n, ull p);
ull determine_order_pow(ull t, ull m, ull p);
#endif //CRYPTOGRAPHY_TONELLI_SHANKS_H
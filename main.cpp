

#include <cassert>
#include <iostream>

#include "3_RSA/include/Tools.h"
#include "4_Digital_Signatures/include/DSA.h"

int main()
{


    DSA_CUSTOM dsa = DSA_CUSTOM();
    auto sig = dsa.sign_message(587);
    ull A = fast_exponentiation(dsa.g, dsa.a, dsa.p); // public key
    bool verified = dsa.verify_message(sig, dsa.g, A, dsa.q, dsa.p);
    std::cout << (verified ? "VERIFIED!!!" : "FAILED!!!") << std::endl;

    return 0;
}

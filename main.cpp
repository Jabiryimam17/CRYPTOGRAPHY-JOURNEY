

#include <iostream>
#include "4_Digital_Signatures/include/ELGAMAL_SIGNATURE.h"
int main()
{

    ELGAMAL_SIGNATURE sig(6961); // small prime
    bool ok = sig.verify_message({1614,{2709, 2994}}, 437, 4250, 6961);
    std::cout << (ok ? "Verified!" : "Failed") << std::endl;
    return 0;
}

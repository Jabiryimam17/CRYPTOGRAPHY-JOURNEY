

#include <iostream>
#include "./4_Digital_Signatures/include/DSA.h"
int main()
{

    DSA_CUSTOM dsa = DSA_CUSTOM(48731, 443, 242,5260);
    auto sig=dsa.sign_message(343);
    auto ok = dsa.verify_message(sig, 5260, 3438, 443,48731);
    std::cout << (ok?"Verified!":"Failed!");

    return 0;
}

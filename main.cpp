

#include <iostream>
#include "./4_Digital_Signatures/include/DSA.h"
int main()
{

    DSA_CUSTOM dsa = DSA_CUSTOM(22531, 751, 674,4488);
    auto sig=dsa.sign_message(244);
    auto ok = dsa.verify_message({432,211, 97}, 4488, 22476, 751,22531);
    std::cout << (ok?"Verified!":"Failed!");

    return 0;
}

#include <vector>
#include <iostream>
#include "./6_Elliptic_Curves_And_Cryptography//include/Elliptic_DSA.h"

int main()
{
    E_Group A = E_Group(231, 473, 17389);
    Point P = {920, 303};
    Point G={11259,11278};
    auto sig = E_DSA::sign_message(G, A, 1321,644);

    std::cout << std::boolalpha;
    sig = {993, 907, 296, {11017,14637}, G, 1321, A};
    std::cout << (E_DSA::verify_signature(sig));
    return 0;
};

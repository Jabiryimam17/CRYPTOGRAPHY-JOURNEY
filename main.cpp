#include <vector>
#include <iostream>
#include "./6_Elliptic_Curves_And_Cryptography//include/Elliptic_Diffie_Hellman.h"

int main()
{
    E_Group A = E_Group(324, 1287, 3851);
    Point P = {920, 303};
    CS_DH D_A = CS_DH(A, P), D_B = CS_DH(A, P);
    auto [x_a, y_a] = D_A.compute_public_key();
    auto [x_b, y_b] = D_B.compute_public_key();
    auto S_A = D_A.compute_private_key({x_b, y_b});
    auto S_B = D_B.compute_private_key({x_a, y_a});
    std::cout << std::boolalpha;
    std::cout << (S_A==S_B) << std::endl;

    std::cout << x_a << ":" << y_a << std::endl;
    return 0;
};

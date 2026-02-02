#include <vector>
#include <iostream>
#include "./6_Elliptic_Curves_And_Cryptography//include/Elliptic_Curve_Group.h"
int main()
{
    E_Group A=E_Group(1541, 1335,3221);
    auto [x,y]=A.scalar_mul_NAF({2898,439}, 3211);

    std::cout << x << ":" << y << std::endl;
    return 0;
};

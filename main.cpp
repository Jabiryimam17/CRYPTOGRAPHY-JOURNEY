


#include "./2_Discrete_Log_DH//include//Shank Algorithm.h"
#include <iostream>
#include "./1_An_Introduction_To_Cryptography//include/Tools.h"
int main() {
    ull p = 17389;
    ull g=9704;
    ull h=13896;

    SHANK breaker=SHANK(G(p));
    ull x =breaker.solve_dhp(G(g), G(h), 1242);
    std::cout << x << std::endl;
    std::cout << (fast_exponentiation(g, x, p) == h?"YES":"NO");



    return 0;
}

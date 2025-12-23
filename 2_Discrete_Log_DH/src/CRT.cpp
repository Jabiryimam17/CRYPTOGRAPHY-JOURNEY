//
// Created by Jabir on 12/23/2025.
//

#include "../include/CRT.h"
#include "../../1_An_Introduction_To_Cryptography/include/Tools.h"
ull crt(const std::vector<Eq>& equations)
{
    ull prefix_mpro=1;
    ull sol=0;
    for (auto& eq:equations)
    {
        ull prefix_m_pro_inverse = fast_exponentiation(prefix_mpro,eq.m-2, eq.m); // use this only if p is prime otherwise use extended euclidean algorithim
        ull  y = (eq.a+eq.m-sol%eq.m)*prefix_m_pro_inverse%eq.m;
        sol = (prefix_mpro*y + sol);
        prefix_mpro = prefix_mpro*eq.m;
    };
    return sol;
}

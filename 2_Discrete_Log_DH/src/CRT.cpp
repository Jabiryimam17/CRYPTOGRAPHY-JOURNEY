//
// Created by Jabir on 12/23/2025.
//

#include "../include/CRT.h"
#include "../../1_An_Introduction_To_Cryptography//include/EEA.h"
long long crt(const std::vector<Eq>& equations)
{
    long long pm_pro = 1;
    long long sol = 0;
    for (auto& eq : equations)
    {
        long long inv = extended_euclidean_algorithm(eq.m, pm_pro % eq.m).second;
        inv = (inv % eq.m + eq.m) % eq.m;

        long long y = (eq.a - sol % eq.m + eq.m) % eq.m * inv % eq.m;
        sol = sol + pm_pro * y;
        pm_pro = pm_pro * eq.m;
    }
    return sol;
}

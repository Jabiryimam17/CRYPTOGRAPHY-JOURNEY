


#include "./2_Discrete_Log_DH//include/POHLIG_HELLMAN.h"
#include <iostream>

int main()
{
    std::vector<Eq> equations{{2,3},{3,7}, {4, 16}};
    std::cout << crt(equations) << std::endl;
    G p(11251);
    POHLIG_HELLMAN solver=POHLIG_HELLMAN(p);
    ull sol=solver.solve_dhp(G(23), G(9689), 11250);
    std::cout << sol << std::endl;



    return 0;
}

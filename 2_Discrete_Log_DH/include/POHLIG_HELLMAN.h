//
// Created by Jabir on 12/24/2025.
//

#ifndef CRYPTOGRAPHY_POHLIG_HELLMAN
#define CRYPTOGRAPHY_POHLIG_HELLMAN
#include "../../Data_Structures/include//Group.h"
#include  "../../2_Discrete_Log_DH//include/Shank Algorithm.h"
#include "../../2_Discrete_Log_DH//include/CRT.h"
class POHLIG_HELLMAN
{
public:
    G p;
    G h;
    G g;
    ull N;
    POHLIG_HELLMAN_SHANK dlp_bruteforce;
    std::vector<std::pair<ull,std::pair<ull,ull>>> prime_factors;
    std::vector<Eq> equations;
    void factorize(ull _N);
    ull solve_dhp(G _g, G _h, ull _N);
    ull solve_dhp_factor(G _g, G _h, ull q_pow, ull q, ull e);

};
#endif //CRYPTOGRAPHY_POHLIG_HELLMAN
//
// Created by Jabir on 2/2/2026.
//


#include "../include/Lenstra_Factorization.h"

std::pair<ull, ull> lenstra_factorization(ull N)
{
    ull A=fill_random(N), a=fill_random(N), b=fill_random(N);
    ull B = (b*b%N-a*a*a%N-A*a%N)%N;
    E_Group E = E_Group(A, B, N);



}

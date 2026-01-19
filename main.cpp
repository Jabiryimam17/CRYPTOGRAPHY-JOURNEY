#include <bitset>
#include <vector>
#include <iostream>


#include "5_Probability/include/pollards_algorithm.h"

int main()
{
    ull x=pollard_algorithm(29,5953042, 15239131);
    // x = solve_linear_equation(13974, 19110, 11, 41387, 81799);
    std::cout << x << std::endl;

    return 0;
}

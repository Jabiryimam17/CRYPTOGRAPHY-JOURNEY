


#include "./2_Discrete_Log_DH//include//CRT.h"
#include <iostream>

int main()
{
    std::vector<Eq> equations{{2,3},{3,7}, {4, 16}};
    std::cout << crt(equations) << std::endl;

    return 0;
}



#include "3_RSA/include/Tools.h"
#include <iostream>

int main()
{

    miller_rabin_test test=miller_rabin_test();
    std::cout << test.random_prime_generator(5) << std::endl;
    return 0;
}

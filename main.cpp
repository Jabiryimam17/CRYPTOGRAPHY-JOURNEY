

#include <iostream>
#include  "3_RSA/include/POLLAND.h"

int main()
{

    auto [success, primes] = break_rsa_polland(13927189,2, 100);
    std::cout << success << primes.first << ":" << primes.second << std::endl;
    return 0;
}

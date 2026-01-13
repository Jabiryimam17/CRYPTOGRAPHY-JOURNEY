#include <bitset>
#include <vector>
#include <iostream>
#include "3_RSA/include/FACTORIZATION.h"

int main()
{
    ull p = miller_rabin_test::random_prime_generator(10);
    ull q = miller_rabin_test::random_prime_generator(10);
    std::cout << p << " : " << q << std::endl;
    RSA_FACTORIZATION rsa_breaker;
    ull calc_p=rsa_breaker.factorize(p*q);
    std::cout << std::boolalpha;
    std::cout << (p==calc_p || q==calc_p) << std::endl;
    return 0;
}

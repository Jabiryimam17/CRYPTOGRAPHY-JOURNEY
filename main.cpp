


#include "./2_Discrete_Log_DH/include/ELGAMAL.h"
#include <iostream>

int main() {
    // ull p = 4294967311ULL; // example small prime < 2^64
    ull p = 1e9+7;
    ull g = 2;

    ELGAMAL el(g, p);

    ull message = 100000;
    auto [c, d] = el.encrypt(message, el.public_key);
    ull decrypted = el.decrypt(c, d);

    std::cout << "Original: " << message << "\n";
    std::cout << "Decrypted: " << decrypted << "\n";

    return 0;
}

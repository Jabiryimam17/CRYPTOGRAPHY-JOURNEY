


#include <openssl/rand.h>
#include <iostream>

int main() {
    unsigned char buf[100];

    if (RAND_bytes(buf, 10) != 1) {
        std::cerr << "OpenSSL RNG failed\n";
        return 1;
    }

    for (unsigned char b : buf) {
        std::cout << (int)b << " ";
    }
    std::cout << "\n";

    return 0;
}

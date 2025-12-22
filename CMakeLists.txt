cmake_minimum_required(VERSION 4.1)
project(cryptography)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
set(OPENSSL_USE_STATIC_LIBS OFF)
find_package(OpenSSL REQUIRED)
add_executable(cryptography
        main.cpp
        "1 An Introduction To Cryptography/include/EEA.h"
        "1 An Introduction To Cryptography/src/EEA.cpp"
        "1 An Introduction To Cryptography/include/Tools.h"
        "1 An Introduction To Cryptography/src/Tools.cpp"
        "2 Discrete Logarithms and Diffie–Hellman/include/Diffie Hellman Key Exchange.h"
        "2 Discrete Logarithms and Diffie–Hellman/src/Diffie Hellman Key Exchange.cpp"
)

target_link_libraries( cryptography
        OpenSSL::SSL
        OpenSSL::Crypto
)

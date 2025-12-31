cmake_minimum_required(VERSION 4.1)
project(cryptography)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OPENSSL_ROOT_DIR "C:/msys64/mingw64")
set(OPENSSL_USE_STATIC_LIBS OFF)
find_package(OpenSSL REQUIRED)
file(GLOB CRYPTO_SRC
        "1_An_Introduction_To_Cryptography/src/*.cpp"
        "2_Discrete_Log_DH/src/*.cpp"
        "Data_Structures/src/*.cpp"
        "3_RSA/src/*.cpp"
)

file(GLOB CRYPTO_HDR
        "1_An_Introduction_To_Cryptography/include/*.h"
        "2_Discrete_Log_DH/include/*.h"
        "Data_Structures/include/*.h"
        "3_RSA/include/*.h"
)

add_executable(cryptography main.cpp ${CRYPTO_SRC})

target_link_libraries( cryptography
        OpenSSL::SSL
        OpenSSL::Crypto
)

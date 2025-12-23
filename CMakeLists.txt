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
)

file(GLOB CRYPTO_HDR
        "1_An_Introduction_To_Cryptography/include/*.h"
        "2_Discrete_Log_DH/include/*.h"
)

add_executable(cryptography main.cpp ${CRYPTO_SRC}
        2_Discrete_Log_DH/src/CRT.cpp)

target_link_libraries( cryptography
        OpenSSL::SSL
        OpenSSL::Crypto
)

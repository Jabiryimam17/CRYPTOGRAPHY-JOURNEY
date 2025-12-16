cmake_minimum_required(VERSION 4.1)
project(cryptography)

set(CMAKE_CXX_STANDARD 20)

add_executable(cryptography
        main.cpp
        "Number Theory/EEA.cpp")

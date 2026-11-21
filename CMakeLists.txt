
cmake_minimum_required(VERSION 3.20)

project(ECNT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#add_library(ecnt
#        src/polynomials/polynomial.cpp
#)

target_include_directories(ecnt PUBLIC include)

target_compile_options(ecnt PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

#add_executable(ecnt_demo
#        examples/basic_group_operations.cpp
#)

#target_link_libraries(ecnt_demo PRIVATE ecnt)

#enable_testing()

#add_executable(
#)
#test_polynomial
#        tests/polynomials/test_polynomial.cpp

#target_link_libraries(test_polynomial PRIVATE ecnt)

#add_test(NAME PolynomialTests COMMAND test_polynomial)


cmake_minimum_required(VERSION 3.20)

project(Polynomials
        VERSION 1.0.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
add_library(polynomials STATIC
        src/polynomials/polynomial.cpp
        include/ecnt/polynomials/polynomialmod.hpp
        src/polynomials/polynomialmod.cpp
        include/ecnt/polynomials/algorithms.hpp
        src/polynomials/algorithms.cpp
)

# Public headers
target_include_directories(polynomials
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Warnings for library implementation
target_compile_options(polynomials
        PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall;-Wextra;-Wpedantic>
)

# Tests
option(BUILD_TESTS "Build tests" OFF)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

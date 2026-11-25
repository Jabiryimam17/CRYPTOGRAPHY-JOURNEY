add_executable(polynomials_tests
        polynomials_tests.cpp
)

target_include_directories(polynomials_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(polynomials_tests
        PRIVATE
        polynomials
)

add_test(NAME polynomials_tests COMMAND polynomials_tests)

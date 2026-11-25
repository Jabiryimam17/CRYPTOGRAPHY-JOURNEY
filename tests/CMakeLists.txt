add_executable(polynomials_tests
        polynomials_tests.cpp
)

add_executable(elliptic_curves_tests
        elliptic_curves_tests.cpp
)

target_include_directories(polynomials_tests
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_link_libraries(polynomials_tests
        PRIVATE
        polynomials
)

target_link_libraries(elliptic_curves_tests
        PRIVATE
        polynomials
)

add_test(NAME polynomials_tests COMMAND polynomials_tests)
add_test(NAME elliptic_curves_tests COMMAND elliptic_curves_tests)


#pragma once
#include <vector>

#include "polynomial.hpp"
namespace ecnt {
    template<typename F>
class PolynomialMod {
    private:
        Polynomial<F> value;
        Polynomial<F> modulus;

    public:
        PolynomialMod(
            Polynomial<F> value,
            Polynomial<F> modulus
        );

        PolynomialMod(size_t n, Polynomial<F> modulus);

        PolynomialMod(F c, Polynomial<F> modulus);

        size_t degree() const;

        F evaluate(F c) const;

        PolynomialMod operator+(const PolynomialMod &rhs) const;

        PolynomialMod operator-(const PolynomialMod &rhs) const;

        PolynomialMod operator*(const PolynomialMod &rhs) const;

        PolynomialMod operator/(const PolynomialMod &rhs) const;

        PolynomialMod operator^(long long e) const;

        PolynomialMod operator*(const F s) const;

        PolynomialMod inverse() const;

        bool operator==(const PolynomialMod &rhs) const;
    };
}


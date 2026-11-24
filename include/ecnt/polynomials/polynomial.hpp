#pragma once
#include <vector>

namespace ecnt {
    template<typename F>
    class Polynomial {
    public:
        std::vector<F> coefficients;

        Polynomial() = default;

        explicit Polynomial(size_t n);

        explicit Polynomial(std::vector<F> coefs);

        explicit Polynomial(F c);

        size_t degree() const;

        F evaluate(F x) const;

        bool operator==(const Polynomial &rhs) const;

        Polynomial operator+(const Polynomial &rhs) const;

        Polynomial operator-(const Polynomial &rhs) const;

        Polynomial operator*(const Polynomial &rhs) const;

        Polynomial operator*(F s) const;

        Polynomial operator/(const Polynomial &rhs) const;

        Polynomial operator%(const Polynomial &rhs) const;

        Polynomial operator^(long long e) const;






        F operator[](size_t i) const;

        F &operator[](size_t i);
    };


}

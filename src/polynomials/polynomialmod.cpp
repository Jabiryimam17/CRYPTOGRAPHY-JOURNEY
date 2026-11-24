#include <ecnt/polynomials/polynomialmod.hpp>
#include <stdexcept>
#include <ecnt/polynomials/algorithms.hpp>

namespace ecnt {
    template<typename F>
    PolynomialMod<F>::PolynomialMod(Polynomial<F> value, Polynomial<F> modulus):value(value), modulus(modulus) {
        if (modulus==Polynomial<F>(F{0})) throw std::domain_error("Zero Polynomial Mod");
        this->value=this->value%this->modulus;
    }

    template<typename F>
    PolynomialMod<F>::PolynomialMod(size_t n, Polynomial<F> modulus):value(n), modulus(modulus) {
        if (modulus==Polynomial<F>(F{0})) throw std::domain_error("Zero Polynomial Mod");
    }

    template<typename F>
    PolynomialMod<F>::PolynomialMod(F c, Polynomial<F> modulus):value(c), modulus(modulus) {
        if (modulus==Polynomial<F>(F{0})) throw std::domain_error("Zero Polynomial Mod");
        this->value=this->value%this->modulus;

    }

    template<typename F>
    PolynomialMod<F> PolynomialMod<F>::operator+(const PolynomialMod& rhs) const {
        return (this->value+rhs.value)%this->modulus;
    }



    template<typename F>
    size_t PolynomialMod<F>::degree() const {
        return value->degree();
    }

    template<typename F>
    F PolynomialMod<F>::evaluate(F x) const {
        F res{F{0}};

        for (size_t i {degree() + 1}; i-- > 0;) res = res * x + (*this)[i];

        return res;
    }

    template<typename F>
    PolynomialMod<F> PolynomialMod<F>::operator-(const PolynomialMod& rhs) const {
        return (this->value-rhs.value)%this->modulus;
    }

    template<typename F>
    PolynomialMod<F> PolynomialMod<F>::operator*(const PolynomialMod& rhs) const {
        return this->value*rhs.value%this->modulus;
    }

    template<typename F>
    PolynomialMod<F> PolynomialMod<F>::operator*(const F s) const {
        return {value*s, modulus};
    };
    template<typename F>
    PolynomialMod<F> PolynomialMod<F>::operator/(const PolynomialMod& rhs) const {
        auto res{algorithms::extended_gcd(rhs.value, rhs.modulus)};
        if (res.g!=Polynomial(F{1})) throw std::domain_error("Inverse not Found");
        return {res.u*this->value, this->modulus};
    }
    template<typename F>
    PolynomialMod<F> PolynomialMod<F>::operator^(long long e) const {
        return {algorithms::power(*this, e), this->modulus};
    }

    template<typename F>
    PolynomialMod<F> PolynomialMod<F>::inverse() const {
        auto res{algorithms::extended_gcd(this->value, this->modulus)};
        if (res.g!=Polynomial(F{1})) throw std::domain_error("Inverse not Found");
        return {res.u, this->modulus};
    }

    template<typename F>
    bool PolynomialMod<F>::operator==(const PolynomialMod &rhs) const {

        return this->modulus==rhs.modulus&&this->value%rhs.modulus==rhs.value%rhs.modulus;
    }

}
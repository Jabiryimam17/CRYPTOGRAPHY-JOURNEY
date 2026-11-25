#include <stdexcept>
#include <ecnt/fields/prime_field.hpp>
#include <ecnt/polynomials/algorithms.hpp>
namespace ecnt::fields {

    PrimeField::PrimeField(ull _num, ull _p):p(_p), num(_num%p), characterstic(_p){};

    PrimeField PrimeField::operator+(const PrimeField& rhs) const {
        return {(num+rhs.num)%p, p};
    }

    PrimeField PrimeField::operator-(const PrimeField& rhs) const {
        return {(num+p-rhs.num)%p, p};
    }

    PrimeField PrimeField::operator-() const {
        return {(p - num) % p, p};
    }

    PrimeField PrimeField::operator*(const PrimeField& rhs) const {
        return {(num*rhs.num)%p, p};
    }

    PrimeField PrimeField::operator/(const PrimeField& rhs) const {
        return *this*rhs.inverse();
    }

    PrimeField PrimeField::operator^( long long e) const {
        PrimeField b{(*this)};
        PrimeField R{1, p};
        if (e<0) b=b.inverse(), e*=-1;
        while (e) {
            if (e&1) R=R*b;
            b=b*b;
            e>>=1;
        }
        return R;
    }

    PrimeField PrimeField::inverse() const {
        if (*this == PrimeField{0, p}) throw std::domain_error("Zero Division");
        return (*this) ^ static_cast<long long>(p - 2);
    }



    bool PrimeField::operator==(const PrimeField &rhs) const {
        return p==rhs.p && num==rhs.num;
    }
}
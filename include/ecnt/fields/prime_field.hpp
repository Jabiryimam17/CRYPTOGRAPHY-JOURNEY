#pragma once

using ull = unsigned long long;
namespace ecnt::fields {
    class PrimeField {
        ull p, num;

    public:
        PrimeField(ull _num = 0, ull _p = 2);

        PrimeField operator+(const PrimeField &rhs) const;

        PrimeField operator-(const PrimeField &rhs) const;

        PrimeField operator-() const;

        PrimeField operator*(const PrimeField &rhs) const;

        PrimeField operator/(const PrimeField &rhs) const;

        PrimeField operator^( long long e) const;


        bool operator==(const PrimeField &rhs) const;

        PrimeField inverse() const;

    };
}


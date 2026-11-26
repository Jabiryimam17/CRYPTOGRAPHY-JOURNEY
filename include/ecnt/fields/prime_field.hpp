#pragma once

using ull = unsigned long long;
namespace ecnt::fields {
    class PrimeField {
        static ull& default_characterstic_ref();

        ull p, num;

    public:
        ull characterstic;

        PrimeField();

        explicit PrimeField(ull _num);

        PrimeField(ull _num, ull _p);


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


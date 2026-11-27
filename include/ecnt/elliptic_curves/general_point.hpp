#pragma once

namespace ecnt::affine {
    template<typename F>
    class ECGG;
    // short Weierstrass equation
    template<typename F>
    class GPoint {
        F x, y;
        ECGG<F>* E;
        bool infinity{false};
    public:
        GPoint(F x, F y, ECGG<F>* E);

        GPoint(ECGG<F>* E);

        GPoint operator+(const GPoint& rhs) const;

        GPoint operator-(const GPoint& rhs) const;

        GPoint operator-() const;

        GPoint operator*(long long s) const;

        friend GPoint operator*(long long s, const GPoint& P) {
            return P * s;
        };

        GPoint inverse() const;

        bool operator==(const GPoint& rhs) const;
    };
}

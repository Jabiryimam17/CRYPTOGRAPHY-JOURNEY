#pragma once

namespace ecnt::affine {
    template<typename F>
    class ECGS;

    // short Weierstrass equation
    template<typename F>
    class Point {
        F x, y;
        ECGS<F>* E;
        bool infinity{false};
    public:
        Point(F x, F y, ECGS<F>* E);

        explicit Point(ECGS<F>* E);

        Point operator+(const Point& rhs) const;

        Point operator-(const Point& rhs) const;

        Point operator-() const;

        Point operator*(long long s) const;

        friend Point operator*(long long s, const Point& P) {
            return P * s;
        };

        Point inverse() const;

        bool operator==(const Point& rhs) const;
    };
}

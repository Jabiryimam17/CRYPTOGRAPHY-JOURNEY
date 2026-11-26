#pragma once


namespace ecnt::projective {
    template<typename F>
    class ECGS;

    template<typename F>
    class Point {
        F x, y, z;
        ECGS<F>* E;

    public:
        Point(F x, F y, F z, ECGS<F>* E);

        Point(ECGS<F>* E);

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
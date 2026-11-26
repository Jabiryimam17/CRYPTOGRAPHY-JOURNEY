#include <stdexcept>
#include <cstdlib>

#include <ecnt/polynomials/algorithms.hpp>
#include <ecnt/elliptic_curves/jacobian_ecgs.hpp>

namespace ecnt::jacobian {
    template<typename F>
    Point<F>::Point(F x, F y, F z, ECGS<F>* E):x(x),y(y), z(z), E(E) {}


    template<typename F>
    Point<F>::Point(ECGS<F>* E): E(E) {
        const F zero = E->A - E->A;
        F one {ecnt::algorithms::lift_scalar<F>(1, E->A)};
        x = one;
        y = one;
        z = zero;
    }

    template<typename F>
    Point<F> Point<F>::operator+(const Point& rhs) const {
        if (rhs.E != E) throw std::invalid_argument("Points not on same curve");
        const F zero{z - z};
        const F two {ecnt::algorithms::lift_scalar<F>(2, z)};
        const F three{ecnt::algorithms::lift_scalar<F>(3, z)};
        const F four{ecnt::algorithms::lift_scalar<F>(4, z)};
        const F eight{ecnt::algorithms::lift_scalar<F>(8, z)};

        if (z == zero) return rhs;
        if (rhs.z == zero) return *this;
        if (rhs==*this) {
            F v{four*x*y*y};
            F w{three*x*x+E->A*(z^4)};
            F xr{-two*v+w*w};
            F yr{-eight*(y^4)+(v-xr)*w};
            F zr{two*y*z};
            return {xr, yr, zr, E};

        }
        if (*this==-rhs) return Point<F>(E);
        F r{x*rhs.z*rhs.z};
        F s{rhs.x*z*z};
        F t{y*(rhs.z^3)};
        F u{rhs.y*(z^3)};
        F v{s-r};
        F w{u-t};
        F xr{-(v^3)-two*r*v*v+w*w};
        F yr{-t*(v^3)+(r*v*v-xr)*w};
        F zr{v*z*rhs.z};
        return {xr, yr, zr, E};
    }

    template<typename F>
    Point<F> Point<F>::operator-(const Point& rhs) const {
        return *this+(-rhs);
    }

    template<typename F>
    Point<F> Point<F>::operator-() const {
        return {x, -y, z, E};
    }

    template<typename F>
    Point<F> Point<F>::inverse() const {
        return -(*this);
    }

    template<typename F>
    Point<F> Point<F>::operator*(long long e) const {
        Point<F> R{E};
        Point<F> B{*this};
        if (e < 0) {
            B=B.inverse();
        }
        e=std::llabs(e);
        while (e) {
            if (e&1) R=R+B;
            B=B+B;
            e>>=1;
        }
        return R;
    };


    template<typename F>
    bool Point<F>::operator==(const Point& rhs) const {
        if (E != rhs.E) return false;

        const F zero{z - z};
        if (z == zero) return rhs.z == zero;
        if (rhs.z == zero) return false;

        return x * (rhs.z ^ 2) == rhs.x * (z ^ 2) && y * (rhs.z ^ 3) == rhs.y * (z ^ 3);
    }
}


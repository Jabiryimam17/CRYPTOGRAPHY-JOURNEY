#include <stdexcept>
#include <cstdlib>

#include <ecnt/polynomials/algorithms.hpp>
#include <ecnt/elliptic_curves/projective_ecgs.hpp>

namespace ecnt::projective {
    template<typename F>
    Point<F>::Point(F x, F y, F z, ECGS<F>* E):x(x),y(y), z(z), E(E) {}


    template<typename F>
    Point<F>::Point(ECGS<F>* E): E(E) {
        const F zero = E->A - E->A;
        x = zero;
        y = ecnt::algorithms::lift_scalar<F>(1, E->A);
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
            F t{E->A*z*z+three*x*x};
            F u{y*z};
            F v{u*x*y};
            F w{t*t-eight*v};
            F xr{two*u*w};
            F yr{t*(four*v-w)-eight*y*y*u*u};
            F zr{eight*u*u*u};
            return {xr, yr, zr, E};
        }
        if (*this==-rhs) return Point<F>(E);
        F u{rhs.y*z-y*rhs.z};
        F v{rhs.x*z-x*rhs.z};
        F w{u*u*z*rhs.z-v*v*v-two*v*v*x*rhs.z};
        F xr{v*w};
        F yr{u*(v*v*x*rhs.z-w)-v*v*v*y*rhs.z};
        F zr{v*v*v*z*rhs.z};
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

        return x/z==rhs.x/rhs.z && y/z == rhs.y/rhs.z;
    }
}


#include <stdexcept>
#include <cstdlib>

#include <ecnt/elliptic_curves/ecgs.hpp>
#include <ecnt/polynomials/algorithms.hpp>

namespace ecnt::affine {
    template<typename F>
    Point<F>::Point(F x, F y, ECGS<F>* E): x(x), y(y), E(E) {}

    template<typename F>
    Point<F>::Point(ECGS<F>* E):infinity(true), E(E), x(F{0}), y(F{0}){};


    template<typename F>
    Point<F> Point<F>::operator+(const Point& rhs) const {
        if (rhs.E != E) throw std::invalid_argument("Points not on same curve");
        if (rhs.infinity) return *this;
        if (infinity) return rhs;
        if (x != rhs.x) {
            F m{(y - rhs.y) / (x - rhs.x)};
            F xr{m * m - x - rhs.x}, yr{m * (x - xr) - y};
            return Point<F>(xr, yr, E);
        }
        if (y != rhs.y) {
            return Point<F>(E);
        }
        const F zero = y - y;
        if (y != zero) {
            const F three{ecnt::algorithms::lift_scalar<F>(3, x)};
            const F two{ecnt::algorithms::lift_scalar<F>(2, y)};
            F m{(three * x * x + E->A) / (two * y)};
            F xr{m * m - two * x}, yr{m * (x - xr) - y};
            return Point<F>(xr, yr, E);
        }
        return Point<F>(E);
    }

    template<typename F>
    Point<F> Point<F>::operator-(const Point& rhs) const {
        if (rhs.E != E) throw std::invalid_argument("Points not on same curve");
        return *this + (-rhs);
    }

    template<typename F>
    Point<F> Point<F>::operator-() const {
        if (infinity) return *this;
        return Point<F>(x, -y, E);
    }
    template<typename F>
    Point<F> Point<F>::inverse() const {
        return -(*this);
    }

    template<typename F>
    Point<F> Point<F>::operator*(long long e) const {
        Point<F> R {E};
        Point<F> B{*this};
        if (e < 0) {
            B = B.inverse();
        }
        e = std::llabs(e);
        while (e) {
            if (e & 1) R = R + B;
            B = B + B;
            e >>= 1;
        }
        return R;
    }

    template<typename F>
    bool Point<F>::operator==(const Point& rhs) const {
        return x == rhs.x && y == rhs.y && E == rhs.E && infinity==rhs.infinity;
    }
}

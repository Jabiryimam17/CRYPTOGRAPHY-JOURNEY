#include <stdexcept>
#include <cstdlib>

#include <ecnt/elliptic_curves/ecgg.hpp>
#include <ecnt/polynomials/algorithms.hpp>


namespace ecnt::affine {
    template<typename F>
    GPoint<F>::GPoint(F x, F y, ECGG<F>* E):x(x), y(y), E(E){}

    template<typename F>
    GPoint<F>::GPoint(ECGG<F>* E):infinity(true),x(0), y(0), E(E){}

    template<typename F>
    GPoint<F> GPoint<F>::operator+(const GPoint& rhs) const {
        if (rhs.E != E) throw std::invalid_argument("Points are not on the same curve");
        if (rhs.infinity) return *this;
        if (infinity) return rhs;
        if (x != rhs.x) {
            F m{(rhs.y-y)/(rhs.x-x)};
            F v{(y*rhs.x - rhs.y*x)/(rhs.x-x)};
            F xr{m*m+E->a*m-E->b-x-rhs.x};
            F yr{-(m+E->a)*xr-v-E->c};
            return GPoint<F>(xr, yr, E);
        }
        if (y != rhs.y) return GPoint<F>(E);
        F _0{x-x};
        F _2{ecnt::algorithms::lift_scalar(2, _0)};
        F _3{ecnt::algorithms::lift_scalar(3, _0)};
        if (_2*y+E->a*x+E->c==_0) return GPoint<F>(E);
        F m{(_3*x*x+_2*E->b*x+E->d-E->a*y)/(_2*y+E->a*x+E->c)};
        F v{y-m*x};
        F xr{m*m+E->a*m-E->b-x-rhs.x};
        F yr{-(m+E->a)*xr-v-E->c};
        return GPoint<F>(xr, yr, E);
    }

    template<typename F>
    GPoint<F> GPoint<F>::operator-(const GPoint& rhs) const {
        return *this + (-rhs);
    }

    template<typename F>
    GPoint<F> GPoint<F>::operator-() const {
        if (infinity) return *this;
        return GPoint<F>(x, -y-E->a*x-E->c, E);
    }

    template<typename F>
    GPoint<F> GPoint<F>::inverse() const {
        return -(*this);
    }

    template<typename F>
    GPoint<F> GPoint<F>::operator*(long long e) const {
        GPoint<F> R {E};
        GPoint<F> B{*this};
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
    bool GPoint<F>::operator==(const GPoint& rhs) const {
        return x == rhs.x && y == rhs.y && E == rhs.E && infinity==rhs.infinity;
    }
}
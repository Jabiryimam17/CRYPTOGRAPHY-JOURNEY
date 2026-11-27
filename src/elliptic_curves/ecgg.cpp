#include <stdexcept>
#include <cmath>

#include <ecnt/elliptic_curves/ecgg.hpp>
#include <ecnt/polynomials/algorithms.hpp>

namespace ecnt::affine {
    template<typename F>
    ECGG<F>::ECGG(F a, F b, F c, F d, F e):a(a),b(b),c(c),d(d),e(e) {
        if (determinant()==(a-a)) throw std::invalid_argument("Invalid curve");
    }

    template<typename F>
    GPoint<F> ECGG<F>::point(F x, F y) const {
        if (y*y+a*x*y+c*y != x*x*x+b*x*x+d*x+e) throw std::invalid_argument("Invalid point");
        return GPoint<F>(x, y, const_cast<ECGG<F>*>(this));
    }

    template<typename F>
    GPoint<F> ECGG<F>::point() const {
        return GPoint<F>(const_cast<ECGG<F>*>(this));
    }

    template<typename F>
    F ECGG<F>::determinant() const {
        F _0{(a-a)};
        F _2{ecnt::algorithms::lift_scalar(2, _0)};
        F _4{algorithms::lift_scalar(4, _0)};
        F _8{algorithms::lift_scalar(8, _0)};
        F _9{algorithms::lift_scalar(9, _0)};
        F _24{algorithms::lift_scalar(24, _0)};
        F _27{algorithms::lift_scalar(27, _0)};
        F _36{algorithms::lift_scalar(36, _0)};
        F _216{algorithms::lift_scalar(216, _0)};
        F _1728{algorithms::lift_scalar(1728, _0)};
        F b2{a*a+_4*b};
        F b4{_2*d+a*c};
        F b6 {c*c+_4*e};
        F b8{a*a*e+_4*b*e-a*c*d+b*c*c-d*d};
        F delta{(-b2*b2*b8+_8*b4*b4*b4-_27*b6*b6+_9*b2*b4*b6)};
        return delta;
    }

    template<typename F>
    F ECGG<F>::j_invariant() const {
        F _0{(a-a)};

        F _2{ecnt::algorithms::lift_scalar(2, _0)};
        F _4{algorithms::lift_scalar(4, _0)};
        F _24{algorithms::lift_scalar(24, _0)};

        F b2{a*a+_4*b};
        F b4{_2*d+a*c};
        F c4{b2*b2-_24*b4};
        return (c4^3)/determinant();
    }

    template<typename F>
    bool ECGG<F>::isomorphic(const ECGG& rhs) const {
        return j_invariant()==rhs.j_invariant();
    }

    template<typename F>
    bool ECGG<F>::operator==(const ECGG& rhs) const {
        return a==rhs.a && b==rhs.b && c==rhs.c && d==rhs.d && e==rhs.e;
    }

    template<typename F>
    bool ECGG<F>::operator!=(const ECGG& rhs) const {
        return !(*this==rhs);
    }
}
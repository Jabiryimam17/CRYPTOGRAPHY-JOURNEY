#include <stdexcept>
#include <cmath>

#include <ecnt/elliptic_curves/projective_ecgs.hpp>
#include <ecnt/polynomials/algorithms.hpp>

namespace ecnt::projective {
    template<typename F>
    ECGS<F>::ECGS(F A, F B):A(A), B(B) {
        if (ecnt::algorithms::gcd(6ULL, A.characterstic) != 1ULL) throw std::invalid_argument("Invalid Curve");
        if (determinant() == (A - A)) throw std::invalid_argument("Invalid Curve");
    }

    template<typename F>
    Point<F> ECGS<F>::point(F x, F y, F z) const {
        if (y*y*z != x*x*x + A*x*z*z+B*z*z*z) throw std::invalid_argument("Invalid Point");
        return Point<F>(x, y, z, const_cast<ECGS<F>*>(this));
    }

    template<typename F>
    Point<F> ECGS<F>::point() const {
        return Point<F>(const_cast<ECGS<F>*>(this));
    }

    template<typename F>
    F ECGS<F>::j_invariant() const {
        const F _1728{ecnt::algorithms::lift_scalar<F>(1728, A)};
        const F _4{ecnt::algorithms::lift_scalar<F>(4, A)};
        const F num {_1728 * _4 * A * A * A};
        const F den {determinant()};
        return num / den;
    }

    template<typename F>
   F ECGS<F>::determinant() const {
        const F _4{ecnt::algorithms::lift_scalar<F>(4, A)};
        const F _27{ecnt::algorithms::lift_scalar<F>(27, A)};
        return _4 * A * A * A + _27 * B * B;
    }

    template<typename F>
    bool ECGS<F>::operator==(const ECGS<F>& rhs) const {
        return A == rhs.A && B == rhs.B;
    }

    template<typename F>
    bool ECGS<F>::isomorphic(const ECGS<F>& rhs) const {
        return j_invariant() == rhs.j_invariant();
    }
}
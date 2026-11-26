#include <stdexcept>
#include <cmath>

#include <ecnt/elliptic_curves/ecgs.hpp>
#include <ecnt/polynomials/algorithms.hpp>

namespace ecnt::affine {
    template<typename F>
    ECGS<F>::ECGS(F A, F B): A(A), B(B) {
        if (A.characterstic==2 || A.characterstic==3) throw std::invalid_argument("Invalid Curve");

        if (determinant() == (A - A)) {
            throw std::invalid_argument("Invalid curve");
        }
    }

    template<typename F>
    Point<F> ECGS<F>::point(F x, F y) const {
        if (y * y != x * x * x + A * x + B) {
            throw std::invalid_argument("Invalid point");
        }
        return Point<F>(x, y, const_cast<ECGS<F>*>(this));
    }

    template<typename F>
    Point<F> ECGS<F>::point() const {
        return Point<F>(const_cast<ECGS<F>*>(this));
    };


    template<typename F>
    Point<F> ECGS<F>::point(F x) const {
        return point(x, std::sqrt(x * x * x + A * x + B));
    }

    template<typename F>
    bool ECGS<F>::isomorphic(const ECGS<F>& rhs) const {
        return j_invariant()==rhs.j_invariant();
    };
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
    bool ECGS<F>::operator==(const ECGS& rhs) const {
        return A == rhs.A && B == rhs.B;
    }
}

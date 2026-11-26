#pragma once

#include <ecnt/elliptic_curves/point.hpp>

namespace ecnt::affine {
    template<typename F>
    class ECGS {
        F A, B;
        friend class Point<F>;
    public:
        ECGS(F A, F B);

        Point<F> point(F x, F y) const;

        Point<F> point() const;


        Point<F> point(F x) const;

        F j_invariant() const;

        bool isomorphic(const ECGS& rhs) const;

        F determinant() const;

        bool operator==(const ECGS& rhs) const;
    };
}

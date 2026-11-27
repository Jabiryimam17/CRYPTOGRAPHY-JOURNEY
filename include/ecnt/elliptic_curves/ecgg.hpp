#pragma once

#include <ecnt/elliptic_curves/general_point.hpp>
namespace ecnt::affine {
    template<typename F>
    class ECGG {
        F a,b,c,d,e;
        friend class GPoint<F>;
    public:
        ECGG(F a, F b, F c, F d, F e);

        GPoint<F> point(F x, F y) const;

        GPoint<F> point() const;

        F determinant() const;

        // GPoint<F> point(F x) const;

        F j_invariant() const;

        bool isomorphic(const ECGG& rhs) const;


        bool operator==(const ECGG& rhs) const;

        bool operator!=(const ECGG& rhs) const;
    };
}
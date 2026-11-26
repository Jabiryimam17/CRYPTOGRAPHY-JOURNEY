#pragma once
#include<ecnt/elliptic_curves/jacobian_point.hpp>
namespace ecnt::jacobian {
    template<typename F>
    class ECGS {
        F A, B;
        friend class Point<F>;
    public:
        ECGS(F A, F B);


        Point<F> point(F x, F y, F z) const;

        Point<F> point() const;

        F j_invariant() const;

        bool isomorphic(const ECGS<F>& rhs) const;

        F determinant() const;

        bool operator==(const ECGS<F>& rhs) const;

    };
}
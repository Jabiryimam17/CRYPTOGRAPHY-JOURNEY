#pragma once

#include <ecnt/elliptic_curves/general_point.hpp>
namespace ecnt::affine {
    template<typename F>
    class ECGG;

    template<typename F>
    class ECGS;

    template<typename F>
    class QuarticCurve;

    template<typename F>
    class QPoint;

    template<typename F>
    ECGS<F> general_to_short_weistrass_curve(const ECGG<F>& EG);

    template<typename F>
    class ECGG {
        F a,b,c,d,e;
        friend class GPoint<F>;
        friend ECGS<F> general_to_short_weistrass_curve<F>(const ECGG<F>& EG);
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
#pragma once

#include <ecnt/elliptic_curves/quartic_curve.hpp>
#include <ecnt/polynomials/algorithms.hpp>
namespace ecnt::affine {

    template<typename F>
    QPoint<F>::QPoint( F x, F y):x(x), y(y){};

    template<typename F>
    QuarticCurve<F>::QuarticCurve(F a, F b, F c, F d, F e):a(a), b(b), c(c), d(d), e(e){}

    template<typename F>
    bool QuarticCurve<F>::check_point(const QPoint<F>& P) const {
        F u{P.x}, v{P.y};
        return a*u*u*u*u + b*u*u*u*v + c*u*u*v*v + d*u*v*v*v + e*v*v*v*v == u*u*u + v*v*v;
    };

    template<typename F>
    QuarticCurve<F> QuarticCurve<F>::shift_curve(F p) {
        F _0{a-a};
        F _2{algorithms::lift_scalar(2, _0)};
        F _4{algorithms::lift_scalar(4, _0)};
        F _6{algorithms::lift_scalar(6, _0)};
        F _3{algorithms::lift_scalar(3, _0)};
        F ap{a};
        F bp{_4*p*a+b};
        F cp{_6*p*p*a+_3*p*b+c};
        F dp{_4*p*p*p*a+_3*p*p*b+_2*p*c+d};
        F ep{p*p*p*p*a+p*p*p*b+p*p*c+p*d+e};
        return QuarticCurve<F>(ap, bp, cp, dp, ep);
    };
    ;
}
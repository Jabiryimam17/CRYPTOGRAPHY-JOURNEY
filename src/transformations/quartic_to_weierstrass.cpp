#pragma once
#include <stdexcept>
#include <vector>
#include <ecnt/elliptic_curves/ecgg.hpp>
#include <ecnt/elliptic_curves/general_point.hpp>
#include <ecnt/elliptic_curves/quartic_curve.hpp>
#include <ecnt/polynomials/algorithms.hpp>
namespace ecnt::affine {
    template<typename F>
    ECGG<F> quartic_to_weierstrass_curves(const QuarticCurve<F>& quartic_curve, const QPoint<F>& point) {
        auto [p, q]{point};
        F _0{q-q};
        if (!quartic_curve.check_point(point)) throw std::invalid_argument("Point is not on the quartic curve");
        if (q==_0 && quartic_curve.d==q) throw std::invalid_argument("Singular Curve");
        QuarticCurve QCP{quartic_curve.shift(p)};
        auto [a, b, c, d, e]{QCP};
        if (q==_0) {
            return ECGG<F>{
                _0,
                quartic_curve.c,
                _0,
                b*d,
                a*d*d
            };
        }
        F _2{algorithms::lift_scalar(2, q)};
        F _4{algorithms::lift_scalar(4, q)};
        F ap{d/q};
        F bp{c-(d*d/(_4*q*q))};
        F cp{_2*q*b};
        F dp{-(_4*q*q*a)};
        F ep{bp*dp};
        return {ap, bp, cp, dp, ep};

    };

    template<typename F>
    GPoint<F> quartic_to_weierstrass_points(const QuarticCurve<F>& quartic_curve, const QPoint<F>& point, const QPoint<F>& rpoint) {
        ECGG<F> E{quartic_to_weierstrass_curves(quartic_curve, rpoint)};
        auto [p, q]{rpoint};
        auto [u, v]{point};
        auto [a, b, c, d, e]{quartic_curve.shift(p)};
        u = u-p;
        if (u==0 && v==q) return GPoint<F>{E};
        if (u==0) return GPoint<F>{
            -E.b,
            E.a*E.b-E.c
        };
        F _2{algorithms::lift_scalar(2, q)};
        F _4{algorithms::lift_scalar(4, q)};
        return GPoint<F>{
            (2*q*(v+q)+d*u)/(u*u),
            (_4*q*q*(v+q)+_2*q*(d*u+c*u*u)-(d*d*u*u/(_2*q)))/(u^3),
            E
        };
    };




}
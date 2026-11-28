#pragma once
#include <vector>
#include <ecnt/elliptic_curves/ecgg.hpp>
#include <ecnt/elliptic_curves/general_point.hpp>
#include <ecnt/elliptic_curves/quartic_curve.hpp>
// TODO :: projective version


namespace ecnt::affine {
    template<typename F>
    ECGG<F> quartic_to_weierstrass_curves(const QuarticCurve<F>& quartic_curve, const QPoint<F>& point) {

    };

    template<typename F>
    GPoint<F> quartic_to_weierstrass_points(const QuarticCurve<F>& quartic_curve, const QPoint<F>& point, const QPoint<F> & rpoint);


}
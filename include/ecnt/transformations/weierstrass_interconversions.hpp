#pragma once
// TODO :: projective version


#include <ecnt/elliptic_curves/general_point.hpp>
#include <ecnt/elliptic_curves/ecgg.hpp>
#include <ecnt/elliptic_curves/ecgs.hpp>
#include <ecnt/elliptic_curves/point.hpp>
namespace ecnt::affine {
    template<typename F>
    ECGS<F> general_to_short_weistrass_curve(const ECGG<F>& EG);

    template<typename F>
    Point<F> general_to_short_weistrass_point(const ECGG<F>& EG, const GPoint<F>& point);

}
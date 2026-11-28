#pragma once

#include <stdexcept>
#include<ecnt/transformations/weierstrass_interconversions.hpp>
#include <ecnt/polynomials/algorithms.hpp>

namespace ecnt::affine {
    template<typename F>
    ECGS<F> general_to_short_weistrass_curve(const ECGG<F>& EG) {
        if (EG.a.characterstic<=3) throw std::invalid_argument("Characteristic must be greater than 3");
        F _0{EG.a-EG.a};
        F _4{algorithms::lift_scalar(4, _0)};
        F _2{algorithms::lift_scalar(2, _0)};
        F _3{algorithms::lift_scalar(3, _0)};
        F _27{algorithms::lift_scalar(27, _0)};
        F ap{EG.b+EG.a*EG.a/_4};
        F bp{EG.d+EG.a*EG.c/_2};
        F cp{EG.c*EG.c/_4+EG.e};
        F A{bp-ap*ap/_3};
        F B{cp-ap*bp/_3+_2*(ap^3)/_27};
        return {A, B};

    };

    template<typename F>
    Point<F> general_to_short_weistrass_point(const ECGG<F>& EG, const GPoint<F>& point) {
        if (EG.a.characterstic<=3) throw std::invalid_argument("Characteristic must be greater than 3");
        ECGS<F> ES{general_to_short_weistrass_curve(EG)};
        if (point.infinity) return {ES};

        auto [x, y]{point};
        F _0{EG.a-EG.a};
        F _2{algorithms::lift_scalar(2, _0)};
        F _4{algorithms::lift_scalar(4, _0)};
        F _3{algorithms::lift_scalar(3, _0)};
        F ap{EG.b+EG.a*EG.a/_4};
        F yp{y+EG.a*x/_2+EG.c/_2}, xp{x+ap/_3};
        return {xp, yp, ES};
    };

}
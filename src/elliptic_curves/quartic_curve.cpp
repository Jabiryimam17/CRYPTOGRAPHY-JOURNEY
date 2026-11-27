#pragma once

#include <ecnt/elliptic_curves/quartic_curve.hpp>
namespace ecnt::affine {

    template<typename F>
    QPoint<F>::QPoint( F x, F y):x(x), y(y){};

    template<typename F>
    QuarticCurve<F>::QuarticCurve(F a, F b, F c, F d, F e):a(a), b(b), c(c), d(d), e(e){}


    bool check_point(Q Point);

    QuarticCurve shift_curve(F p);
    ;
}
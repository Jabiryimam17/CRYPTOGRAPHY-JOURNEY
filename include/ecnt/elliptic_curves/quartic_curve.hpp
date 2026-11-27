#pragma once

// #include <ecnt/elliptic_curves/elliptic_curve.hpp>
namespace ecnt::affine {

    template<typename F>
    class QPoint {
        F x, y;

        QPoint(F x, F y);
    };

    template<typename F>
    class QuarticCurve {
        F a, b, c, d, e;

        QuarticCurve(F a, F b, F c, F d, F e);

        bool check_point(Q Point);

        QuarticCurve shift_curve(F p);




    };
}
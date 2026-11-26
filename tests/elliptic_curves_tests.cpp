#include <cassert>
#include <iostream>
#include <stdexcept>

#include <ecnt/fields/prime_field.hpp>
#include <ecnt/elliptic_curves/group.hpp>

#include "../src/elliptic_curves/point.cpp"
#include "../src/elliptic_curves/ecgs.cpp"
#include "../src/elliptic_curves/projective_point.cpp"
#include "../src/elliptic_curves/projective_ecgs.cpp"

using ecnt::fields::PrimeField;
using AffineCurve = ecnt::affine::ECGS<PrimeField>;
using AffinePoint = ecnt::affine::Point<PrimeField>;
using ProjectiveCurve = ecnt::projective::ECGS<PrimeField>;
using ProjectivePoint = ecnt::projective::Point<PrimeField>;

namespace {
    constexpr unsigned long long p = 101;
    constexpr unsigned long long p_large = 1000003;

    PrimeField f(long long value) {
        const auto reduced = (value % static_cast<long long>(p) + static_cast<long long>(p)) % static_cast<long long>(p);
        return PrimeField(static_cast<unsigned long long>(reduced), p);
    }

    PrimeField f_large(long long value) {
        const auto reduced = (value % static_cast<long long>(p_large) + static_cast<long long>(p_large)) % static_cast<long long>(p_large);
        return PrimeField(static_cast<unsigned long long>(reduced), p_large);
    }

    void test_ecgs_properties() {
        AffineCurve e(f(2), f(3));
        assert(e.determinant() == f(73));
        assert(e.j_invariant() == f(74));

        AffineCurve same(f(2), f(3));
        assert(e == same);

        AffineCurve iso(f(2), f(3));
        assert(e.isomorphic(iso));

        AffineCurve non_iso(f(2), f(1));
        assert(!e.isomorphic(non_iso));

        bool thrown = false;
        try {
            (void) AffineCurve(f(0), f(0));
        } catch (const std::invalid_argument &) {
            thrown = true;
        }
        assert(thrown);
    }

    void test_point_factory_and_identity() {
        AffineCurve e(f(2), f(3));

        auto p0 = e.point(f(95), f(49));
        auto same = e.point(f(95), f(49));
        assert(p0 == same);

        auto infinity = e.point();
        assert(p0 + infinity == p0);
        assert(infinity + p0 == p0);
        assert(infinity + infinity == infinity);

        bool thrown = false;
        try {
            (void) e.point(f(1), f(1));
        } catch (const std::invalid_argument &) {
            thrown = true;
        }
        assert(thrown);
    }

    void test_point_arithmetic() {
        AffineCurve e(f(2), f(3));

        auto p0 = e.point(f(95), f(49));
        auto q = e.point(f(79), f(44));
        auto r = e.point(f(64), f(68));
        auto two_p = e.point(f(21), f(32));
        auto infinity = e.point();

        assert(p0 + q == r);
        assert(q + p0 == r);
        assert(p0 + p0 == two_p);

        assert(p0.inverse() == -p0);
        assert(p0 - q == p0 + (-q));

        assert(p0 + (-p0) == infinity);
        assert((-p0) + p0 == infinity);
    }

    void test_scalar_multiplication() {
        AffineCurve e(f(2), f(3));

        auto p0 = e.point(f(95), f(49));
        auto q = e.point(f(18), f(35));
        auto two_p = e.point(f(21), f(32));
        auto infinity = e.point();

        assert(p0 * 0 == infinity);
        assert(0 * p0 == infinity);

        assert(p0 * 1 == p0);
        assert(1 * p0 == p0);

        assert(p0 * 2 == two_p);
        assert(2 * p0 == two_p);

        assert(p0 * 5 == q);
        assert(p0 * -1 == -p0);
        assert(-1 * p0 == -p0);
        assert(p0 * -10 == -(p0 * 10));

        assert(p0 * 0 == infinity);
    }

    void test_cross_curve_operations_throw() {
        AffineCurve e1(f(1), f(1));
        AffineCurve e2(f(1), f(1));

        auto p1 = e1.point(f(0), f(1));
        auto p2 = e2.point(f(0), f(1));

        assert(!(p1 == p2));

        bool plus_thrown = false;
        try {
            (void) (p1 + p2);
        } catch (const std::invalid_argument &) {
            plus_thrown = true;
        }
        assert(plus_thrown);

        bool minus_thrown = false;
        try {
            (void) (p1 - p2);
        } catch (const std::invalid_argument &) {
            minus_thrown = true;
        }
        assert(minus_thrown);
    }

    void test_projective_ecgs_properties() {
        ProjectiveCurve e(f_large(2), f_large(3));
        assert(e.determinant() == f_large(275));
        assert(e.j_invariant() == f_large(611112));

        ProjectiveCurve same(f_large(2), f_large(3));
        assert(e == same);
        assert(e.isomorphic(same));

        ProjectiveCurve non_iso(f_large(2), f_large(1));
        assert(!e.isomorphic(non_iso));

        bool thrown = false;
        try {
            (void) ProjectiveCurve(f_large(0), f_large(0));
        } catch (const std::invalid_argument &) {
            thrown = true;
        }
        assert(thrown);
    }

    void test_projective_point_factory_and_identity() {
        ProjectiveCurve e(f_large(2), f_large(3));

        auto p0 = e.point(f_large(3), f_large(6), f_large(1));
        auto same = e.point(f_large(15), f_large(30), f_large(5));
        assert(p0 == same);

        auto infinity = e.point();
        assert(p0 + infinity == p0);
        assert(infinity + p0 == p0);
        assert(infinity + infinity == infinity);

        bool thrown = false;
        try {
            (void) e.point(f_large(1), f_large(1), f_large(1));
        } catch (const std::invalid_argument &) {
            thrown = true;
        }
        assert(thrown);
    }

    void test_projective_point_arithmetic() {
        ProjectiveCurve e(f_large(2), f_large(3));

        auto p0 = e.point(f_large(3), f_large(6), f_large(1));
        auto q = e.point(f_large(126), f_large(25), f_large(1));
        auto r = e.point(f_large(318862), f_large(153992), f_large(1));
        auto two_p = e.point(f_large(868058), f_large(985537), f_large(1));
        auto infinity = e.point();

        assert(p0 + q == r);
        assert(q + p0 == r);
        assert(p0 + p0 == two_p);

        assert(p0.inverse() == -p0);
        assert(p0 - q == p0 + (-q));

        assert(p0 + (-p0) == infinity);
        assert((-p0) + p0 == infinity);
    }

    void test_projective_scalar_multiplication() {
        ProjectiveCurve e(f_large(2), f_large(3));

        auto p0 = e.point(f_large(3), f_large(6), f_large(1));
        auto two_p = e.point(f_large(868058), f_large(985537), f_large(1));
        auto five_p = e.point(f_large(682116), f_large(992905), f_large(1));
        auto ten_p = e.point(f_large(565278), f_large(269036), f_large(1));
        auto infinity = e.point();

        assert(p0 * 0 == infinity);
        assert(0 * p0 == infinity);

        assert(p0 * 1 == p0);
        assert(1 * p0 == p0);

        assert(p0 * 2 == two_p);
        assert(2 * p0 == two_p);

        assert(p0 * 5 == five_p);
        assert(5 * p0 == five_p);
        assert(p0 * 10 == ten_p);
        assert(p0 * -1 == -p0);
        assert(-1 * p0 == -p0);
        assert(p0 * -10 == -(p0 * 10));
    }

    void test_projective_cross_curve_operations_throw() {
        ProjectiveCurve e1(f_large(2), f_large(3));
        ProjectiveCurve e2(f_large(2), f_large(3));

        auto p1 = e1.point(f_large(3), f_large(6), f_large(1));
        auto p2 = e2.point(f_large(3), f_large(6), f_large(1));

        assert(!(p1 == p2));

        bool plus_thrown = false;
        try {
            (void) (p1 + p2);
        } catch (const std::invalid_argument &) {
            plus_thrown = true;
        }
        assert(plus_thrown);

        bool minus_thrown = false;
        try {
            (void) (p1 - p2);
        } catch (const std::invalid_argument &) {
            minus_thrown = true;
        }
        assert(minus_thrown);
    }
}

int main() {
    test_ecgs_properties();
    test_point_factory_and_identity();
    test_point_arithmetic();
    test_scalar_multiplication();
    test_cross_curve_operations_throw();
    test_projective_ecgs_properties();
    test_projective_point_factory_and_identity();
    test_projective_point_arithmetic();
    test_projective_scalar_multiplication();
    test_projective_cross_curve_operations_throw();
    std::cout << "All elliptic-curve tests passed\n";
    return 0;
}

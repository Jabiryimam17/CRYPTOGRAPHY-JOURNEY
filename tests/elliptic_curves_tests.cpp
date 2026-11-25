#include <cassert>
#include <iostream>
#include <stdexcept>

#include <ecnt/fields/prime_field.hpp>
#include <ecnt/elliptic_curves/group.hpp>

#include "../src/elliptic_curves/point.cpp"
#include "../src/elliptic_curves/ecgs.cpp"

using ecnt::ECGS;
using ecnt::Point;
using ecnt::fields::PrimeField;

namespace {
    constexpr unsigned long long p = 101;

    PrimeField f(long long value) {
        const auto reduced = (value % static_cast<long long>(p) + static_cast<long long>(p)) % static_cast<long long>(p);
        return PrimeField(static_cast<unsigned long long>(reduced), p);
    }

    using Curve = ECGS<PrimeField>;
    using ECPoint = Point<PrimeField>;

    void test_ecgs_properties() {
        Curve e(f(2), f(3));
        assert(e.determinant() == f(73));
        assert(e.j_invariant() == f(74));

        Curve same(f(2), f(3));
        assert(e == same);

        Curve iso(f(2), f(3));
        assert(e.isomorphic(iso));

        Curve non_iso(f(2), f(1));
        assert(!e.isomorphic(non_iso));

        bool thrown = false;
        try {
            (void) Curve(f(0), f(0));
        } catch (const std::invalid_argument &) {
            thrown = true;
        }
        assert(thrown);
    }

    void test_point_factory_and_identity() {
        Curve e(f(2), f(3));

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
        Curve e(f(2), f(3));

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
        Curve e(f(2), f(3));

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
        Curve e1(f(1), f(1));
        Curve e2(f(1), f(1));

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
}

int main() {
    test_ecgs_properties();
    test_point_factory_and_identity();
    test_point_arithmetic();
    test_scalar_multiplication();
    test_cross_curve_operations_throw();
    std::cout << "All elliptic-curve tests passed\n";
    return 0;
}

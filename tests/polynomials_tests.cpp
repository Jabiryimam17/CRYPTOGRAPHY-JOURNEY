#include <cassert>
#include <iostream>
#include <stdexcept>

#include <ecnt/fields/prime_field.hpp>
#include <ecnt/polynomials/algorithms.hpp>
#include <ecnt/polynomials/polynomial.hpp>
#include <ecnt/polynomials/polynomialmod.hpp>

using ecnt::fields::PrimeField;
using ecnt::Polynomial;
using ecnt::PolynomialMod;

namespace {
    bool is_prime(unsigned long long n) {
        if (n < 2) return false;
        for (unsigned long long d = 2; d * d <= n; ++d) {
            if (n % d == 0) return false;
        }
        return true;
    }

    void test_algorithms() {
        {
            auto g = ecnt::algorithms::gcd(54, 24);
            assert(g == 6);
        }

        {
            auto res = ecnt::algorithms::extended_gcd(99, 78);
            assert(res.g == 3);
            assert(99 * res.u + 78 * res.v == res.g);
        }

        {
            auto p = ecnt::algorithms::power(3, 5);
            assert(p == 243);
        }

        {
            auto inv = ecnt::algorithms::modular_inverse(3, 11);
            assert(inv == 4);
            assert(3 * inv % 11 == 1);
        }

        {
            bool thrown = false;
            try {
                (void) ecnt::algorithms::modular_inverse(2, 4);
            } catch (const std::domain_error &) {
                thrown = true;
            }
            assert(thrown);
        }

        {
            std::vector<int> values{2, 3, 2};
            std::vector<int> modules{3, 5, 7};
            auto x = ecnt::algorithms::CRT(values, modules);
            assert(x % 3 == 2);
            assert(x % 5 == 3);
            assert(x % 7 == 2);
        }

        {
            bool thrown = false;
            try {
                (void) ecnt::algorithms::CRT(std::vector<int>{1, 2}, std::vector<int>{3});
            } catch (const std::invalid_argument &) {
                thrown = true;
            }
            assert(thrown);
        }
    }

    void test_prime_field() {
        constexpr unsigned long long p = 2;
        assert(is_prime(p));

        PrimeField a(1, p);
        PrimeField b(1, p);
        PrimeField z(0, p);
        PrimeField one(1, p);

        assert(a + b == z);
        assert(a - b == z);
        assert(a * b == one);
        assert(-a == a);
        assert((a ^ 5) == one);
        assert((a / b) == one);
        assert(a.inverse() == one);

        {
            bool thrown = false;
            try {
                (void) z.inverse();
            } catch (const std::domain_error &) {
                thrown = true;
            }
            assert(thrown);
        }
    }

    void test_polynomial() {
        {
            Polynomial<int> p(std::vector<int>{1, 2, 3});
            assert(p.degree() == 2);
            assert(p.evaluate(2) == 17);
        }

        {
            Polynomial<int> p(std::vector<int>{1, 2, 3});
            Polynomial<int> q(std::vector<int>{3, 0, 1});
            auto sum = p + q;
            assert(sum == Polynomial<int>(std::vector<int>{4, 2, 4}));

            auto diff = p - q;
            assert(diff == Polynomial<int>(std::vector<int>{-2, 2, 2}));

            auto prod = p * q;
            assert(prod == Polynomial<int>(std::vector<int>{3, 6, 10, 2, 3}));
        }

        {
            Polynomial<int> p(std::vector<int>{2, -1, 3});
            auto scaled = p * 2;
            assert(scaled == Polynomial<int>(std::vector<int>{4, -2, 6}));
        }

        {
            Polynomial<int> dividend(std::vector<int>{1, -3, 2});
            Polynomial<int> divisor(std::vector<int>{-1, 1});
            auto quotient = dividend / divisor;
            auto remainder = dividend % divisor;
            assert(quotient == Polynomial<int>(std::vector<int>{-1, 2}));
            assert(remainder == Polynomial<int>(0));
        }
        // {
        //     Polynomial<int> dividend(std::vector<int>{2, 1, 0});
        //     Polynomial<int> divisor(std::vector<int>{5, 0});
        //     auto quotient = dividend / divisor;
        //     auto remainder = dividend % divisor;
        //     assert(quotient == Polynomial<int>(std::vector<int>{-1, 2}));
        //     assert(remainder == Polynomial<int>(0));
        // }

        {
            bool thrown = false;
            Polynomial<int> p(std::vector<int>{1, 2, 3});
            try {
                (void) (p / Polynomial<int>(0));
            } catch (const std::domain_error &) {
                thrown = true;
            }
            assert(thrown);
        }
    }

    void test_polynomial_mod() {
        constexpr unsigned long long p = 2;
        assert(is_prime(p));

        using PFPoly = Polynomial<PrimeField>;
        PFPoly mod(std::vector<PrimeField>{PrimeField(1, p), PrimeField(1, p), PrimeField(1, p)});

        {
            PolynomialMod<PrimeField> a(
                PFPoly(std::vector<PrimeField>{PrimeField(1, p), PrimeField(0, p), PrimeField(1, p), PrimeField(1, p)}),
                mod
            );
            PolynomialMod<PrimeField> b(PrimeField(1, p), mod);

            auto c = a + b;
            auto d = c - b;
            assert(d == a);

            auto e = a * b;
            assert(e == a);
        }

        {
            PolynomialMod<PrimeField> a(
                PFPoly(std::vector<PrimeField>{PrimeField(0, p), PrimeField(1, p)}),
                mod
            );
            auto sq = a * a;
            assert(sq.degree() <= 1);
        }

        {
            bool thrown = false;
            try {
                (void) PolynomialMod<PrimeField>(PrimeField(1, p), PFPoly(PrimeField(0, p)));
            } catch (const std::domain_error &) {
                thrown = true;
            }
            assert(thrown);
        }
    }
}

int main() {
    test_algorithms();
    test_prime_field();
    test_polynomial();
    test_polynomial_mod();
    std::cout << "All polynomial tests passed\n";
    return 0;
}

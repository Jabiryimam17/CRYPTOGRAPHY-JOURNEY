#include <stdexcept>
#include <cstdlib>
#include <type_traits>
#include <ecnt/polynomials/algorithms.hpp>
#include <ecnt/polynomials/polynomial.hpp>
#include <ecnt/polynomials/polynomialmod.hpp>
#include <ecnt/fields/prime_field.hpp>

namespace ecnt::algorithms {
    template<typename I>
    ExtendedGcdResult<I> extended_gcd(I a, I b) {
        I up{I{0}}, upp{I{1}};
        I vp{I{1}}, vpp{I{0}};
        while (b != I{0}) {
            I q{a / b}, r{a % b};
            I un{upp - q * up}, vn{vpp - q * vp};
            a = b;
            b = r;
            upp = up, vpp = vp;
            up = un, vp = vn;
        }
        return {a, upp, vpp};
    }

    template<typename I>
    I gcd(I a, I b) {
        while (b != I{0}) {
            I q{a / b}, r{a % b};
            a = b;
            b = r;
        }
        return a;
    }


    template<typename G>
    G power(G b, long long e) {
        if (e < 0) {
            throw std::domain_error("Negative exponent is not supported for this type");
            e = -e;
        }

        G r{1};

        while (e) {
            if (e & 1) r = r * b;
            b = b * b;
            e >>= 1;
        }

        return r;
    }

    template<typename G>
    G modular_inverse(const G &a, const G &mod) {
        auto result{extended_gcd(a, mod)};

        if (result.g != G{1})
            throw std::domain_error("Inverse not found");

        return result.u % mod;
    }

    template<typename G>
    G CRT(std::vector<G> values, std::vector<G> modules) {
        if (values.size() != modules.size()) throw std::invalid_argument("Size mismatch");
        size_t n{values.size()};
        G M{1};
        for (auto& m:modules) {
            auto g{gcd(M, m)};
            if (g!=G{1}) throw std::domain_error("Not Pairwise Prime");
            M=M*m;
        }

        G x{0};

        for (size_t i = 0; i < n; i++) {
            G Mi {M / modules[i]};

            G inv { modular_inverse(Mi, modules[i])};

            x = x + values[i] * Mi * inv;
        }
        return x;
    }

    template<typename F>
    F lift_scalar(long long n, const F &reference) {
        const bool is_negative = n < 0;
        unsigned long long k = static_cast<unsigned long long>(std::llabs(n));

        const F zero = reference - reference;
        F one = zero;

        if constexpr (std::is_same_v<F, ecnt::fields::PrimeField>) {
            one = ecnt::fields::PrimeField(1, reference.characterstic);
        } else {
            one = zero + F{1};
        }

        F result = zero;
        F base = one;

        while (k) {
            if (k & 1ULL) result = result + base;
            base = base + base;
            k >>= 1ULL;
        }

        return is_negative ? -result : result;
    }

    template ExtendedGcdResult<int> extended_gcd<int>(int a, int b);
    template int gcd<int>(int a, int b);
    template int power<int>(int b, long long e);
    template int modular_inverse<int>(const int &a, const int &mod);
    template int CRT<int>(std::vector<int> values, std::vector<int> modules);

    template ExtendedGcdResult<ecnt::Polynomial<int>> extended_gcd<ecnt::Polynomial<int>>(ecnt::Polynomial<int> a,
                                                                                             ecnt::Polynomial<int> b);
    template ecnt::Polynomial<int> power<ecnt::Polynomial<int>>(ecnt::Polynomial<int> b, long long e);

    template ExtendedGcdResult<ecnt::Polynomial<ecnt::fields::PrimeField>>
    extended_gcd<ecnt::Polynomial<ecnt::fields::PrimeField>>(ecnt::Polynomial<ecnt::fields::PrimeField> a,
                                                              ecnt::Polynomial<ecnt::fields::PrimeField> b);
    template ecnt::Polynomial<ecnt::fields::PrimeField>
    power<ecnt::Polynomial<ecnt::fields::PrimeField>>(ecnt::Polynomial<ecnt::fields::PrimeField> b, long long e);

    template ecnt::fields::PrimeField
    lift_scalar<ecnt::fields::PrimeField>(long long n, const ecnt::fields::PrimeField &reference);
}

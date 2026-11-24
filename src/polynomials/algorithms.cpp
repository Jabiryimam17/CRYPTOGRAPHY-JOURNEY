#include <stdexcept>
#include <ecnt/polynomials/algorithms.hpp>

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
            up = un, vn = vp;
        }
        return {a, {upp, vpp}};
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
            b = b.inverse();
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

        if (result.gcd != G{1})
            throw std::domain_error("Inverse not found");

        return result.x % mod;
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
}

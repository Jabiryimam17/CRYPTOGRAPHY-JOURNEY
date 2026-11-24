#pragma once
#include <vector>
namespace ecnt::algorithms {
    template<typename I>
    struct ExtendedGcdResult {
        I g;
        I u;
        I v;
    };


    template<typename I>
    ExtendedGcdResult<I> extended_gcd(I a, I b);

    template<typename I>
    I gcd(I a, I b);

    template<typename G>
    G power(G b, long long e);

    template<typename G>
    G modular_inverse(const G &a, const G &mod);


    template<typename G>
    G CRT(std::vector<G> values, std::vector<G> modules);


}

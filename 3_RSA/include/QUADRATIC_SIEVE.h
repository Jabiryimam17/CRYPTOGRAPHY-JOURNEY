//
// Created by Jabir on 1/11/2026.
//

#ifndef CRYPTOGRAPHY_QUADRATIC_SIEVE_H
#define CRYPTOGRAPHY_QUADRATIC_SIEVE_H
#include <bitset>
#include <vector>
#include <cmath>
#include "TONELLI_SHANKS.h"
const int S=10;
class QS
{
public:
    ull B;
    ull N;
    std::vector<std::pair<ull, ull>> prime_bases;
    QS(ull B, ull N);
    void build_prime_base();
    void sieve_potentials(std::vector<ull>& candidates, ull a);
    void sieve_potentials_p(std::vector<ull>& candidates, ull a, ull p, ull s);
    void sieve_b_smooths(std::vector<ull>& b_smooths, std::vector<int> where, std::vector<std::bitset<S>>& m, ull a);
    void sieve_b_smooths_p(std::vector<ull>& b_smooths, std::vector<int> where, std::vector<std::bitset<S>>& m, ull a, ull p, ull s, size_t r);
    ull calc_start(ull p, ull a, ull s);
    ull calc_sqrt_sol(ull p, ull n);
};
#endif //CRYPTOGRAPHY_QUADRATIC_SIEVE_H
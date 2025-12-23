//
// Created by Jabir on 12/23/2025.
//

#ifndef CRYPTOGRAPHY_SHANK_ALGORITHM_H
#define CRYPTOGRAPHY_SHANK_ALGORITHM_H
#include <vector>
using ull=unsigned long long;
struct G
{
    unsigned long long v;
    G();
    explicit G(unsigned long long v=0);
    G operator*(G r) const;

    bool operator>(G r) const;
    bool operator<(G r) const;
    G operator>>(G r) const;
    G operator&(G r) const;
    G operator%(G r) const;
    bool operator==(G r) const;
};
class SHANK // general shank bruteforcer for any group
{
    public:
    G p;
    std::vector<std::pair<ull,G>> g_generated, h_g_inverse_generated;
    SHANK(G _p);
    ull solve_dhp(G g, G h, unsigned long long N);
    static G mod_pow(G b, G e, G mod);

};

#endif //CRYPTOGRAPHY_SHANK_ALGORITHM_H
//
// Created by Jabir on 12/24/2025.
//

#ifndef CRYPTOGRAPHY_GROUP_H
#define CRYPTOGRAPHY_GROUP_H
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
    static G mod_pow(G b, G e, G mod);
};
#endif //CRYPTOGRAPHY_GROUP_H
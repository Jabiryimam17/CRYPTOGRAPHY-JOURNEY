//
// Created by Jabir on 12/22/2025.
//

#include"../include/EEA.h"

std::pair<long long,long long> extended_euclidean_algorithm(long long a, long long b) {
    long long old_r=a, r=b;
    long long old_s=1, s=0;
    long long old_t=0, t=1;
    while (r!=0)
    {
        long long q=old_r/r;
        long long temp=r;
        r=old_r-q*r;
        old_r=temp;

        temp=s;
        s = old_s-q*s;
        old_s=temp;

        temp=t;
        t=old_t-q*t;
        old_t=temp;
    }
    return {old_s, old_t};
}

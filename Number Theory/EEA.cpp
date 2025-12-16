//
// Created by Jabir on 12/16/2025.
//An
#include <bits/stdc++.h>
using namespace std;
pair<int,int> extended_euclidean_algorithm(int a, int b) {
    int old_r=a, r=b;
    int old_s=1, s=0;
    int old_t=0, t=0;
    while (r!=0)
    {
        int q=old_r/r;
        int temp=r;
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
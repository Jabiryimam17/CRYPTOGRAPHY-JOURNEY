//
// Created by Jabir on 12/24/2025.
//

#include "../../2_Discrete_Log_DH//include/POHLIG_HELLMAN.h"
void POHLIG_HELLMAN::factorize(ull _N)
{
    prime_factors.clear();
    N=_N;
    for (ull f=2; f <=N;f++)
    {
        ull e=0;
        ull acc=1;
        while (_N%f==0) e++, _N/=f, acc*=f;
        if (e>0) prime_factors.push_back({acc,{f, e}});
    }
}

ull POHLIG_HELLMAN::solve_dhp(G _g, G _h, ull _N)
{
    factorize(_N);
    equations.clear();
    for (auto& f:prime_factors)
    {
        G s_g=G::mod_pow(_g, G(N/f.first), p);
        G s_h=G::mod_pow(_h, G(N/f.first), p);
        ull a=solve_dhp_factor(s_g,s_h, f.first, f.second.first, f.second.second);
        if (a > f.second.first) return p.v+1; // no solution exists
        equations.emplace_back(static_cast<long long>(a), static_cast<long long>(f.first));
    }
    ull sol = crt(equations);
    return sol;
}

ull POHLIG_HELLMAN::solve_dhp_factor(G _g, G _h, ull q_pow, ull q, ull e)
{
    G g_f=G::mod_pow(_g, G(q_pow/q), p);
    dlp_bruteforce.prepare(g_f, p, q, e);
    ull curr_g_pow=q_pow;
    ull curr_q_pow=1;
    G p_h=_h;
    ull sol=0;
    // general prefix optimization i am doing here is the following
    // the basic principe xi=lg(h*g^-(summation of x*q^j where j from 0 to i-1))^q^e-i-1 to base g
    // let us say p_h_i-1= (h*g^-(summation of xj*q^j where j from 0 to i-1)) then we can add the next one based on the lines 41-45
    // since p_h_i = p_h_i-1* g ^ -(xi*q^i)
    for (ull i=0; i < e; i++)
    {
        curr_g_pow/=q;
        G r_h=G::mod_pow(p_h, G(curr_g_pow), p);
        ull x_i=dlp_bruteforce.solve_dhp(r_h);
        if (x_i > q) return x_i;// to indicate no solution exist
        ull val=x_i*curr_q_pow;
        G u=G::mod_pow(_g, G(val), p);
        G u_i=G::mod_pow(u, G(q_pow-val), p);
        p_h = p_h*u_i;
        sol += val;
        curr_q_pow*=q;
    }
    return sol;

}

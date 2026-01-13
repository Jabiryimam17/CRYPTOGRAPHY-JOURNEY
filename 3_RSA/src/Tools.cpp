//
// Created by Jabir on 12/29/2025.
//

#include "../include/Tools.h"

#include <cmath>
#include <iostream>
#include <numbers>
#include <variant>

ull miller_rabin_test::random_prime_generator(unsigned int k)
{
    ull r_p = 0;
    bool prime=false;
    while (!prime)
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&r_p), 3);
        if (r_p%2==0) continue;
        prime = test_witness(k, r_p);
    };
    return r_p;
}

bool miller_rabin_test::test_witness(unsigned int k, ull p)
{
    ull witness = 0;
    for (int i=0; i < k; i++)
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&witness), sizeof(witness));
        witness%=p;
        if (witness==0) continue;
        if (is_composite(p, witness))
        {
            std::cout << witness << std::endl;
            return false;
        }
    }
    return true;
}

bool miller_rabin_test::is_composite(ull n, ull a)
{
    ull d = n - 1;
    ull s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    ull x = fast_exponentiation(a, d, n);
    if (x == 1 || x == n - 1)
        return false;

    for (ull i = 1; i < s; i++) {
        x = mod_mul(x, x, n);
        if (x == n - 1)
            return false;
    }

    return true;
}

ull miller_rabin_test::riemann_based_random_prime_generator() // conjecture based not theory based
{
    ull r_p = 0;
    bool prime=false;
    while (!prime)
    {
        RAND_bytes(reinterpret_cast<unsigned char*>(&r_p), sizeof(32));
        if (r_p%2==0) continue;
        ull r_root=log(r_p)/log(std::numbers::e);
        ull r=2*(r_root*r_root);
        prime=true;
        for (int w=3; w < r; w+=2)
        {
            if (is_composite(r_p, w)) {prime=false; break;}
        }
    };
    return r_p;
}

int gauss(std::vector<std::vector<double>>& a, std::vector<double>& ans)
{
    int n=a.size();
    int m=a[0].size()-1;

    std::vector<int> where(m, -1);
    for (int col=0,row=0; row < n && col < m; col++)
    {
        int sel=row;
        for (int i=row; i < n; i++)
        {
            if (a[i][col] > a[sel][col]) sel=i;
        }
        if (abs(a[sel][col])<EPS) continue;
        std::swap(a[sel], a[row]);
        where[col]=row;

        for (int i=0; i < n; i++)
        {
            if (i!=row)
            {
                double c=a[i][col]/a[row][col];
                for (int j=col; j <= m; j++) a[i][j] -= a[row][j]*c;
            }
        }
        row++;
    }

    ans.assign(m, 0);
    bool is_independent=false;
    for (int i=0; i < m; i++)
    {
        if (where[i]!=-1) ans[i]=a[where[i]][m]/a[where[i]][i];
        else is_independent=true;
    }

    for (int i=0; i < n; i++)
    {
        double sum=0;
        for (int j=0; j < m; j++) sum += ans[j]*a[i][j];
        if (abs(sum-a[i][m])>EPS) return 0;
    }
    return is_independent?INF:1; // there is at least one solution which is ans;

}


int gauss_bit(std::vector<std::bitset<N_P>>& a, int n, int m, std::bitset<N_P>& ans)
{
    std::vector<int> where(m, -1);
    for (int r=0, c=0; r < n&&c < m; c++)
    {
        for (int i=r; i < n; i++)
        {
            if (a[i][c])
            {
                std::swap(a[i], a[r]);
                break;
            }
        }
        if (a[r][c]==0) continue;
        where[c]=r;
        for (int i=0; i < n; i++)
        {
            if (i!=r && a[i][c]) a[i]^=a[r];
        }
        r++;
    }
    bool is_independent=false;
    for (int i=0; i < m; i++)
    {
        if (where[i]!=-1) ans[i]=a[i][m];
        else is_independent=true;
    }

    for (int i=0; i < n; i++)
    {
        int sum=0;
        for (int j=0; j < m; j++) sum ^= a[i][j];
        if (sum!=a[i][m]) return 0;
    }
    return is_independent?2:1;
}


void gauss_bit_qs(std::vector<std::bitset<N_P>>& A, int b_n, int p_m, std::vector<std::bitset<N_B>>& ans) {
    std::vector<std::bitset<N_B>> I(b_n);
    for (int i = 0; i < b_n; i++) I[i].set(i);

    int pivots = 0;
    int r = 0;
    for (int c = 0; c < p_m && r < b_n; c++) {
        int pivot_row = r;
        for (int i = r; i < b_n; i++) {
            if (A[i][c]) {
                pivot_row = i;
                break;
            }
        }
        if (A[pivot_row][c] == 0) continue;

        std::swap(I[pivot_row], I[r]);
        std::swap(A[pivot_row], A[r]);

        for (int i = r + 1; i < b_n; i++) {
            if (A[i][c]) {
                A[i] ^= A[r];
                I[i] ^= I[r];
            }
        }
        r++;
        pivots++;
    }


    ans.assign(b_n - pivots, std::bitset<N_B>());
    for (int i = pivots; i < b_n; i++) ans[i - pivots] = I[i];
}
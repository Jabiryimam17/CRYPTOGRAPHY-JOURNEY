//
// Created by Jabir on 1/6/2026.
//


#include "../include//JACOBI.h"

long long jacobi(long long a, long long n)
{
     if (n <= 0 || n % 2 == 0) return 0;

     if (a == 0) return 0;
     if (a == 1) return 1;

     int sign = 1;

     if (a < 0) {
          a = -a;
          if (n % 4 == 3) sign = -sign;
     }

     a %= n;
     int c=n%8==3 || n%8==5?-1:1;
     while (a % 2 == 0) {
          a /= 2;
          sign *= c;
     }

     if (a == 1) return sign;

     if (a % 4 == 3 && n % 4 == 3) sign = -sign;

     return sign * jacobi(n % a, a);
}

#include <iostream>
#include <vector>

#include  "3_RSA/include/Tools.h"

int main()
{
    std::vector<std::vector<double>> eqs{
        {1, -2,-4, 0},
        {-1, 1, 2, 0},
        {3, -3, -6,0}
    };
    std::vector<double> ans;
    auto s = gauss(eqs, ans);
    if (s==0)
    {
        std::cout << "INCONSISTENT" << std::endl;
        return -1;
    }
    std::cout << (s==1?"CONSISTENT":"DEPENDENT") << std::endl;
    for (int x=0; x < ans.size(); x++)
    {
        std::cout << x << " : " << ans[x] << std::endl;
    }
    return 0;
}

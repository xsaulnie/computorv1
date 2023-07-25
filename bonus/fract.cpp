#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

int pgcd(int a, int b);

bool reductible(int &num, int &denum)
{
    int pg = pgcd(num, denum);
    while (pg != 1)
    {
        num = num / pg;
        denum = denum / pg;
        pg = pgcd(num, denum);
    }
    if (num >= 100 || denum >= 100)
        return true;
    return false;
}

void print_fract(float num, float denum)
{
    int numi;
    int denumi;

    if (std::floor(num) != num || std::floor(denum) != denum || abs(denum) == 1)
    {
        std::cout << num / denum << std::endl;
        return ;
    }

    numi = num;
    denumi = denum;

    reductible(numi, denumi);

    if (denumi == 1)
    {
        std::cout <<  num / denum << std::endl;
        return ;
    }

    if (num / denum < 0)
        std::cout << "-";

    std::cout << abs(numi) << '/' << abs(denumi) << std::endl;
    return ;
}

void print_fract_i(float num, float denum, bool sig)
{
    int numi;
    int denumi;

    if (std::floor(num) != num || std::floor(denum) != denum || abs(denum) == 1)
    {
        std::cout << (sig ? num / denum : abs(num / denum));
        return ;
    }

    numi = num;
    denumi = denum;

    reductible(numi, denumi);

    if (denumi == 1)
    {
        std::cout << (sig ? num / denum : abs(num / denum));
        return ;
    }

    if (num / denum < 0 && sig)
        std::cout << "-";

    std::cout << abs(numi) << '/' << abs(denumi);
    return ;
}
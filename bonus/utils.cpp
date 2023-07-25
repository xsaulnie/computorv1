#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

void print_fract_i(float num, float denum, bool sig);

int pgcd(int a, int b)
{
    int r ;
    if (b == 0)
        return a;
    r = a % b;
    while (r != 0)
    {
        a = b;
        b = r;
        r = a % b;
    }
    return b; 
}

void canonical(std::map<int, float> &coef)
{
    float beta = - ( (coef[1] * coef[1] - (4 * coef[2] * coef[0]))  / (4 * coef[2]));
    float alpha = - (coef[1] / (2 * coef[2]));
    std::cout << "Canonical form: ";
    
    if (coef[2] != 1)
        std::cout << coef[2] << " * ";
    std::cout << "(X";
    if (alpha != 0)
    {
        std::cout << (alpha > 0 ? " - " : " + ");
        print_fract_i(abs(coef[1]), abs( 2 * coef[2]), false);
    }
    if (beta == 0)
    {
        std::cout << ")^2 = 0" << std::endl;
        return ;
    }
    std::cout << ")^2" << (beta < 0 ? " - " : " + " );
    print_fract_i(abs(coef[1] * coef[1] - (4 * coef[2] * coef[0])), abs(4 * coef[2]), false);
    std::cout << " = 0"<< std::endl;
}

void factorized(float b, float a, float delta)
{
    if (delta < 0)
        return ;
    float x1 = ((-b - sqrt(delta)) / 2 * a);
    float x2 = ((-b + sqrt(delta)) / 2 * a);

    std::cout << "Factorized form : ";
    if (delta > 0)
    {
        std::cout << a << "(X";
        std::cout << (x1 >= 0 ? " - " : " + ");
        print_fract_i(abs(-b - sqrt(delta)), abs(2 * a), false);
        std::cout << ")(X";
        std::cout << (x2 >= 0 ? " - " : " + ");
        print_fract_i(abs(-b + sqrt(delta)), abs(2 * a), false);
        std::cout << ")" << std::endl;
    }

    if (delta == 0)
    {
        std::cout << a << "(X";
        std::cout << (x1 >= 0 ? " - " : " + ");
        print_fract_i(abs(-b), abs(2 * a), false);
        std::cout << ")^2" << std::endl;
    }  
}
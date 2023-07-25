#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

void print_fract(float num, float denum);
void print_fract_i(float num, float denum, bool sig);
void canonical(std::map<int, float> &coef);
void factorized(float b, float a, float delta);

void solverorder0(std::map<int, float> &coef)
{
    if (coef[0] == 0)
        std::cout << "Any real number is a solution to this equation." << std::endl;
    else
        std::cout << "This equation has no solution."<< std::endl;
}

void solverorder1(std::map<int, float> &coef)
{
    std::cout << "The solution is :" << std::endl;
    if (coef.find(0) == coef.end() || coef[0] == 0)
    {
        std::cout << "0" << std::endl;
        return;
    }
    print_fract(- 1 * coef[0], coef[1]);
}

void solverorder2(std::map<int, float> &coef)
{
    float delta;

    if (coef.find(0) == coef.end())
        coef[0] = 0;
    if (coef.find(1) == coef.end())
        coef[1] = 0;

    canonical(coef);

    delta = (coef[1] * coef[1]) - (4 * coef[2] * coef[0]);
    std::cout << "Identification: a := " << coef[2] << " b := " << coef[1] << " c := " << coef[0] << std::endl;
    std::cout << "Discriminant computation : delta = b^2 - (4 * a * c)" << std::endl;
    std::cout << "delta = " << coef[1] << "^2 - (4 * " << coef[2] << " * " << coef[0] << ")" << std::endl;
    std::cout << "delta = " << delta << std::endl;

    if (delta > 0 )
    {
        std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
        std::cout << "x1 = (-b - sqrt(delta)) / 2 * a, x1 = ";
        print_fract(-coef[1] - sqrt(delta), 2 * coef[2]);
        std::cout << "x2 = (-b + sqrt(delta)) / 2 * a), x2 = ";
        print_fract(-coef[1] + sqrt(delta), 2 * coef[2]);

    }
    else if (delta == 0)
    {
        std::cout << "Discriminant is strictly null, the double solution is:" << std::endl;
        std::cout << "x = -b / 2 * a, x = ";
        print_fract(-coef[1], 2 * coef[2]);
    }
    else
    {
        std::cout << "Discriminant is stricly negative, the two conjugate complex solutions are:" << std::endl;
        std::cout << "z1 = (-b / 2 * a) - (sqrt(-delta) / 2 * a) * i, z1 = ";
        if (coef[1] != 0)
            print_fract_i(-coef[1], 2 * coef[2], true);
        std::cout << (coef[2] < 0 ? " + " : " - ");
        print_fract_i(abs(sqrt(-delta)), abs(2 * coef[2]), false);
        std::cout << "*i"<< std::endl;
        std::cout << "z2 = (-b / 2 * a) + (sqrt(-delta) / 2 * a) * i, z2 = ";
        if (coef[1] != 0)
            print_fract_i(-coef[1], 2 * coef[2], true); 
        std::cout << (coef[2] < 0 ? " - " : " + ");
        print_fract_i(abs(sqrt(-delta)), abs(2 * coef[2]), false);
        std::cout << "*i" << std::endl;
    }
    factorized(coef[1], coef[2], delta);
}

void solver(std::map<int, float> &coef)
{
    if (coef.empty())
    {
        std::cout << "Any real number is a solution to this equation." << std::endl;
        return;
    }

    int deg = coef.rbegin()->first;

    switch (deg)
    {
        case 0:
            solverorder0(coef);
            break;
        case 1:
            solverorder1(coef);
            break;
        case 2:
            solverorder2(coef);
            break;
    }
}
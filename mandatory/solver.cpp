#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

void solverorder0(std::map<int, float> &coef)
{
    if (coef[0] == 0)
        std::cout << "Any real number is a solution to this equation." << std::endl;
    else
        std::cout << "This equation has no solution."<< std::endl;
}

void solverorder1(std::map<int, float> &coef)
{
    std::cout << "The solution is:" << std::endl;
    if (coef.find(0) == coef.end() || coef[0] == 0)
    {
        std::cout << "0" << std::endl;
        return;
    }
    std::cout << - coef[0] / coef[1] << std::endl;
}

void solverorder2(std::map<int, float> &coef)
{
    float delta;

    if (coef.find(0) == coef.end())
        coef[0] = 0;
    if (coef.find(1) == coef.end())
        coef[1] = 0;
    delta = (coef[1] * coef[1]) - (4 * coef[2] * coef[0]);

    if (delta > 0 )
    {
        std::cout << "Discriminant is strictly positive, the two solutions are:" << std::endl;
        std::cout << (-coef[1] - sqrt(delta)) / (2 * coef[2]) << std::endl;
        std::cout << (-coef[1] + sqrt(delta)) / (2 * coef[2]) << std::endl;
    }
    else if (delta == 0)
    {
        std::cout << "Discriminant is null, the double solution is:" << std::endl;
        std::cout << (-coef[1]) / (2 * coef[2]) << std::endl;
    }
    else
    {
        std::cout << "Discriminant is stricly negative, the two conjugate complex solutions are:" << std::endl;
        std::cout << (-coef[1]) / (2 * coef[2]) << (coef[2] < 0 ? " + " : " - ") << abs(sqrt(-delta) / (2 * coef[2])) << "*i"<< std::endl;
        std::cout << (-coef[1]) / (2 * coef[2]) << (coef[2] < 0 ? " - " : " + ") << abs(sqrt(-delta) / (2 * coef[2])) << "*i"<< std::endl;
    }
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
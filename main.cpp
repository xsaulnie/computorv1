#include <stdlib.h>
#include <iostream>
#include <map>
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
    //std::cout << "delta" << delta << std::endl;

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

bool print_order(std::map<int, float> &coef)
{
    int deg = coef.rbegin()->first; 
    std::cout << "Polynomial degree: " << deg << std::endl;
    if (deg >= 3)
        return true;
    return false;
}

void print_reduce(std::map<int, float>&coef)
{
    std::cout << "Reduced form: ";
    std::map<int, float>::iterator it = coef.begin();
    std::cout << it->second << " * X^" << it->first;
    it++;
    while(it != coef.end())
    {
        std::cout << (it->second < 0 ? " - " : " + ") << abs(it->second) << " * X^" << it->first;
        it++;
    }
    std::cout << " = 0" << std::endl;
}

void get_coef(std::map<int, float> &coef, std::string eq, char sig)
{
    int index;
    float value;

    eq.erase(remove(eq.begin(), eq.end(), ' '), eq.end());

    //std::string mess = std::string(eq.find('*'), eq.end());

    //index = atoi((eq[eq.find('*') + 3]));
    //std::cout << eq << std::endl;
    //std::cout << eq.substr(eq.find('*') + 3, eq.size()) << std::endl;
    index = atoi(eq.substr(eq.find('*') + 3, eq.size()).c_str());
    value = atof(eq.c_str());

    if (sig == '+')
    {
        if (coef.find(index) == coef.end())
            coef[index] = value;
        else
            coef[index] = coef[index] - value;
    }
    else
    {
        if (coef.find(index) == coef.end())
            coef[index] = - value;
        else
            coef[index] = coef[index] - value;
    }

}

void get_coefs(std::map<int, float> &coef, std::string equation, char sig)
{
    std::string::iterator it = equation.begin();
    std::string::iterator it_cur = equation.begin();

    while (it != equation.end())
    {
        if (*it == '+' || *it == '-')
        {
            get_coef(coef, std::string(it_cur, it), sig);
            it_cur = it;
        }
        it++;
    }
    get_coef(coef, std::string(it_cur, equation.end()), sig);
}

std::map<int, float> parcing(std::string equation)
{
    std::map<int, float> coef;
    int equal;

    equal = equation.find("=");

    get_coefs(coef, equation.substr(0, equal), '+');
    get_coefs(coef, equation.substr(equal + 2), '-');

    return coef;
}

int main(int argc, char *argv[])
{
    std::map<int, float> coef;

    if (argc != 2)
    {
        std::cout << "Error : Wrong number of argument" << std::endl;
        exit(1);
    }
    coef = parcing(argv[1]);

    print_reduce(coef);
    if (print_order(coef))
    {
        std::cout << "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
        exit(1);
    }
    solver(coef);
    return 0;
}
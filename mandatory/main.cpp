#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

bool check_syntax(std::string eq);
std::map<int, float> parcing(std::string equation);
void solver(std::map<int, float> &coef);

bool print_order(std::map<int, float> &coef)
{
    int deg;

    if (coef.empty())
        deg = 0;
    else
        deg = coef.rbegin()->first;       
    std::cout << "Polynomial degree: " << deg << std::endl;
    if (deg >= 3)
        return true;
    return false;
}

void print_reduce(std::map<int, float>&coef)
{
    std::cout << "Reduced form: ";

    if (coef.empty())
    {
        std::cout << "0 = 0" << std::endl;
        return;
    }
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

int main(int argc, char *argv[])
{
    std::map<int, float> coef;

    if (argc != 2)
    {
        std::cout << "Error : Wrong number of argument" << std::endl;
        exit(1);
    }

    if (check_syntax(argv[1]))
    {
        std::cout << "Incorrect equation : Syntax error" << std::endl;
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
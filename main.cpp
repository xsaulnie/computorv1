#include <stdlib.h>
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>


void get_coef(std::map<int, float> &coef, std::string eq, char sig)
{
    int index;
    float value;

    eq.erase(remove(eq.begin(), eq.end(), ' '), eq.end());
    std::cout << eq << std::endl;

    index = eq[eq.find('*') + 3] - 48;
    value = atof(eq.c_str());

    if (sig == '+')
    {
        coef[index] = value;
    }
    else
    {
        if (coef.find(index) == coef.end())
            coef[index] = - value;
        else
            coef[index] = coef[index] - value;
    }

//   std::cout << eq[eq.find('*') + 3] - 48 << std::endl;
//    std::cout << atof(eq.c_str()) << std::endl;
}

void get_coefs(std::map<int, float> &coef, std::string equation, char sig)
{
    std::string::iterator it = equation.begin();
    std::string::iterator it_cur = equation.begin();

    while (it != equation.end())
    {
        if (*it == '+' || *it == '-')
        {
            //std::cout << std::string(it_cur, it) << std::endl;
            get_coef(coef, std::string(it_cur, it), sig);
            it_cur = it;
        }
        it++;
    }
    get_coef(coef, std::string(it_cur, equation.end()), sig);
    //std::cout << std::string(it_cur, equation.end())<< std::endl;
}

std::map<int, float> parcing(std::string equation)
{
    std::map<int, float> coef;
    int equal;

    equal = equation.find("=");

    get_coefs(coef, equation.substr(0, equal), '+');
    get_coefs(coef, equation.substr(equal + 2), '-');
    //std::cout << equation.substr(0, equal) << std::endl;
    //std::cout << equation.substr(equal + 2) << std::endl;
    //exit(0);

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

    // std::cout << coef[0] << std::endl;
    // std::cout << coef[1] << std::endl;
    // std::cout << coef[2] << std::endl;
    std::map<int, float>::iterator it = coef.begin();
    while (it != coef.end())
    {
        std::cout << "Coef " << it->first << " Value " << it->second << std::endl;
        it++;
    }
    return 0;
}
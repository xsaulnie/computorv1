#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

void get_coef(std::map<int, float> &coef, std::string eq, char sig)
{
    int index;
    float value;
    int pos = 0;
    int expo;

    eq.erase(remove(eq.begin(), eq.end(), ' '), eq.end());

    if (eq[0] == '+' || eq[0] == '-')
        pos = 1;

    if (eq[0 + pos] == 'X')
    {
        if (eq[0] == '-')
            value = -1;
        else
            value = 1;
    }
    else
    {
        value = atof(eq.c_str());
    }

    expo = eq.find('^');
    if (expo != -1)
    {
        index = atoi(eq.substr(expo + 1, eq.size()).c_str());
    }
    else
    {
        if (eq.find('X') == (unsigned long)(-1))
            index = 0;
        else
            index = 1;
    }

    //std::cout << "monome : " << eq << " index " << index << " value " << value <<std::endl;

    if (sig == '+')
    {
        if (coef.find(index) == coef.end())
            coef[index] = value;
        else
            coef[index] = coef[index] + value;
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

    if (*it == '-')
    {
        it_cur = it;
        it++;
        while (*it != '+' && *it  != '-' && it != equation.end())
            it++;
        get_coef(coef, std::string(it_cur, it), sig);
        it_cur = it;
    }

    if (it == equation.end())
        return;
    else
        it++;

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

void remove_nulls(std::map<int, float> &coef)
{
    std::map<int, float>::iterator it = coef.begin();
    std::vector<int> index_to_remove;

    while (it != coef.end())
    {
        if (it->second == 0)
        {
            index_to_remove.push_back(it->first);
        }
        it++;
    }

    std::vector<int>::iterator it2 = index_to_remove.begin();

    while (it2 != index_to_remove.end())
    {
        coef.erase(*it2);
        it2++;
    }
}

std::map<int, float> parcing(std::string equation)
{
    std::map<int, float> coef;
    int equal;

    equation.erase(remove(equation.begin(), equation.end(), ' '), equation.end());
    equal = equation.find("=");

    get_coefs(coef, equation.substr(0, equal), '+');
    get_coefs(coef, equation.substr(equal + 1), '-');

    remove_nulls(coef);

    return coef;
}
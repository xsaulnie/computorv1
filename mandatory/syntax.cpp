#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

bool incorrect_car(char c)
{
    std::vector<char> cor{'=', '+', '-', 'X', '^', ' ', '*', '.'};
    if (!isdigit(c) && std::find(cor.begin(), cor.end(), c ) == cor.end())
    {
        return true;
    }
    return false;
}

bool sign_after_equal(std::string &equation)
{
    unsigned long pos = equation.find('=');

    if (pos == equation.length() - 1)
        return true;

    if (equation[pos + 1] == '-')
        equation[pos + 1] = '0';
    
    return false;
}

bool remove_space(std::string &eq)
{
    std::string::iterator it = eq.begin();
    while (it != eq.end())
    {
        if (*it == 'X')
        {
            if (*(it + 1) != '^')
                return true;
            if (!isdigit(*(it + 2)))
                return true;
        }

        if (*it == '.')
        {
            if (!isdigit(*(it + 1)))
                return true;
            if (it == eq.begin())
                return true;
            if (!isdigit(*(it - 1)))
                return true;
        }
        it++;
    }
    eq.erase(remove(eq.begin(), eq.end(), ' '), eq.end());

    if (sign_after_equal(eq))
        return true;

    it = eq.begin();
    if (*it == '+' || *it == '=')
        return true;
    else if (*it == '-')
    {
        *it = '0';
        it++;
    }
    while (it != eq.end())
    {
        if (*it == '+' || *it == '-' || *it == '=')
            {
                if (!isdigit(*(it + 1)) || !isdigit(*(it - 1)))
                    return true;
                *it = '|';
            }
        it++;
    }
    return false;
}

bool pointdigit(std::string::iterator &it, bool flag)
{
    while (isdigit(*it))
    {
        it++;
    }
    if (*it == '.')
    {
        if (flag == false)
            return true;
        else
            it++;
        while (isdigit(*it))
        {
            it++;
        }
    }
    return false;
}

bool check_monome(std::string eq)
{
    std::string::iterator it = eq.begin();
    while (it != eq.end())
    {
        if (pointdigit(it, true))
            return true;
        if (it == eq.end() || *it != '*')
            return true;
        else
            it++;
        if (it == eq.end() || *it != 'X')
            return true;
        else
            it++;
        if (it == eq.end() || *it != '^')
            return true;
        else
            it++;
        if (pointdigit(it, false))
            return true;
        if (it == eq.end())
            return false;
        if (*it != '|')
            return true;
        else
            it++;
    }
    if (*(it - 1) == '|')
        return true;
    return false;
}

bool check_syntax(std::string eq)
{
    std::string::difference_type equal = std::count(eq.begin(), eq.end(), '=');

    if (equal != 1)
        return true;
    
    std::string::iterator it = eq.begin();

    while (it != eq.end())
    {
        if (incorrect_car(*it))
            return true;
        it++;
    }

    if (remove_space(eq))
        return true;

    if (check_monome(eq))
    {
        return true;
    }

    return false;
}
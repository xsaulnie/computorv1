#include <stdlib.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

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

void print_monome(std::map<int, float>::iterator it, bool abso)
{
    if (it->first == 0)
    {
        std::cout << ( abso ? abs(it->second) : it->second );
    }
    else if (it->first == 1)
    {
        if (abs(it->second) == 1)
            std::cout << "X";
        else
            std::cout << ( abso ? abs(it->second) : it->second ) << " * X";
    }
    else
    {
        if (abs(it->second) == 1)
            std::cout << "X^2";
        else
            std::cout << ( abso ? abs(it->second) : it->second ) << " * X^" << it->first;
    }
    return ;

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
    print_monome(it, false);
    it++;
    while (it != coef.end())
    {
        std::cout << (it->second < 0 ? " - " : " + ");
        print_monome(it, true);
        it++;
    }
    std::cout << " = 0" << std::endl;
}

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

    std::cout << "monome : " << eq << " index " << index << " value " << value <<std::endl;

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
        std::cout << *it2 << "removed" << std::endl;
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

bool incorrect_car(char c)
{
    std::vector<char> cor{'=', '+', '-', 'X', '^', ' ', '*', '.'};
    if (!isdigit(c) && std::find(cor.begin(), cor.end(), c ) == cor.end())
    {
        //std::cout << "c " << c << " first " << !isdigit(c) <<  " second " << (std::find(cor.begin(), cor.end(), c ) == cor.end()) << std::endl;
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
        if (*it == 'X' && *(it + 1) != ' ' && (it + 1) != eq.end())
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

        if (*it == '^')
        {
            if (!isdigit(*(it + 1)))
                return true;
            if (it == eq.begin())
                return true;
            if (*(it - 1) != 'X')
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
                if ((!isdigit(*(it + 1))  && *(it + 1) != 'X') || (!isdigit(*(it - 1)) && *(it - 1) != 'X'))
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

    std::cout << "syntax" << eq << std::endl;

    while (it != eq.end())
    {
        if (pointdigit(it, true))
            return true;

        if (it == eq.end())
            return false;
        if ((*it != '*' && *it != '|' && *it != 'X'))
            return true;

        if (*it == '*' || *it == 'X')
        {
            if (*it == '*')
            {
                it++;
                if (it == eq.end() || *it != 'X')
                    return true;
                else
                    it++;
            }
            else
                it++;
            if (it == eq.end())
                return false;
            if ((*it != '^' && *it != '|'))
                return true;
            if (*it == '^')
            {
                it++;
                if (pointdigit(it, false))
                    return true;
                if (it == eq.end())
                    return false;
            }
        }
        std::cout << *it << std::endl;
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
    {
        std::cout << "space" << std::endl;
        return true;
    }

    if (check_monome(eq))
    {
        return true;
    }

    return false;
}

int main(int argc, char *argv[])
{
    std::map<int, float> coef;

    if (argc != 2)
    {
        std::cout << "Error : Wrong number of argument" << std::endl;
        exit(1);
    }

    int num = 1326;
    int denum = 546;
    reductible(num, denum);
    std::cout << num << denum << std::endl;
    exit(0);

    std::cout << "computor bonus" << std::endl;

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
    std::cout << "exit" << std::endl;
    return 0;
}
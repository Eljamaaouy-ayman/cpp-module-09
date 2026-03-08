#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2)
        return (std::cerr << "Error ./RPN [arg]" << std::endl, 0);
    if (!parse_arg(av[1]))
        return 0;
    std::stack<int> calc;
    int a, b;
    for (int i = 0; av[1][i]; i++)
    {
        if ((av[1][i] < '0' || av[1][i] > '9') && av[1][i] > 32)
        {
            if (calc.size() < 2)
                return (std::cout << "Error" << std::endl, 0);
            else
            {
                a = calc.top();
                calc.pop();
                b = calc.top();
                calc.pop();
                if (av[1][i] == '*')
                    calc.push(b * a);
                if (av[1][i] == '+')
                    calc.push(b + a);
                if (av[1][i] == '-')
                    calc.push(b - a);
                if (av[1][i] == '/')
                    calc.push(b / a);
            }
        }
        else if (av[1][i] <= 32)
            continue;
        else
            calc.push(av[1][i] - '0');
    }
    std::cout << calc.top() << std::endl;
    return 1;
}
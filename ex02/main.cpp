#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    try
    {
        if(!av || ac <= 1)
            throw std::invalid_argument("Usage: ./PmergeMe [n1] [n2] [n3] [...] [n]");
        processInput(ac, av);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
    
}
#include "PmergeMe.hpp"

template <typename T>
void restoreB(T& a, T& b, T& bSorted){
    int n = a.size();

    for(int i = 0;i < n; i++){
        int idx = a[i].getIndex();
        bSorted.push_back(b[idx]);
    }
    if (static_cast<int>(b.size()) > n)
        bSorted.push_back(b[n]);
}

template <typename T>
void makePairs(T& nums, T& a, T& b)
{
    int n = nums.size() - 1;
    for(int i = 0; i < n; i += 2){
        if (nums[i] < nums[i + 1])
        {
            nums[i + 1].saveIndex(a.size());
            a.push_back(nums[i + 1]);
            b.push_back(nums[i]);
        }
        else
        {
            nums[i].saveIndex(a.size());
            a.push_back(nums[i]);
            b.push_back(nums[i + 1]);
        }
    }
    if ((n + 1) % 2 != 0)
        b.push_back(nums[n]);
}


template <typename T>
void mergeInsert(T& nums)
{
    if (nums.size() < 2)
        return ;
    T a;
    T b;
    T restoredB;

    makePairs(nums, a, b);
    mergeInsert(a);
    restoreB(a, b, restoredB);

    nums.clear();
    nums.push_back(restoredB[0]);

    int previousJacobsN = 0;
    int u = 0;
    const int restBSize = restoredB.size();
    const int aSize = a.size();

    for(int k = 0; previousJacobsN < restBSize - 1; k++)
    {
        int currentJacobsN = t_sequence(k);
        while (u < currentJacobsN && u < aSize)
            nums.push_back(a[u++]);
        int m = std::min(currentJacobsN + 1, restBSize);
        for(int i = m, j = 0;i > previousJacobsN + 1; i--, j++){
            typename T::iterator it = std::lower_bound(nums.begin(), nums.end() - j, restoredB[i - 1]);
            nums.insert(it, restoredB[i - 1]);
        }
        previousJacobsN = currentJacobsN;
    }
    for(;u < aSize; u++)
        nums.push_back(a[u]);
}


template <typename T>
void isSorted(T& seq)
{
    for(int i = 1; i < seq.size(); i++)
    {
        if (seq[i] < seq[i - 1])
            throw std::runtime_error("warning: sequence not properly sorted!");
    }
}

template <typename T>
double sortAndTime(T& seq)
{
    double start = getCurrentTimeMs();
    mergeInsert(seq);
    double end = getCurrentTimeMs();
    return (end - start);
}

int Int::compCount = 0;

Int::Int(int val) : c(0), value(val)
{
    std::memset(indexs, 0, sizeof(indexs));
}

Int::Int(const Int& other) : c(other.c), value(other.value)
{
	std::memcpy(indexs, other.indexs, sizeof(indexs));
}

Int& Int::operator=(const Int& other)
{
    if (this != &other){
        value = other.value;
        c = other.c;
        std::memcpy(indexs, other.indexs, sizeof(indexs));
    }
    return (*this);
}

Int::Int(const std::string& s) : c(0)
{
    std::memset(indexs, 0, sizeof(indexs));
    value = atoi(s.c_str());
}

Int::~Int(){}

int Int::getValue()
{return value;}

int Int::getIndex()
{
    if (c > 0)
        return (indexs[--c]);
    return (-1);
}

void Int::saveIndex(int idx)
{
    if (c < 35)
        indexs[c++] = idx;
}

bool Int::operator<(const Int& other)
{
    compCount++;
    return (this->value < other.value);
}

bool Int::operator==(const Int& other)
{
    return (this->value == other.value);
}

bool isValidArg(std::string arg)
{
    double toDouble;

    if (arg.empty() || (arg.find_first_not_of("0123456789") != std::string::npos))
        return false;
    toDouble = std::strtod(arg.c_str(), 0);
    if (toDouble > std::numeric_limits<int>::max())
        return false;
    return true;
}

size_t t_sequence(size_t k){
    size_t powerTwo = (1 << k);
    int sign = (k % 2 == 0) ? 1 : -1;
    size_t jacobNumber = (powerTwo + sign) / 3;
    return jacobNumber;
}

double getCurrentTimeMs()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000000 + time.tv_usec);
}

void display (std::vector<Int>& nums, int status)
{
    std::cout << (status ? "before: " : "after: ");
    for(size_t i = 0;i < nums.size(); i++)
        std::cout << nums[i].getValue() << " ";
    std::cout << std::endl;
}

void displayTiming(size_t size, double vectTime, double deqTime, int compars)
{
    std::cout << "Time to process a range of " << size
            << " elements with std::vector : " << vectTime << "us" << std::endl;
    std::cout << "Time to process a range of " << size
            << " elements with std::deque : " << deqTime << "us" << std::endl;

    std::cout << std::endl;
    std::cout << "number of comparaisons : " << compars << std::endl;
}

void parseArguments(int ac, char **av, std::vector<Int>& vect, std::deque<Int>& deq)
{
    for (int i = 1; i < ac; i++)
    {
        if (!isValidArg(av[i]))
            throw std::invalid_argument("Error: invalid argument!");
        Int nb(av[i]);

        if (std::find(vect.begin(), vect.end(), nb) != vect.end())
            throw std::invalid_argument("Error: duplicate number!");
        vect.push_back(nb);
        deq.push_back(nb);
    }
}

void processInput(int ac, char **av)
{
    std::vector<Int> vect;
    std::deque<Int> deq;

    parseArguments(ac, av, vect, deq);
    display(vect, 1);
    double vectTime = sortAndTime(vect);
    Int::compCount = 0;
    double deqTime = sortAndTime(deq);
    display(vect, 0);
    displayTiming(vect.size(), vectTime, deqTime, Int::compCount);

    isSorted(vect);
    isSorted(deq);
}



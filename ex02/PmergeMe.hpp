#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <cstring>
#include <sys/time.h>

class Int {
    public:
        static int compCount;

        Int (int val = 0);
        Int (const Int& other);
        Int (const std::string& s);
        ~Int();

        bool operator< (const Int& other);
        bool operator== (const Int& other);
        Int& operator=(const Int& other);


        void saveIndex(int index);
        int getIndex();
        int getValue();

    private:
        int value;
        int indexs[35];
        unsigned char c;
};

template <typename T>
void mergeInsert(T& nums);

template <typename T>
void makePairs(T& nums, T& a, T& b);

template <typename T>
void restoreB(T& a, T& b, T& bSorted);

template <typename T>
double sortAndTime(T& seq);

template <typename T>
void isSorted(T& seq);

void processInput(int ac, char **av);
bool isValidArg(std::string arg);
size_t t_sequence(size_t size);
double getCurrentTimeMs();
void display(std::vector<Int>& vec, int status);
void displayTiming(size_t size, double timeVec, double timeDeq, int comp);

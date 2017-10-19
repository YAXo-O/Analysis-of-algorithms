#include <chrono>
#include <iostream>
#include <random>
#include <cstdlib>
#include "tests.h"
#include "array.h"
#include "sorts.h"

/* printing utils */
void printSep(unsigned len = 60)
{
    for(unsigned i = 0; i < len; i++)
        std::cout << "-";
    std::cout << std::endl;
}

void launchTests()
{
    // Insertion Sort tests
    insertionTest(10);
    insertionTest(100);
    insertionTest(1000);
}

template<typename T>
long long insertionTest(Array<T> &arr)
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    insertionSort(arr);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return ((long long)(end - start).count())/repetitions;
}

void insertionTest(size_t size)
{
    printSep();
    char str[5];
    itoa(size, str, 10);
    std::cout << "Insertion Sort array len = " + std::string(str) << std::endl;

    long long int time = 0;
    {
        Array<int> arr(size);
        for(size_t i = 0; i < size; i++)
            arr[i] = i;
        for(unsigned int i = 0; i < repetitions; i++)
            time += insertionTest(arr);
    }
    printSep(30);
    std::cout << "Best case scenario: " << time << std::endl;

    time = 0;
    std::mt19937 gen(0);
    std::uniform_int_distribution<int> uid(-32000, 32000);
    for(unsigned int i = 0; i < repetitions; i++)
    {
        Array<int> arr(size);
        for(size_t i = 0; i < size; i++)
            arr[i] = uid(gen);

        time += insertionTest(arr);
    }
    std::cout << "Avrg case: " << time << std::endl;

    time = 0;
    for(unsigned int i = 0; i < repetitions; i++)
    {
        Array<int> arr(size);
        for(size_t i = 0; i < size; i++)
            arr[i] = size - i;

        time += insertionTest(arr);
    }
    std::cout << "Worst case scenario: " << time << std::endl;
}

#include <chrono>
#include <iostream>
#include <random>
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
    std::cout << "Tests per round: " << repetitions << std::endl;

    // Insertion Sort tests
    insertionTest(10);
    for(int i = 100; i <= 1000; i += 100)
        insertionTest(i);

    // BSTree-based sort
    bstTest(10);
    for(int i = 100; i <= 1000; i+= 100)
        bstTest(i);

    // LSD sort
    lsdTest(10);
    for(int i = 100; i <= 1000; i+= 100)
        lsdTest(i);
}

template<typename T>
long long sortTest(Array<T> &arr, void (* sort)(Array<T> &))
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    sort(arr);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    return ((long long)(end - start).count())/repetitions;
}

void insertionTest(size_t size)
{
    printSep();
    std::cout << "Insertion Sort array len = " << size << std::endl;

    long long int time = 0;
    {
        Array<int> arr(size);
        for(size_t i = 0; i < size; i++)
            arr[i] = i;
        for(unsigned int i = 0; i < repetitions; i++)
            time += sortTest(arr, insertionSort);
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

        time += sortTest(arr, insertionSort);
    }
    std::cout << "Avrg case: " << time << std::endl;

    time = 0;
    for(unsigned int i = 0; i < repetitions; i++)
    {
        Array<int> arr(size);
        for(size_t i = 0; i < size; i++)
            arr[i] = size - i;

        time += sortTest(arr, insertionSort);
    }
    std::cout << "Worst case scenario: " << time << std::endl;
}


template<typename T>
void createBalancedTree(BinarySearchTree<T> &tree, T start, T end)
{
    if((end - start) <= 1)
        return;

    T value = (start + end)/2;
    tree.insertValue(value);

    createBalancedTree(tree, start, (start+end)/2);
    createBalancedTree(tree, (start+end)/2, end);
}

void bstTest(size_t size)
{
    printSep();
    std::cout << "Binary Search Tree Based Sort array len = " << size << std::endl;

    long long int time = 0;
    {
        for(unsigned int i = 0; i < repetitions; i++)
        {
            BinarySearchTree<int> tree;
            createBalancedTree(tree, 0, int(size));
            Array<int> arr(size);
            tree.widthWriteToArray(arr);
            time += sortTest(arr, BSTSort);
        }
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

        time += sortTest(arr, BSTSort);
    }
    std::cout << "Avrg case: " << time << std::endl;

    time = 0;
    for(unsigned int i = 0; i < repetitions; i++)
    {
        Array<int> arr(size);
        for(size_t i = 0; i < size; i++)
            arr[i] = i;

        time += sortTest(arr, BSTSort);
    }
    std::cout << "Worst case scenario: " << time << std::endl;
}

// LSD Test

void lsdTest(size_t size)
{
    printSep();
    std::cout << "LSD sort len = " << size << std::endl;

    long long int time = 0;
    std::mt19937 gen(0);
    std::uniform_int_distribution<int> uid(0, 999);
    for(unsigned int i = 0; i < repetitions; i++)
    {
        uint16_t *arr = new uint16_t[size];
        for(size_t i = 0; i < size; i++)
            arr[i] = uid(gen);

        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        LSDSort(arr, size);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

        time += ((long long)(end - start).count())/repetitions;
        delete[] arr;
    }
    std::cout << "Avrg case: " << time << std::endl;
}

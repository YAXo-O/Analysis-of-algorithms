#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include <cmath>
#include "array.h"
#include "binarysearchtree.h"

/* Insertion Sort */

// Shifts array rightways while searching for place to put array[id]
template<typename T>
void shiftRightInplace(Array<T> &array, int id)
{
    T tmp = array[id];
    int i = id - 1;
    for(;(i >= 0) && (array[i] > tmp); i--)
        array[i+1] = array[i];

    array[i+1] = tmp;
}

template<typename T>
void insertionSort(Array<T> &array)
{
    // Picking first element from "non-sorted" sub-array
    for(size_t sortedBorder = 1; sortedBorder < array.count(); sortedBorder++)
        shiftRightInplace(array, sortedBorder);
}

/* Binary Search Tree Based Sort */

template<typename T>
void BSTSort(Array<T> &array)
{
    BinarySearchTree<T> BST(array);
    BST.writeToArray(array);
}

/* Least Significant Digit radix sort */

const unsigned char decade = 2; // Maximal decades per array element
const unsigned char decadeValue = 9; // Maximal decade value

inline unsigned char getDigit(uint16_t number, size_t digitIndex)
{
    return (number/uint16_t(pow(decadeValue + 1, digitIndex)))%(decadeValue + 1);
}

void LSDSort(uint16_t *array, size_t size)
{
    uint16_t counting[decadeValue + 1];
    uint16_t *result = new uint16_t[size];

    for(unsigned char i = 0; i < decade; i++)
    {
        for(unsigned char j = 0; j <= decadeValue; j++)
            counting[j] = 0;
        for(size_t j = 0; j < size; j++)
            counting[getDigit(array[j], i)]++;

        unsigned char count = 0;

        for(unsigned char j = 0; j <= decadeValue; j++)
        {
            unsigned char tmp = counting[j];
            counting[j] = count;
            count += tmp;
        }
        for(size_t j = 0; j < size; j++)
        {
            unsigned char d = getDigit(array[j], i);
            result[counting[d]] = array[j];
            counting[d]++;
        }
    }

    std::memcpy(array, result, 2*size);
    delete[] result;
}

#endif // SORTS_H

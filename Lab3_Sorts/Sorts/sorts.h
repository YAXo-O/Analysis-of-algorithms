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

inline unsigned char getDigit(uint16_t number, size_t digitIndex);
void LSDSort(uint16_t *array, size_t size);

#endif // SORTS_H

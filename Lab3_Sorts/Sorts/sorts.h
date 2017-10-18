#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include "array.h"
#include "binarysearchtree.h"

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

template<typename T>
void BSTSort(Array<T> &array)
{
    BinarySearchTree<T> BST(array);
    BST.writeToArray(array);
}

#endif // SORTS_H

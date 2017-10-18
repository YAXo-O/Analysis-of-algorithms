#ifndef SORTS_H
#define SORTS_H

#include <iostream>
#include "array.h"

// [ 0 1 5 4 6 ]
//   0 1 2 3 4
// 2 -> 2 ==>
// [ 0 1 6 5 4 ]
//   0 1 2 3 4

// Shifts array rightways starting with array[id] up to array[rightEnd] including
// Element array[rightEnd] of original array is stored in array[id];
template<typename T>
void shiftRightInplace(Array<T> &array, size_t id, size_t rightEnd)
{
    T tmp = array[rightEnd];
    for(auto i = rightEnd; i > id; i--)
        array[i] = array[i-1];
    array[id] = tmp;
}

template<typename T>
void insertionSort(Array<T> &array)
{
    // Picking first element from "non-sorted" sub-array
    for(size_t sortedBorder = 1; sortedBorder < array.count(); sortedBorder++)
    {
        // Searching for its place in a "sorted" sub-array
        size_t i = 0;
        for(; i < sortedBorder && array[i] < array[sortedBorder]; i++);
        shiftRightInplace(array, i, sortedBorder);
    }
}


#endif // SORTS_H

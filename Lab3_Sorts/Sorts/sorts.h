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


#endif // SORTS_H

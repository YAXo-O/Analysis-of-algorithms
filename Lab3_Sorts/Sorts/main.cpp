#include <iostream>
#include "array.h"
#include "sorts.h"

using namespace std;

template<typename T>
void printArray(const Array<T> &array)
{
    std::cout << "[ ";
    for(auto i: array)
        std::cout << i << " ";
    std::cout << "];" << std::endl;
}

int main()
{
    Array<int> a1 = {-10, 10, 8, 7, 1, 4, 3, 11, 2, 1, -8, 4};
    printArray(a1);
    insertionSort(a1);
    printArray(a1);

    return 0;
}

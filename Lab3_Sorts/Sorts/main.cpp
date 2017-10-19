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
    uint16_t arr[] = {10, 221, 1, 650, 16};
    size_t arrLen = sizeof(arr)/2;
    LSDSort(arr, arrLen);

    std::cout << "[ ";
    for(size_t i = 0; i < arrLen; i++)
        std::cout << arr[i] << " ";
    std::cout << "]" << std::endl;


    return 0;
}

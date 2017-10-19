#include "sorts.h"

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

#include <iostream>
#include "Matrix.h"

int main()
{

	const int size = 401;

	Matrix m1(size, size);
	Matrix m2(size, size);
	int count = 0;
	for(int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			m1.at(i, j) = count++;
			m2.at(i, j) = size*size - count;
		}

	Matrix res = m1.winograd(m2);
	Matrix res2 = m1.winogradC(m2);

	return 0;
}
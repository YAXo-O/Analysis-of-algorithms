#include <iostream>
#include "Matrix.h"

int main()
{
	Matrix m1(2, 2);
	m1.fill(0);
	m1.at(0, 1) = 1;
	m1.at(1, 0) = 1;
	Matrix m2(2, 2);
	m2.fill(1);

	Matrix res = m1*m2;
	res.print();

	return 0;
}
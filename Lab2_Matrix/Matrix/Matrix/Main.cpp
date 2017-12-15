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
	std::cout << "m1: " << std::endl;
	m1.print();
	std::cout << "m2: " << std::endl;
	m2.print();

	Matrix res = m1.winograd(m2);
	Matrix res2 = m1.winogradC(m2);

	return 0;
}
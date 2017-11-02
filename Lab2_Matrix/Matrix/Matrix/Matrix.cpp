#include <cstring>
#include <iostream>
#include "Matrix.h"

extern "C" void matricesMultiply(int64_t *a, int64_t *b, int64_t *c, size_t l, size_t m, size_t n);

Matrix::Matrix(size_t _dimX, size_t _dimY): data(new int64_t[_dimX*_dimY]), dimX(_dimX), dimY(_dimY)
{
}

Matrix::Matrix(const Matrix &other): data(new int64_t[other.dimX*other.dimY]), dimX(other.dimX), dimY(other.dimY)
{
	memcpy(data, other.data, sizeof(int64_t)*dimX*dimY);
}

Matrix::Matrix(Matrix &&other): data(other.data), dimX(other.dimX), dimY(other.dimY)
{
	other.data = nullptr;
	other.dimX = other.dimY = 0;
}

Matrix::~Matrix()
{
	if(data)
		delete[] data;
}

Matrix Matrix::operator*(const Matrix &other) throw(std::invalid_argument)
{
	if (other.dimY != dimX || data == nullptr || other.data == nullptr)
		throw std::invalid_argument("Matrices sizes mismatch");

	Matrix res(other.dimX, dimY);
	matricesMultiply(data, other.data, res.data, dimY, dimX, other.dimX);

	return res;
}

const int64_t & Matrix::at(size_t i, size_t j) const throw(std::out_of_range)
{
	if (i >= dimX || j >= dimY || data == nullptr)
		throw std::out_of_range("Matrix out of range");

	return data[j*dimX + i];
}

int64_t & Matrix::at(size_t i, size_t j) throw(std::out_of_range)
{
	if (i >= dimX || j >= dimY || data == nullptr)
		throw std::out_of_range("Matrix out of range");

	return data[j*dimX + i];
}

void Matrix::fill(int64_t value)
{
	if (data)
	{
		size_t size = dimX*dimY;
		for (size_t i = 0; i < size; i++)
			data[i] = value;
	}
}

void Matrix::print()
{
	if (data)
	{
		for (size_t j = 0; j < dimY; j++)
		{
			for (size_t i = 0; i < dimX; i++)
				std::cout << data[i + j*dimX] << " ";
			std::cout << std::endl;
		}
	}
	else
		std::cout << "No data";
}


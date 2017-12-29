#include <cstring>
#include <iostream>
#include <ctime>
#include <chrono>
#include "Matrix.h"

struct winograd_t
{
	int64_t *g, *h, *r;
	size_t a, b, c ;
	int64_t *rowFactor, *colFactor;

	winograd_t(int64_t *_g = nullptr, int64_t *_h = nullptr, int64_t *_r = nullptr,
		size_t _a = 0, size_t _b = 0, size_t _c = 0): g(_g), h(_h), r(_r), a(_a), b(_b), c(_c),
			rowFactor(new int64_t[_a]), colFactor(new int64_t[_c])
	{
	}

	~winograd_t()
	{
		delete[] rowFactor;
		delete[] colFactor;
	}
};

extern "C" void matricesMultiply(int64_t *a, int64_t *b, int64_t *c, size_t l, size_t m, size_t n);
extern "C" void winogradMasm(winograd_t *data);

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

Matrix Matrix::operator*(const Matrix &other)// throw(std::invalid_argument)
{
	if (other.dimY != dimX || data == nullptr || other.data == nullptr)
		throw std::invalid_argument("Matrices sizes mismatch");

	Matrix res(other.dimX, dimY);
	matricesMultiply(data, other.data, res.data, dimY, dimX, other.dimX);

	return res;
}

Matrix Matrix::winograd(Matrix &other)// throw(std::invalid_argument)
{
	if (other.dimY != dimX || data == nullptr || other.data == nullptr)
		throw std::invalid_argument("Matrices sizes mismatch");

	Matrix res(other.dimX, dimY);
	winograd_t win(data, other.data, res.data, dimY, dimX, other.dimX);

	std::clock_t start = clock();
	winogradMasm(&win);
	std::cout << "Time: " << difftime(clock(), start) << std::endl;

	/*std::cout << "rowFactor: ";
	for (int i = 0; i < win.a; i++)
		std::cout << win.rowFactor[i] << " ";
	std::cout << std::endl << "colFactor: ";
	for (int i = 0; i < win.c; i++)
		std::cout << win.colFactor[i] << " ";
	std::cout << std::endl << std::endl;
	*/

	/*
	for (int i = 0; i < res.dimX; i++)
	{
		for (int j = 0; j < res.dimY; j++)
			std::cout << res.data[i*dimX + j] << " ";
		std::cout << std::endl;
	}
	*/

	return res;
}

Matrix Matrix::winogradC(Matrix &other)
{
	int a = dimY;
	int b = dimX;
	int c = other.dimX;
	int d = b / 2;
	int *rowFactor = new int[a];
	int *colFactor = new int[c];
	
	for (int i = 0; i < a; i++)
	{
		rowFactor[i] = data[i*dimX] * data[i*dimX + 1];
		for (int j = 1; j < d; j++)
			rowFactor[i] += data[i*dimX + 2 * j] * data[i*dimX + 2 * j + 1];
			
	}

	for (int i = 0; i < c; i++)
	{
		colFactor[i] = other.data[i] * other.data[dimX + i];
		for (int j = 1; j < d; j++)
			colFactor[i] += other.data[2 * j*other.dimX + i] * other.data[(2 * j + 1)*other.dimX + i];
	}

	/*
	std::cout << "rowFactor: ";
	for (int i = 0; i < a; i++)
		std::cout << rowFactor[i] << " ";
	std::cout << std::endl << "colFactor: ";
	for (int i = 0; i < c; i++)
		std::cout << colFactor[i] << " ";
	std::cout << std::endl;
	*/

	Matrix *res = new Matrix(a, c);
	for (int i = 0; i < a; i++)
	{
		for (int j = 0; j < c; j++)
		{
			res->data[i*res->dimX + j] = -rowFactor[i] - colFactor[j];
			for (int k = 0; k < d; k++)
			{
				int valueLeft = (data[i*dimX + 2*k + 1] + other.data[2*k*other.dimX + j]);
				int valueRight = (data[i*dimX + 2 * k] + other.data[(2 * k + 1)*other.dimX + j]);
				res->data[i*res->dimX + j] += valueLeft*valueRight;
			}
		}
	}

	if (b % 2 != 0)
		for (int i = 0; i < a; i++)
			for (int j = 0; j < c; j++)
				res->data[i*res->dimX + j] += data[i*dimX + b - 1] * other.data[(b-1)*other.dimX + j];

	/*
	for (int i = 0; i < res->dimX; i++)
	{
		for (int j = 0; j < res->dimY; j++)
			std::cout << res->data[i*dimX + j] << " ";
		std::cout << std::endl << std::endl;
	}
	*/

	delete[] rowFactor;

	return *res;
}

const int64_t & Matrix::at(size_t i, size_t j) const// throw(std::out_of_range)
{
	if (i >= dimX || j >= dimY || data == nullptr)
		throw std::out_of_range("Matrix out of range");

	return data[j*dimX + i];
}

int64_t & Matrix::at(size_t i, size_t j)// throw(std::out_of_range)
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


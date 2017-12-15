#pragma once

#include <stddef.h>
#include <stdexcept>

class Matrix
{
public:
	Matrix(size_t dimX, size_t dimY);
	Matrix(const Matrix &other);
	Matrix(Matrix &&other);
	~Matrix();

	Matrix operator*(const Matrix &other);// throw(std::invalid_argument); // Ordinary multiplication
	Matrix winograd(Matrix &other);// throw(std::invalid_argument);
	Matrix winogradC(Matrix &other);
	const int64_t &at(size_t i, size_t j) const;// throw(std::out_of_range);
	int64_t &at(size_t i, size_t j);// throw(std::out_of_range);

	void fill(int64_t value);
	void print();

private:
	int64_t *data;
	size_t dimX;
	size_t dimY;

};


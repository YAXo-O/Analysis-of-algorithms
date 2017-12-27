#include <cstring>
#include "matrix.h"

Matrix::Matrix(size_t dimx, size_t dimy): sizex(dimx), sizey(dimy), data(new double[sizex*sizey])
{
}

Matrix::Matrix(const Matrix &other): sizex(other.sizex), sizey(other.sizey), data(new double[sizex*sizey])
{
    std::memcpy(data, other.data, sizex*sizey*sizeof(double));
}

Matrix::Matrix(const Matrix &&other): sizex(other.sizex), sizey(other.sizey), data(new double[sizex*sizey])
{
    std::memcpy(data, other.data, sizex*sizey*sizeof(double));
}

Matrix::Matrix(const QVector3D &vec)
{
    sizex = 4;
    sizey = 1;
    data = new double[4];

    data[0] = vec.x();
    data[1] = vec.y();
    data[2] = vec.z();
    data[3] = 1;
}

Matrix::Matrix(const QVector3D &&vec)
{
    sizex = 4;
    sizey = 1;
    data = new double[4];

    data[0] = vec.x();
    data[1] = vec.y();
    data[2] = vec.z();
    data[3] = 1;
}

Matrix::~Matrix()
{
    delete data;
}

void Matrix::fill(double value)
{
    size_t limit = sizex*sizey;
    for(size_t i = 0; i < limit; i++)
        data[i] = value;
}

void Matrix::loadIdentity()
{
    for(size_t i = 0; i < sizey; i++)
        for(size_t j = 0; j < sizex; j++)
            data[j + i*sizex] = (i == j) ? 1 : 0;
}

QVector3D Matrix::toVector() throw(std::out_of_range)
{
    if(sizex*sizey < 3)
        throw std::out_of_range("matrix is too small!");

    return QVector3D(data[0], data[1], data[2]);
}

double &Matrix::at(size_t x, size_t y) throw(std::out_of_range)
{
    if(x >= sizex || y >= sizey)
        throw std::out_of_range("Incorrect ids");

    return data[x + y*sizex];
}

Matrix &Matrix::operator=(const Matrix &other)
{
    sizex = other.sizex;
    sizey = other.sizey;
    data = new double[sizex*sizey];

    std::memcpy(data, other.data, sizex*sizey*sizeof(double));

    return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) throw(std::invalid_argument)
{
    if(sizex != other.sizex || sizey != other.sizey)
        throw std::invalid_argument("Incorrect matrixes sizes");

    size_t limits = sizex*sizey;
    for(size_t i = 0; i < limits; i++)
        data[i] += other.data[i];

    return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) throw(std::invalid_argument)
{
    if(sizex != other.sizex || sizey != other.sizey)
        throw std::invalid_argument("Incorrect matrixes sizes");

    size_t limits = sizex*sizey;
    for(size_t i = 0; i < limits; i++)
        data[i] -= other.data[i];

    return *this;
}

Matrix &Matrix::operator*=(double scalar)
{
    size_t limits = sizex*sizey;
    for(size_t i = 0; i < limits; i++)
        data[i] *= scalar;

    return *this;
}

Matrix &Matrix::operator/=(double scalar)
{
    size_t limits = sizex*sizey;
    for(size_t i = 0; i < limits; i++)
        data[i] *= scalar;

    return *this;
}

Matrix &Matrix::operator*=(Matrix &other) throw(std::invalid_argument)
{
    operator=(operator*(other));

    return *this;
}

Matrix Matrix::operator+(const Matrix &other) throw(std::invalid_argument)
{
    if(sizex != other.sizex || sizey != other.sizey)
        throw std::invalid_argument("Incorrect matrixes sizes");

    size_t limits = sizex*sizey;
    Matrix result(*this);
    for(size_t i = 0; i < limits; i++)
        result.data[i] = other.data[i] + data[i];

    return result; // Вот в этот момент лучше семинтика перемещения, чем копирование
}

Matrix Matrix::operator*(double scalar)
{
    size_t limits = sizex*sizey;
    Matrix result(*this);
    for(size_t i = 0; i < limits; i++)
        result.data[i] = data[i] * scalar;

    return result;
}

Matrix Matrix::operator*(Matrix &other) throw(std::invalid_argument)
{
    if(sizex != other.sizey)
        throw std::invalid_argument("Incompatable matrixes sizes");

    Matrix result(other.sizex, sizey);
    result.fill(0);

    for(size_t i = 0; i < sizey; i++)
        for(size_t j = 0; j < other.sizex; j++)
            for(size_t k = 0; k < sizex; k++)
                result.at(j, i) += at(k, i)*other.at(j, k);

    return result;
}

Matrix &Matrix::transpose() throw(std::invalid_argument)
{
    if(sizex != sizey)
        throw std::invalid_argument("Non-square matrix to be transformed");

    for(size_t i = 0; i < sizex; i++)
        for(size_t j = i+1; j < sizex; j++)
        {
            double tmp = at(j, i);
            at(j, i) = at(i, j);
            at(i, j) = tmp;
        }

    return *this;
}

Matrix &Matrix::reverse() throw(std::invalid_argument)
{
    transpose();
    operator/=(determinator());

    return *this;
}

double Matrix::determinator() throw(std::out_of_range)
{
    if(sizex != sizey || sizex != 3)
        throw std::out_of_range("Determinators for square 3x3 matrixes only");

    return at(0, 0)*(at(1, 1)*at(2, 2) - at(1, 2)*at(2, 1)) - at(1, 0)*(at(0, 1)*at(2, 2) - at(2, 1)*at(0, 2)) +
            at(2, 0)*(at(0, 1)*at(1, 2) - at(0, 2)*at(1, 1));
}

#ifdef DEBUG
#include <iostream>
void Matrix::print()
{
    for(size_t i = 0; i < sizex; i++)
    {
        for(size_t j = 0; j < sizey; j++)
            std::cout << data[i + j*sizex] << " ";
        std::cout << std::endl;
    }
}
#endif

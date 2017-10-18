#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>
#include <stdexcept>
#include <cstring>

template<typename T>
class Array
{
public:
    Array(size_t size);
    Array(const std::initializer_list<T> &list);
    Array(const Array &other);
    ~Array();

    void fill(T &value);
    void fill(T &&value);

    Array<T> operator=(const Array<T> &other);
    T &operator[](size_t id) throw(std::out_of_range);
    const T &operator[](size_t id) const throw(std::out_of_range);

    T *begin() const;
    T *end() const;

    size_t count() const;

private:
    size_t size;
    T *data;

};

template<typename T>
Array<T>::Array(size_t _size): size(_size), data(new T[size])
{
}

template<typename T>
Array<T>::Array(const std::initializer_list<T> &list): size(list.size()), data(new T[size])
{
    std::memcpy(data, list.begin(), size*sizeof(T));
}

template<typename T>
Array<T>::Array(const Array<T> &other)
{
    delete[] data;
    size = other.size;
    data = new T[size];
    std::memcpy(data, other.data, size*sizeof(T));
}

template<typename T>
Array<T>::~Array()
{
    delete[] data;
}

template<typename T>
void Array<T>::fill(T &value)
{
    for(size_t i = 0; i < size; i++)
        data[i] = value;
}

template<typename T>
void Array<T>::fill(T &&value)
{
    fill(value);
}

template<typename T>
Array<T> Array<T>::operator=(const Array<T> &other)
{
    delete data;
    size = other.size;
    data = new T[size];
    std::memcpy(data, other.data, size*sizeof(T));
}

template<typename T>
T &Array<T>::operator[](size_t id) throw(std::out_of_range)
{
    if(id >= size)
        throw std::out_of_range("Access to non-existing array member");

    return data[id];
}

template<typename T>
const T &Array<T>::operator[](size_t id) const throw(std::out_of_range)
{
    return operator[](id);
}


template<typename T>
T *Array<T>::begin() const
{
    return data;
}

template<typename T>
T *Array<T>::end() const
{
    return data + size;
}

template<typename T>
size_t Array<T>::count() const
{
    return size;
}

#endif // ARRAY_H

#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <stdexcept>
#include <algorithm>

template <class T>
class Vector
{
private:
    T* arr;
    int currsize;
    int capacity;

    void resize(int new_capacity)
    {
        T* narr = new T[new_capacity];
        for (int i = 0; i < currsize; i++)
        {
            narr[i] = arr[i];
        }
        delete[] arr;
        arr = narr;
        capacity = new_capacity;
    }

public:
    Vector(int n = 1)
    {
        if (n <= 0) n = 1;
        arr = new T[n];
        currsize = 0;
        capacity = n;
    }

    ~Vector()
    {
        delete[] arr;
    }

    Vector(const Vector& other)
        : arr(new T[other.capacity]), currsize(other.currsize), capacity(other.capacity)
    {
        for (int i = 0; i < currsize; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    Vector& operator=(const Vector& other)
    {
        if (this != &other)
        {
            delete[] arr;
            capacity = other.capacity;
            currsize = other.currsize;
            arr = new T[capacity];
            for (int i = 0; i < currsize; i++)
            {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    Vector(Vector&& other) noexcept
        : arr(other.arr), currsize(other.currsize), capacity(other.capacity)
    {
        other.arr = nullptr;
        other.currsize = other.capacity = 0;
    }

    Vector& operator=(Vector&& other) noexcept
    {
        if (this != &other)
        {
            delete[] arr;
            arr = other.arr;
            currsize = other.currsize;
            capacity = other.capacity;
            other.arr = nullptr;
            other.currsize = other.capacity = 0;
        }
        return *this;
    }

    int getsize() const { return currsize; }
    int getcapacity() const { return capacity; }
    bool empty() const { return currsize == 0; }

    const T& operator[](int index) const
    {
        if (index < 0 || index >= currsize)
            throw std::out_of_range("Vector index out of range");
        return arr[index];
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= currsize)
            throw std::out_of_range("Vector index out of range");
        return arr[index];
    }

    void push_back(const T& value)
    {
        if (currsize == capacity)
        {
            resize(capacity * 2);
        }
        arr[currsize++] = value;
    }

    void pop_back()
    {
        if (empty()) throw std::out_of_range("Vector is empty");
        currsize--;
        if (currsize > 0 && currsize <= capacity / 4)
        {
            resize(capacity / 2);
        }
    }

    T remove_at(int index)
    {
        if (index < 0 || index >= currsize)
            throw std::out_of_range("Vector index out of range");
        T k = arr[index];
        for (int i = index; i < currsize - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        currsize--;
        if (currsize > 0 && currsize <= capacity / 4)
        {
            resize(capacity / 2);
        }
        return k;
    }

    void clear() { currsize = 0; }
};

#endif
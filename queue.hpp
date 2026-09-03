#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <stdexcept>

template <class T>
class Queue
{
private:
    int _rear;
    int _front;
    int _currsize;
    int _capacity;
    T *arr;

    void resize(int new_capacity)
    {
        T *narr = new T[new_capacity];
        for (int i = 0; i < _currsize; i++)
        {
            narr[i] = arr[(_front + i) % _capacity];
        }
        delete[] arr;
        arr = narr;
        _front = 0;
        _rear = _currsize;
        _capacity = new_capacity;
    }

public:
    Queue(int n = 1)
    {
        if (n <= 0) n = 1;
        arr = new T[n];
        _rear = _front = 0;
        _currsize = 0;
        _capacity = n;
    }

    ~Queue()
    {
        delete[] arr;
    }

    Queue(const Queue& other)
    {
        _capacity = other._capacity;
        _currsize = other._currsize;
        _front = 0;
        _rear = _currsize;
        arr = new T[_capacity];
        for (int i = 0; i < _currsize; i++)
        {
            arr[i] = other.arr[(other._front + i) % other._capacity];
        }
    }

    Queue& operator=(const Queue& other)
    {
        if (this != &other)
        {
            delete[] arr;
            _capacity = other._capacity;
            _currsize = other._currsize;
            _front = 0;
            _rear = _currsize;
            arr = new T[_capacity];
            for (int i = 0; i < _currsize; i++)
            {
                arr[i] = other.arr[(other._front + i) % other._capacity];
            }
        }
        return *this;
    }

    Queue(Queue&& other) noexcept
        : arr(other.arr), _front(other._front), _rear(other._rear),
          _currsize(other._currsize), _capacity(other._capacity)
    {
        other.arr = nullptr;
        other._front = other._rear = other._currsize = other._capacity = 0;
    }

    Queue& operator=(Queue&& other) noexcept
    {
        if (this != &other)
        {
            delete[] arr;
            arr = other.arr;
            _front = other._front;
            _rear = other._rear;
            _currsize = other._currsize;
            _capacity = other._capacity;
            other.arr = nullptr;
            other._front = other._rear = other._currsize = other._capacity = 0;
        }
        return *this;
    }

    int size() const { return _currsize; }
    int capacity() const { return _capacity; }
    bool empty() const { return _currsize == 0; }

    const T& front() const
    {
        if (empty()) throw std::out_of_range("Queue is empty");
        return arr[_front];
    }

    T& front()
    {
        if (empty()) throw std::out_of_range("Queue is empty");
        return arr[_front];
    }

    const T& back() const
    {
        if (empty()) throw std::out_of_range("Queue is empty");
        return arr[(_rear - 1 + _capacity) % _capacity];
    }

    T& back()
    {
        if (empty()) throw std::out_of_range("Queue is empty");
        return arr[(_rear - 1 + _capacity) % _capacity];
    }

    void enqueue(const T& element)
    {
        if (_currsize == _capacity)
        {
            resize(_capacity * 2);
        }
        arr[_rear] = element;
        _rear = (_rear + 1) % _capacity;
        _currsize++;
    }

    T dequeue()
    {
        if (empty()) throw std::out_of_range("Queue is empty");
        T r = arr[_front];
        _front = (_front + 1) % _capacity;
        _currsize--;
        if (_currsize > 0 && _currsize <= _capacity / 4)
        {
            resize(_capacity / 2);
        }
        return r;
    }
};

#endif
#ifndef __HEAP_HPP__
#define __HEAP_HPP__

#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Heap
{
protected:
    std::vector<T> _arr;
    int _size;
    int _capacity;

    static void swap(T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    int left(int index) const { return 2 * index + 1; }
    int right(int index) const { return 2 * index + 2; }
    int parent(int index) const { return (index - 1) / 2; }

    void shiftUp(int i)
    {
        while (i > 0 && _arr[parent(i)] < _arr[i])
        {
            swap(_arr[parent(i)], _arr[i]);
            i = parent(i);
        }
    }

    void maxHeapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < _size && _arr[l] > _arr[largest])
            largest = l;
        if (r < _size && _arr[r] > _arr[largest])
            largest = r;

        if (largest != i)
        {
            swap(_arr[i], _arr[largest]);
            maxHeapify(largest);
        }
    }

public:
    Heap() : _size(0), _capacity(0) {}

    explicit Heap(const std::vector<T>& a)
        : _arr(a), _size(static_cast<int>(a.size())), _capacity(static_cast<int>(a.size())) {}

    int size() const { return _size; }
    bool empty() const { return _size == 0; }
    const std::vector<T>& array() const { return _arr; }
    std::vector<T>& array() { return _arr; }

    void buildHeap()
    {
        for (int i = (_size - 1) / 2; i >= 0; i--)
            maxHeapify(i);
    }

    void heapSort()
    {
        int original_size = _size;
        buildHeap();
        for (int i = _size - 1; i >= 0; i--)
        {
            swap(_arr[0], _arr[i]);
            _size--;
            maxHeapify(0);
        }
        _size = original_size;
    }

    void insertKey(const T& data)
    {
        if (_size == _capacity)
        {
            _arr.push_back(data);
            _size++;
            _capacity++;
        }
        else
        {
            _arr[_size++] = data;
        }
        shiftUp(_size - 1);
    }

    T deleteMax()
    {
        if (_size <= 0) throw std::out_of_range("Heap is empty");
        T max = _arr[0];
        swap(_arr[0], _arr[_size - 1]);
        _size--;
        maxHeapify(0);
        return max;
    }

    const T& max() const
    {
        if (_size <= 0) throw std::out_of_range("Heap is empty");
        return _arr[0];
    }

    void print() const
    {
        for (int i = 0; i < _size; i++)
        {
            // Requires T to be streamable
        }
    }
};

#endif
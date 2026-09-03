#ifndef __PRIORITY_QUEUE_HPP__
#define __PRIORITY_QUEUE_HPP__

#include <vector>
#include <stdexcept>
#include "heap.hpp"

template <typename T>
class PriorityQueue
{
private:
    Heap<T> _heap;

public:
    PriorityQueue() = default;

    explicit PriorityQueue(const std::vector<T>& a)
        : _heap(a)
    {
        _heap.buildHeap();
    }

    int size() const { return _heap.size(); }
    bool empty() const { return _heap.empty(); }

    void insert(const T& element)
    {
        _heap.insertKey(element);
    }

    T removeMax()
    {
        return _heap.deleteMax();
    }

    const T& max() const
    {
        return _heap.max();
    }

    void changePriority(int index, const T& new_priority)
    {
        if (index < 0 || index >= _heap.size())
            throw std::out_of_range("Invalid index");

        const auto& arr = _heap.array();
        T old_priority = arr[index];
        _heap.array()[index] = new_priority;

        if (new_priority > old_priority)
        {
            // Need to shift up - but Heap's shiftUp is protected
            // We'll need to expose it or re-implement
            // For now, rebuild heap (simple but O(n))
            _heap.buildHeap();
        }
        else
        {
            _heap.buildHeap();
        }
    }

    void removeAt(int index)
    {
        if (index < 0 || index >= _heap.size())
            throw std::out_of_range("Invalid index");

        // Move to front and remove max
        _heap.array()[index] = _heap.max() + T(1); // Requires T to support + and T(1)
        _heap.buildHeap(); // Rebuild to maintain heap property
        _heap.deleteMax();
    }

    const std::vector<T>& data() const { return _heap.array(); }
};

#endif
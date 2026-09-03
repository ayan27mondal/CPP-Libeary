#ifndef __STACK_USING_LINKEDLIST_HPP__
#define __STACK_USING_LINKEDLIST_HPP__

#include <stdexcept>
#include "linkedlist.hpp"

template <class T>
class Stack
{
private:
    LinkedList<T> _stack;

public:
    Stack() = default;

    void push(const T& e) { _stack.append(e); }
    T pop() { return _stack.remove_last(); }

    const T& top() const
    {
        if (empty()) throw std::out_of_range("Stack is empty");
        return _stack.back();
    }

    T& top()
    {
        if (empty()) throw std::out_of_range("Stack is empty");
        return _stack.back();
    }

    int size() const { return _stack.ll_size(); }
    bool empty() const { return _stack.empty(); }
};

#endif
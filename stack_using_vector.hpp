#ifndef __STACK_USING_VECTOR_HPP__
#define __STACK_USING_VECTOR_HPP__

#include <stdexcept>
#include "vector.hpp"

template <class T>
class Stack
{
private:
    Vector<T> _st;

public:
    Stack() = default;

    void push(const T& element)
    {
        _st.push_back(element);
    }

    T pop()
    {
        if (empty()) throw std::out_of_range("Stack is empty");
        T r = _st[_st.getsize() - 1];
        _st.pop_back();
        return r;
    }

    const T& top() const
    {
        if (empty()) throw std::out_of_range("Stack is empty");
        return _st[_st.getsize() - 1];
    }

    T& top()
    {
        if (empty()) throw std::out_of_range("Stack is empty");
        return _st[_st.getsize() - 1];
    }

    int size() const { return _st.getsize(); }
    bool empty() const { return _st.empty(); }
};

#endif
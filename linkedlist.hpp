#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <stdexcept>

template <class T>
class LinkedList
{
private:
    class Link
    {
    public:
        T _data;
        Link* _prev;
        Link* _next;
        Link(const T& data) : _data(data), _prev(nullptr), _next(nullptr) {}
        Link(const T& data, Link* prev, Link* next) : _data(data), _prev(prev), _next(next) {}
    };

    Link* _head;
    Link* _tail;
    int _length;

    void deleteAll()
    {
        while (_head)
        {
            Link* n = _head;
            _head = _head->_next;
            delete n;
        }
        _tail = nullptr;
        _length = 0;
    }

    void copyFrom(const LinkedList& other)
    {
        _head = _tail = nullptr;
        _length = 0;
        for (Link* curr = other._head; curr != nullptr; curr = curr->_next)
        {
            append(curr->_data);
        }
    }

public:
    LinkedList() : _head(nullptr), _tail(nullptr), _length(0) {}

    ~LinkedList()
    {
        deleteAll();
    }

    LinkedList(const LinkedList& other)
        : _head(nullptr), _tail(nullptr), _length(0)
    {
        copyFrom(other);
    }

    LinkedList& operator=(const LinkedList& other)
    {
        if (this != &other)
        {
            deleteAll();
            copyFrom(other);
        }
        return *this;
    }

    LinkedList(LinkedList&& other) noexcept
        : _head(other._head), _tail(other._tail), _length(other._length)
    {
        other._head = other._tail = nullptr;
        other._length = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept
    {
        if (this != &other)
        {
            deleteAll();
            _head = other._head;
            _tail = other._tail;
            _length = other._length;
            other._head = other._tail = nullptr;
            other._length = 0;
        }
        return *this;
    }

    int ll_size() const { return _length; }
    bool empty() const { return _length == 0; }

    void append(const T& data)
    {
        Link* n = new Link(data, _tail, nullptr);
        if (_length == 0)
            _head = _tail = n;
        else
        {
            _tail->_next = n;
            _tail = n;
        }
        _length++;
    }

    const T& front() const
    {
        if (empty()) throw std::out_of_range("List is empty");
        return _head->_data;
    }

    T& front()
    {
        if (empty()) throw std::out_of_range("List is empty");
        return _head->_data;
    }

    const T& back() const
    {
        if (empty()) throw std::out_of_range("List is empty");
        return _tail->_data;
    }

    T& back()
    {
        if (empty()) throw std::out_of_range("List is empty");
        return _tail->_data;
    }

    T remove_last()
    {
        if (empty()) throw std::out_of_range("List is empty");
        T ret = _tail->_data;
        Link* to_delete = _tail;
        if (_length == 1)
            _head = _tail = nullptr;
        else
        {
            _tail = _tail->_prev;
            _tail->_next = nullptr;
        }
        delete to_delete;
        _length--;
        return ret;
    }

    T remove_first()
    {
        if (empty()) throw std::out_of_range("List is empty");
        T ret = _head->_data;
        Link* to_delete = _head;
        if (_length == 1)
            _head = _tail = nullptr;
        else
        {
            _head = _head->_next;
            _head->_prev = nullptr;
        }
        delete to_delete;
        _length--;
        return ret;
    }

    const T& get(int index) const
    {
        if (index < 0 || index >= _length)
            throw std::out_of_range("Index out of range");
        Link* curr = _head;
        for (int i = 0; i < index; i++)
            curr = curr->_next;
        return curr->_data;
    }

    T& get(int index)
    {
        if (index < 0 || index >= _length)
            throw std::out_of_range("Index out of range");
        Link* curr = _head;
        for (int i = 0; i < index; i++)
            curr = curr->_next;
        return curr->_data;
    }

    void clear() { deleteAll(); }
};

#endif
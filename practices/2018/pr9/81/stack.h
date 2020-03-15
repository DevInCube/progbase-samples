#pragma once

template <typename T>
class Stack
{
    T items_[100];
    int size_ = 0;
public:
    void push(const T & value);
    T pop();
    T peek();
    bool isEmpty();
};

template <typename T>
bool Stack<T>::isEmpty()
{
    return size_ == 0;
}

template <typename T>
void Stack<T>::push(T const& value)
{
    if (size_ == 100) abort();
    items_[size_] = value;
    size_ += 1;
}

template <typename T>
T Stack<T>::peek()
{
    if (size_ == 0) abort();
    return items_[size_ - 1];
}

template <typename T>
T Stack<T>::pop()
{
    if (size_ == 0) abort();
    T val = items_[size_ - 1];
    size_ -= 1;
    return val;
}


#include "list.h"
#include <iostream>
#include <cassert>

static void InvalidIndexError()
{
    assert(0 && "Invalid index");
    std::cerr << "Invalid index" << std::endl;
}
//
void List::realloc( size_t newCapacity)
{ 
    float *newArray = static_cast<float *>(std::realloc(this->items_, sizeof(this->items_[0]) * newCapacity));
    if (newArray == NULL)
    {
        std::cerr << "Reallocation error" << std::endl;
        abort();
    }
    this->items_ = newArray;
    this->capacity_ = newCapacity;
    // printf("Reallocated\n");
}

List::List()
{
    this->capacity_ = 4;
    this->size_ = 0;
    this->items_ = static_cast<float*>(malloc(sizeof(this->items_[0]) * this->capacity_));
    if (this->items_ == NULL)
    {
        std::cerr << "Allocation error" << std::endl;
        abort();
    }
}

List::~List()
{
    free(this->items_);
}
//
size_t List::size()
{
    return this->size_;
}
//
float & List::operator[](int index)
{
    if (index < 0 || index > this->size())
    {
        InvalidIndexError();
        abort();
    }
    return this->items_[index];
}
//
void List::insert( int index, float value)
{
    if (index < 0 || index > this->size())
    {
        InvalidIndexError();
        return;
    }

    if (this->size_ == this->capacity_)
    {
        int newCapacity = this->capacity_ * 2;
        realloc(newCapacity);
    }

    for (int i = this->size_ - 1; i >= index; i--)
    {
        this->items_[i + 1] = this->items_[i];
    }
    this->items_[index] = value;
    this->size_ += 1;
}
//
void List::removeAt( int index)
{
    if (index < 0 || index > this->size())
    {
        InvalidIndexError();
        return;
    }

    for (int i = index; i < this->size(); i++)
    {
        this->items_[i] = this->items_[i + 1];
    }
    this->size_ -= 1;
}
//
void List::add( float value)
{
    if (this->size_ == this->capacity_)
    {
        int newCapacity = this->capacity_ * 2;
        realloc(newCapacity);
    }
    this->items_[this->size_] = value;
    this->size_ += 1;
}
//
void List::remove( float value)
{
    this->removeAt(this->indexOf(value));
}
//
int List::indexOf( float value)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (this->items_[i] == value)
        {
            return i;
        }
    }
    return -1;
}
//
bool List::contains( float value)
{
    for (int i = 0; i < this->size(); i++)
    {
        if (this->items_[i] == value)
        {
            return true;
        }
    }
    return false;
}
//
bool List::isEmpty()
{
    return this->size() == 0;
}
//
void List::clear()
{
    this->size_ = 0;
}
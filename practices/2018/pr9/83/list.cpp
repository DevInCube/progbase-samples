#include <cstdio>
#include "list.h"

List::List() 
{
    this->capacity = 4;
    this->size_ = 0;
    this->items = static_cast<float *>(malloc(sizeof(this->items[0]) * this->capacity));
    if (this->items == NULL)
    {
        fprintf(stderr, "Allocation error\n");
        abort();
    }
}

List::~List() 
{
    free(this->items);
}

size_t List::size()
{
    return this->size_;
}

//

static void List_InvalidIndexError()
{
    assert(0 && "Invalid index");
    fprintf(stderr, "Invalid index");
}
//
void List::realloc(size_t newCapacity)
{
    float *newArray = static_cast<float *>(std::realloc(this->items, sizeof(this->items[0]) * newCapacity));
    if (newArray == NULL)
    {
        fprintf(stderr, "Reallocation error\n");
        abort();
    }
    this->items = newArray;
    this->capacity = newCapacity;
    // printf("Reallocated\n");
}


//
float & List::operator [](int index)
{
    if (index < 0 || index > this->size_)
    {
        List_InvalidIndexError();
        abort();
    }
    float & item = this->items[index];
    return item;
}
//
void List::insert(int index, float value)
{
    if (index < 0 || index > size_)
    {
        List_InvalidIndexError();
        return;
    }

    if (this->size_ == this->capacity)
    {
        int newCapacity = this->capacity * 2;
        this->realloc(newCapacity);
    }

    for (int i = this->size_ - 1; i >= index; i--)
    {
        this->items[i + 1] = this->items[i];
    }
    this->items[index] = value;
    this->size_ += 1;
}
//
void List::removeAt(int index)
{
    if (index < 0 || index > size_)
    {
        List_InvalidIndexError();
        return;
    }

    for (int i = index; i < size_; i++)
    {
        this->items[i] = this->items[i + 1];
    }
    this->size_ -= 1;
}
//
void List::add(float value)
{
    if (this->size_ == this->capacity)
    {
        int newCapacity = this->capacity * 2;
        this->realloc(newCapacity);
    }
    this->items[this->size_] = value;
    this->size_ += 1;
}
//
void List::remove(float value)
{
    int index = this->indexOf(value);
    this->removeAt(index);
}
//
int List::indexOf(float value)
{
    for (int i = 0; i < size_; i++)
    {
        if (this->items[i] == value)
        {
            return i;
        }
    }
    return -1;
}
//
bool List::contains(float value)
{
    for (int i = 0; i < size_; i++)
    {
        if (this->items[i] == value)
        {
            return true;
        }
    }
    return false;
}
//
bool List::isEmpty()
{
    return this->size_ == 0;
}
//
void List::clear()
{
    this->size_ = 0;
}
//
#include "list.h"

List::List()
{
    this->capacity = 4;
    this->size_ = 0;
    this->items = static_cast<float*>(malloc(sizeof(this->items[0]) * this->capacity));
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

///

static void List_InvalidIndexError()
{
    assert(0 && "Invalid index");
    fprintf(stderr, "Invalid index");
}
//
void List::realloc(size_t newCapacity)
{
    float *newArray = static_cast<float *>(std::realloc(this->items, sizeof(this->items[0]) * newCapacity));
    if (newArray == nullptr)
    {
        fprintf(stderr, "Reallocation error\n");
        abort();
    }
    this->items = newArray;
    this->capacity = newCapacity;
    // printf("Reallocated\n");
}

size_t List::size()
{
    return this->size_;
}
//
float & List::operator [](int index)
{
    if (index < 0 || index > this->size_)
    {
        List_InvalidIndexError();
        abort();
    }
    float & f = this->items[index];
    return f;
}

void List::insert(int index, float value)
{
    if (index < 0 || index > size_)
    {
        List_InvalidIndexError();
        return;
    }

    if (size_ == capacity)
    {
        int newCapacity = capacity * 2;
        this->realloc(newCapacity);
    }

    for (int i = size_ - 1; i >= index; i--)
    {
        items[i + 1] = items[i];
    }
    items[index] = value;
    size_ += 1;
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
        items[i] = items[i + 1];
    }
    size_ -= 1;
}
//
void List::add(float value)
{
    if (size_ == capacity)
    {
        int newCapacity = capacity * 2;
        this->realloc(newCapacity);
    }
    items[size_] = value;
    size_ += 1;
}
//
void List::remove(float value)
{
    removeAt(indexOf(value));
}
//
int List::indexOf(float value)
{
    for (int i = 0; i < size_; i++)
    {
        if (items[i] == value)
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
        if (items[i] == value)
        {
            return true;
        }
    }
    return false;
}
//
bool List::isEmpty()
{
    return size() == 0;
}
//
void List::clear()
{
    this->size_ = 0;
}
//
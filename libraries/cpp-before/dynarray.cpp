#include "dynarray.h"

ruslan::DynArray::DynArray(size_t cap)
{
    this->items_ = new T[cap];
    this->capacity_ = cap;
}

ruslan::DynArray::~DynArray()
{
    delete[] this->items_;
}

size_t ruslan::DynArray::size()
{
    return this->capacity_;
}

ruslan::T &ruslan::DynArray::operator[](int index)
{
    return this->items_[index];
}
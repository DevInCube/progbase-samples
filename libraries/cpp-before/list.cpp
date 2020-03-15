#include "list.h"

ruslan::List::List() : array_{16}, size_{} {}

size_t ruslan::List::size() { return this->size_; }

ruslan::T &ruslan::List::operator[](int index) { return this->array_[index]; }

void ruslan::List::push_back(T value)
{
    this->array_[this->size_++] = value;
}
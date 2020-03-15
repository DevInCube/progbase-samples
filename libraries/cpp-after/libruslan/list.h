#pragma once

#include "dynarray.h"

namespace ruslan
{

class List
{
    DynArray array_;
    size_t size_;

public:
    List();

    size_t size();

    T &operator[](int index);

    void push_back(T value);
};

} // namespace ruslan
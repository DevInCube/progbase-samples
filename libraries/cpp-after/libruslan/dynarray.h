#pragma once
#include <cstdlib>

namespace ruslan
{

using T = int;

class DynArray
{
    T *items_;
    size_t capacity_;

public:
    explicit DynArray(size_t cap);
    ~DynArray();

    size_t size();

    T &operator[](int index);
};

} // namespace ruslan
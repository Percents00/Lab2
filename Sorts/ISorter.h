#pragma once

#include "../Sequence.h"
#include "../SharedPtr.h"

template <typename T, typename Comparator>
class ISorter {
public:
    virtual void Sort(SharedPtr<Sequence<T>> sequence, Comparator comp) = 0;
    virtual ~ISorter() = default;
};

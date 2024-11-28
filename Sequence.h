#pragma once
#include "UniquePtr.h"
#include "SharedPtr.h"

template <typename T>
class Sequence {
public:
    virtual ~Sequence() = default;

    virtual SharedPtr<Sequence<T>> Append(const T& item) const = 0;
    virtual SharedPtr<Sequence<T>> Prepend(const T& item) const = 0;
    virtual SharedPtr<Sequence<T>> InsertAt(int index, const T& item) const = 0;
    virtual SharedPtr<Sequence<T>> GetSubsequence(int startIndex, int endIndex) const = 0;
    
    virtual void Set(int index, const T& value) = 0;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual const T& Get(int index) const = 0;
    virtual T& Get(int index) = 0;


    virtual int GetLength() const noexcept = 0;
    virtual SharedPtr<Sequence<T>> Copy() const = 0;


};
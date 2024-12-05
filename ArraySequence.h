#pragma once

#include "Sequence.h"
#include "DynamicArray.h"
#include <algorithm>

template <typename T>
class ArraySequence : public Sequence<T> {
private:
  SharedPtr<DynamicArray<T>> array_;

public:
  ArraySequence() : array_(new DynamicArray<T>(0)) {}
  ArraySequence(const SharedPtr<DynamicArray<T>>& arr) : array_(arr) {}
    ArraySequence(const T* items, int count) : array_(new DynamicArray<T>(items, count)) {}
  ArraySequence(const ArraySequence<T>& other) : array_(new DynamicArray<T>(*other.array_)) {}


  SharedPtr<Sequence<T>> Append(const T& item) const override {
      int oldSize = array_->GetSize();
      SharedPtr<DynamicArray<T>> newArray(new DynamicArray<T>(oldSize + 1));
      for (int i = 0; i < oldSize; i++) {
        newArray->Set(i, array_->Get(i));
      }
      newArray->Set(oldSize, item);
      return SharedPtr<Sequence<T>>(new ArraySequence<T>(newArray));
  }

  SharedPtr<Sequence<T>> Prepend(const T& item) const override {
      int oldSize = array_->GetSize();
      SharedPtr<DynamicArray<T>> newArray(new DynamicArray<T>(oldSize + 1));
      newArray->Set(0, item);
      for (int i = 0; i < oldSize; ++i) {
          newArray->Set(i + 1, array_->Get(i));
      }
      return SharedPtr<Sequence<T>>(new ArraySequence<T>(newArray));
  }

  SharedPtr<Sequence<T>> InsertAt(int index, const T& item) const override {
      int oldSize = array_->GetSize();
      if (index < 0 || index > oldSize) {
          throw std::out_of_range("Index out of range");
      }
      SharedPtr<DynamicArray<T>> newArray(new DynamicArray<T>(oldSize + 1));
      for (int i = 0; i < index; ++i) {
          newArray->Set(i, array_->Get(i));
      }
      newArray->Set(index, item);
      for (int i = index; i < oldSize; ++i) {
          newArray->Set(i + 1, array_->Get(i));
      }
      return SharedPtr<Sequence<T>>(new ArraySequence<T>(newArray));
  }

  SharedPtr<Sequence<T>> GetSubsequence(int startIndex, int endIndex) const override {
      if (startIndex < 0 || endIndex >= array_->GetSize() || startIndex > endIndex) {
          throw std::out_of_range("Index out of range");
      }
      int newSize = endIndex - startIndex + 1;
      SharedPtr<DynamicArray<T>> newArray(new DynamicArray<T>(newSize));
      for (int i = 0; i < newSize; ++i) {
          newArray->Set(i, array_->Get(startIndex + i));
      }
      return SharedPtr<Sequence<T>>(new ArraySequence<T>(newArray));
  }


  T GetFirst() const override {
    if (array_->GetSize() == 0) {
      throw std::out_of_range("Sequence is empty");
    }
    return array_->Get(0);
  }

  T GetLast() const override {
    if (array_->GetSize() == 0) {
      throw std::out_of_range("Sequence is empty");
    }
    return array_->Get(array_->GetSize() - 1);
  }

  const T& Get(int index) const override {
    if (index < 0 || index >= array_->GetSize()) {
      throw std::out_of_range("Index out of range");
    }
    return array_->Get(index);
  }

  T& Get(int index) override {
    if (index < 0 || index >= array_->GetSize()) {
        throw std::out_of_range("Index out of range");
    }
    return array_->Get(index);
  }


  void Set(int index, const T& value) override {
    if (index < 0 || index >= array_->GetSize()) {
      throw std::out_of_range("Index out of range");
    }
    array_->Set(index, value);
  }

  int GetLength() const noexcept override { return array_->GetSize(); }

  SharedPtr<Sequence<T>> Copy() const override {
      return SharedPtr<Sequence<T>>(new ArraySequence<T>(*this));
  }

};
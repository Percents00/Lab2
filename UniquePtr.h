#pragma once

#include <stdexcept>
#include <utility>

template <typename T>
class UniquePtr {
private:
  T* ptr_ = nullptr;

public:
  UniquePtr() = default;

  explicit UniquePtr(T* p) : ptr_(p) {}

  UniquePtr(UniquePtr&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {}

  ~UniquePtr() { delete ptr_; }

  UniquePtr& operator=(UniquePtr&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = std::exchange(other.ptr_, nullptr);
    }
    return *this;
  }

  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;

  T& operator*() const {
    if (!ptr_) {
      throw std::runtime_error("Dereferencing null UniquePtr");
    }
    return *ptr_;
  }

  T* operator->() const {
    if (!ptr_) {
      throw std::runtime_error("Dereferencing null UniquePtr");
    }
    return ptr_;
  }

  T* Get() const noexcept { return ptr_; }

  void swap(UniquePtr& other) noexcept { std::swap(ptr_, other.ptr_); }

  explicit operator bool() const noexcept { return ptr_ != nullptr; }

  bool operator==(std::nullptr_t) const noexcept { return ptr_ == nullptr; }
  bool operator!=(std::nullptr_t) const noexcept { return ptr_ != nullptr; }

};
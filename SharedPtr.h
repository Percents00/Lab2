#pragma once

#include <cstddef>
#include <stdexcept>

template <typename T>
class SharedPtr {
private:
  struct ControlBlock {
    std::size_t ref_count = 1;

    ~ControlBlock() = default;

  };

  T* ptr_ = nullptr;
  ControlBlock* control_block_ = nullptr;

public:
  SharedPtr() = default;

  explicit SharedPtr(T* p) : ptr_(p), control_block_(p ? new ControlBlock() : nullptr) {}


  SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), control_block_(other.control_block_) {
    if (control_block_) {
      ++control_block_->ref_count;
    }
  }

  SharedPtr(SharedPtr&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)), control_block_(std::exchange(other.control_block_, nullptr)) {}

  SharedPtr& operator=(const SharedPtr& other) {
      if (this != &other) {
          if (control_block_) {
              --control_block_->ref_count;
              if (control_block_->ref_count == 0) {
                  delete ptr_;
                  delete control_block_;
              }
          }
          ptr_ = other.ptr_;
          control_block_ = other.control_block_;
          if (control_block_) {
              ++control_block_->ref_count;
          }
      }
      return *this;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    if (this != &other) {
      this->reset();
      ptr_ = std::exchange(other.ptr_, nullptr);
      control_block_ = std::exchange(other.control_block_, nullptr);
    }
    return *this;
  }

  ~SharedPtr() { this->reset(); }

  T& operator*() const {
    if (!ptr_) {
      throw std::runtime_error("Dereferencing null SharedPtr");
    }
    return *ptr_;
  }

  T* operator->() const {
    if (!ptr_) {
      throw std::runtime_error("Dereferencing null SharedPtr");
    }
    return ptr_;
  }


  T* Get() const noexcept { return ptr_; }

  std::size_t getRefCount() const noexcept { return control_block_ ? control_block_->ref_count : 0; }

  void reset() noexcept {
    if (control_block_ && --control_block_->ref_count == 0) {
      delete ptr_;
      delete control_block_;
    }
    ptr_ = nullptr;
    control_block_ = nullptr;
  }

  void reset(T* newPtr) {
    this->reset();
    ptr_ = newPtr;
    control_block_ = newPtr ? new ControlBlock() : nullptr;
  }


  explicit operator bool() const noexcept { return ptr_ != nullptr; }

  bool operator==(std::nullptr_t) const noexcept { return ptr_ == nullptr; }
  bool operator!=(std::nullptr_t) const noexcept { return ptr_ != nullptr; }

};
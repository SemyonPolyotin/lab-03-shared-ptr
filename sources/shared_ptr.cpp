// Copyright 2020 Your Name <your_email>

#include <shared_ptr.hpp>

template <typename T>
SharedPtr<T>::SharedPtr() {
  pointer = nullptr;
  counter = nullptr;
}

template <typename T>
SharedPtr<T>::SharedPtr(T* ptr) {
  pointer = ptr;
  counter = new std::atomic_uint{1};
}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& r) {
  pointer = r.pointer;
  counter = r.counter;
  ++(*counter);
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& r) {
  pointer = r.pointer;
  counter = r.counter;
  r.pointer = nullptr;
  r.counter = nullptr;
}

template <typename T>
SharedPtr<T>::~SharedPtr() {
  if (!counter) {
    return;
  }
  if (--(*counter) == 0) {
    delete pointer;
    delete counter;
  }
  pointer = nullptr;
  counter = nullptr;
}

template <typename T>
auto SharedPtr<T>::operator=(const SharedPtr& r) -> SharedPtr& {
  if (this == &r) {
    return *this;
  }
  this->~SharedPtr();
  pointer = r.pointer;
  counter = r.counter;
  ++(*counter);
  return *this;
}

template <typename T>
auto SharedPtr<T>::operator=(SharedPtr&& r) -> SharedPtr& {
  if (this == &r) {
    return *this;
  }
  this->~SharedPtr();
  pointer = r.pointer;
  counter = r.counter;
  r.pointer = nullptr;
  r.counter = nullptr;
  return *this;
}

template <typename T>
SharedPtr<T>::operator bool() const {
  return pointer != nullptr;
}

template <typename T>
auto SharedPtr<T>::operator*() const -> T& {
  return *pointer;
}

template <typename T>
auto SharedPtr<T>::operator->() const -> T* {
  return pointer;
}

template <typename T>
auto SharedPtr<T>::get() -> T* {
  return pointer;
}

template <typename T>
void SharedPtr<T>::reset() {
  *this = SharedPtr();
}

template <typename T>
void SharedPtr<T>::reset(T* ptr) {
  *this = SharedPtr(ptr);
}

template <typename T>
void SharedPtr<T>::swap(SharedPtr& r) {
  if (this == &r) {
    return;
  }
  std::swap(pointer, r.pointer);
  std::swap(counter, r.counter);
}

template <typename T>
auto SharedPtr<T>::use_count() const -> size_t {
  return static_cast<size_t>(*counter);
}

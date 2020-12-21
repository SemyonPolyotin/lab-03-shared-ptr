// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <cstddef>
template <typename T>
class SharedPtr {
 public:
  SharedPtr();
  SharedPtr(T* ptr);
  SharedPtr(const SharedPtr& r);
  SharedPtr(SharedPtr&& r);
  ~SharedPtr();
  auto operator=(const SharedPtr& r) -> SharedPtr&;
  auto operator=(SharedPtr&& r) -> SharedPtr&;

  // проверяет, указывает ли указатель на объект
  operator bool() const;
  auto operator*() const -> T&;
  auto operator->() const -> T*;

  auto get() -> T*;
  void reset();
  void reset(T* ptr);
  void swap(SharedPtr& r);
  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  auto use_count() const -> size_t;

 private:
  T* pointer;
  std::atomic_uint* counter;
};

#endif  // INCLUDE_HEADER_HPP_

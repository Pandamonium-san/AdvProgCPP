#pragma once
#include <vector>

template<class T>
class SharedPtr
{
  T* m_ptr;
  int* m_count;

  bool Invariant() { return (m_ptr == nullptr && m_count == nullptr) || (m_ptr != nullptr && m_count != nullptr); }
public:
  SharedPtr() {
    m_ptr = nullptr;
    m_count = nullptr;
  }
  SharedPtr(std::nullptr_t nullp) {
    m_ptr = nullptr;
    m_count = nullptr;
  }
  SharedPtr(T* ptr) {
    m_ptr = ptr;
    if (ptr == nullptr)
      m_count = nullptr;
    else
      m_count = new int(1);
    assert(Invariant());
  }
  SharedPtr(const SharedPtr& other) {
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    ++(*m_count);
    assert(Invariant());
  }
  SharedPtr(SharedPtr&& other) {
    m_ptr = other.m_ptr;
    m_count = other.m_count;
    other.m_count = nullptr;
    other.m_ptr = nullptr;
    assert(Invariant());
  }
  ~SharedPtr() {
    assert(Invariant());
    if (m_count != nullptr && --(*m_count) == 0) {
      delete m_count;
      delete m_ptr;
    }
  }
  SharedPtr& operator=(const SharedPtr& rhs) {
    if (m_count != nullptr && --(*m_count) == 0) {
      delete m_count;
      delete m_ptr;
    }
    m_ptr = rhs.m_ptr;
    m_count = rhs.m_count;
    ++(*m_count);
    assert(Invariant());
    return *this;
  }
  SharedPtr& operator=(SharedPtr&& rhs) {
    if (m_count != nullptr && --(*m_count) == 0) {
      delete m_count;
      delete m_ptr;
    }
    m_ptr = rhs.m_ptr;
    m_count = rhs.m_count;
    rhs.m_ptr = nullptr;
    rhs.m_count = nullptr;
    assert(Invariant());
    return *this;
  }

  void reset(T* ptr = nullptr) {
    if (m_ptr != nullptr && --(*m_count) == 0) {
      delete m_count;
      delete m_ptr;
    }
    m_ptr = ptr;
    if (ptr == nullptr)
      m_count = nullptr;
    else
      m_count = new int(1);
    assert(Invariant());
  }
  bool unique() { return *m_count == 1; }
  T* get() { return m_ptr; }
  T* operator->() { return m_ptr; }
  T& operator*() { return *m_ptr; }

  operator bool() { return m_ptr != nullptr; }
  friend bool operator==(const SharedPtr& lhs, const SharedPtr& rhs) { return lhs.m_ptr == rhs.m_ptr; }
  friend bool operator<(const SharedPtr& lhs, const SharedPtr& rhs) { return lhs.m_ptr < rhs.m_ptr; }
};


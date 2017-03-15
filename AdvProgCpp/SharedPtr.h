#pragma once
#include <vector>
#include <cassert>
#include <utility>

class RCounter;

template<class T>
class SharedPtr
{
  T* m_ptr;
  RCounter* m_counter;

  template<class T>
  friend class WeakPtr;
  template<class T>
  friend class SharedPtr;
  bool Invariant() { return (m_ptr == nullptr && m_counter == nullptr) || (m_ptr != nullptr && m_counter != nullptr && m_counter->Invariant()); }
public:
  SharedPtr();
  SharedPtr(std::nullptr_t nullp);
  SharedPtr(T* ptr);
  
  SharedPtr(const SharedPtr& other);
  SharedPtr(SharedPtr&& other);

  template<class U>
  SharedPtr(const SharedPtr<U>& other);
  template<class U>
  SharedPtr(SharedPtr<U>&& other);
  template<class U>
  SharedPtr(WeakPtr<U>& other);
  ~SharedPtr();

  SharedPtr& operator=(const SharedPtr& rhs);
  SharedPtr& operator=(SharedPtr&& rhs);
  void swap(SharedPtr& other);
  void reset(T* ptr = nullptr);

  bool unique() { return m_counter->UseCount() == 1; }
  T* get() { return m_ptr; }
  T* operator->() { return m_ptr; }
  T& operator*() { return *m_ptr; }
  bool operator==(const SharedPtr& rhs) { return m_ptr == rhs.m_ptr; }
  bool operator<(const SharedPtr& rhs) { return m_ptr < rhs.m_ptr; }
  explicit operator bool() { return m_ptr != nullptr; }
};

template<class T>
class WeakPtr
{
  T* m_ptr;
  RCounter* m_counter;

  bool Invariant() { return (m_counter == nullptr && m_ptr == nullptr) || m_counter != nullptr; }
  friend class SharedPtr<T>;
public:
  WeakPtr();
  WeakPtr(const WeakPtr& ptr);
  ~WeakPtr();
  template<class U>
  WeakPtr(const WeakPtr<U>& ptr);
  template<class U>
  WeakPtr(const SharedPtr<U>& ptr);

  template<class U>
  WeakPtr& operator=(const SharedPtr<U>& ptr);
  WeakPtr& operator=(const WeakPtr& ptr);
  bool expired();
  SharedPtr<T> lock();
};

class RCounter
{
  long m_count;
  long m_refs;

public:
  RCounter()
  {
    m_count = 1;
    m_refs = 1;
  }
  ~RCounter() {}
  long Add()
  {
    assert(Invariant());
    ++m_refs;
    return ++m_count;
  }
  long Release()
  {
    assert(Invariant());
    int temp = --m_count;
    ReleaseWeak();
    return temp;
  }
  long AddWeak()
  {
    assert(Invariant());
    return ++m_refs;
  }
  long ReleaseWeak()
  {
    assert(Invariant());
    long temp = --m_refs;
    if (temp == 0)
      delete this;
    return temp;
  }
  long UseCount()
  {
    return m_count;
  }
  bool Invariant() { return m_count <= m_refs && m_count >= 0; }
};
#pragma once
#include <vector>
#include <utility>

class RCounter
{
  int m_count;
  int m_refs;
public:
  RCounter()
  {
    m_count = 1;
    m_refs = 1;
  }
  ~RCounter() {}
  int Add()
  {
    ++m_refs;
    return ++m_count;
  }
  int Release()
  {
    int temp = --m_count;
    ReleaseWeak();
    return temp;
  }
  int AddWeak()
  {
    return ++m_refs;
  }
  int ReleaseWeak()
  {
    int temp = --m_refs;
    if (temp == 0)
      delete this;
    return temp;
  }
  int UseCount()
  {
    return m_count;
  }
};

template<class T>
class SharedPtr
{
  T* m_ptr;
  RCounter* m_counter;

  template<class T>
  friend class WeakPtr;
public:
  SharedPtr();
  SharedPtr(std::nullptr_t nullp);
  SharedPtr(T* ptr);
  SharedPtr(const SharedPtr& other);
  SharedPtr(SharedPtr&& other);
  template<class U>
  SharedPtr(const WeakPtr<U>& other);
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

  friend class SharedPtr<T>;
public:
  WeakPtr();
  template<class U>
  WeakPtr(const SharedPtr<U>& ptr);
  template<class U>
  WeakPtr(const WeakPtr<U>& ptr);
  ~WeakPtr();

  template<class U>
  WeakPtr& operator=(const SharedPtr<U>& ptr);
  WeakPtr& operator=(const WeakPtr& ptr);
  bool expired() const;
  SharedPtr<T> lock() const;
};
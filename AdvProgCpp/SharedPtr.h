#pragma once
#include <vector>
#include <utility>

class RCounter
{
  unsigned int m_count;
  unsigned int m_self;
public:
  RCounter()
  {
    m_count = 1;
    m_self = 1;
  }
  ~RCounter() {}
  unsigned int Add()
  {
    ++m_self;
    return ++m_count;
  }
  unsigned int Release()
  {
    unsigned int temp = --m_count;
    ReleaseWeak();
    return temp;
  }
  unsigned int AddWeak()
  {
    return ++m_self;
  }
  unsigned int ReleaseWeak()
  {
    unsigned int temp = --m_self;
    if (temp == 0)
      delete this;
    return temp;
  }
  unsigned int UseCount()
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

  operator bool() { return m_ptr != nullptr; }
  friend bool operator==(const SharedPtr& lhs, const SharedPtr& rhs) { return lhs.m_ptr == rhs.m_ptr; }
  friend bool operator<(const SharedPtr& lhs, const SharedPtr& rhs) { return lhs.m_ptr < rhs.m_ptr; }
};

template<class T>
class WeakPtr
{
  T* m_ptr;
  RCounter* m_counter;

  friend class SharedPtr<T>;
public:
  WeakPtr()
  {
    m_ptr = nullptr;
    m_counter = nullptr;
  }
  template<class U>
  WeakPtr(const SharedPtr<U>& ptr)
  {
    m_ptr = ptr.m_ptr;
    m_counter = ptr.m_counter;
    if (m_counter != nullptr)
      m_counter->AddWeak();
  }
  template<class U>
  WeakPtr(const WeakPtr<U>& ptr)
  {
    m_ptr = ptr.m_ptr;
    m_counter = ptr.m_counter;
    if (m_counter != nullptr)
      m_counter->AddWeak();
  }
  template<class U>
  WeakPtr& operator=(const SharedPtr<U>& ptr)
  {
    if (m_counter != nullptr)
      m_counter->ReleaseWeak();
    m_ptr = ptr.m_ptr;
    m_counter = ptr.m_counter;
    if (m_counter != nullptr)
      m_counter->AddWeak();
    return *this;
  }
  WeakPtr& operator=(const WeakPtr& ptr)
  {
    if (m_counter != nullptr)
      m_counter->ReleaseWeak();
    m_ptr = ptr.m_ptr;
    m_counter = ptr.m_counter;
    if (m_counter != nullptr)
      m_counter->AddWeak();
    return *this;
  }
  ~WeakPtr()
  {
    if (m_counter != nullptr)
      m_counter->ReleaseWeak();
  }
  bool expired() const
  {
    if (m_counter == nullptr)
      return true;
    if (m_counter->UseCount() == 0) {
      return true;
    }
    return false;
  }
  SharedPtr<T> lock() const
  {
    if (expired()) {
      return SharedPtr<T>();
    }
    else {
      return SharedPtr<T>(*this);
    }
  }
};
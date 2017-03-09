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
    return --m_count;
  }
  unsigned int AddWeak()
  {
    return ++m_self;
  }
  unsigned int ReleaseWeak()
  {
    return --m_self;
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
  bool Invariant() { return true; }// (m_ptr == nullptr && m_counter == nullptr) || (m_ptr != nullptr && m_counter != nullptr); }
public:
  SharedPtr()
  {
    m_ptr = nullptr;
    m_counter = nullptr;
  }
  SharedPtr(std::nullptr_t nullp)
  {
    m_ptr = nullptr;
    m_counter = nullptr;
  }
  SharedPtr(T* ptr)
  {
    m_ptr = ptr;
    if (ptr == nullptr)
      m_counter = nullptr;
    else
      m_counter = new RCounter();
    assert(Invariant());
  }
  SharedPtr(const SharedPtr& other)
  {
    m_ptr = other.m_ptr;
    m_counter = other.m_counter;
    m_counter->Add();
    assert(Invariant());
  }
  SharedPtr(SharedPtr&& other)
  {
    m_ptr = nullptr;
    m_counter = nullptr;
    swap(other);
    assert(Invariant());
  }
  template<class T>
  SharedPtr(const WeakPtr<T>& other)
  {
    m_ptr = other.m_ptr;
    assert(Invariant());
  }
  ~SharedPtr()
  {
    assert(Invariant());
    if (m_counter != nullptr && m_counter->Release() == 0) {
      delete m_ptr;
      if (m_counter->ReleaseWeak() == 0)
        delete m_counter;
    }
  }

  SharedPtr& operator=(const SharedPtr& rhs)
  {
    SharedPtr(rhs).swap(*this);
    assert(Invariant());
    return *this;
  }
  SharedPtr& operator=(SharedPtr&& rhs)
  {
    SharedPtr(std::move(rhs)).swap(*this);
    assert(Invariant());
    return *this;
  }

  void swap(SharedPtr& other)
  {
    T* temp = m_ptr;
    RCounter* temp2 = m_counter;
    m_ptr = other.m_ptr;
    m_counter = other.m_counter;
    other.m_ptr = temp;
    other.m_counter = temp2;
  }
  void reset(T* ptr = nullptr)
  {
    SharedPtr(ptr).swap(*this);
    assert(Invariant());
  }

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

public:
  WeakPtr()
  {
    m_ptr = nullptr;
    m_counter = nullptr;
  }
  template<class T>
  WeakPtr(const SharedPtr<T>& ptr)
  {
    m_ptr = ptr.m_ptr;
    m_counter = ptr.m_counter;
    m_counter->AddWeak();
  }
  WeakPtr(const WeakPtr& ptr)
  {
    m_ptr = ptr.m_ptr;
    m_counter = ptr.m_counter;
    m_counter->AddWeak();
  }
  template<class T>
  WeakPtr& operator=(const SharedPtr<T>& ptr)
  {
    if (m_counter != nullptr)
      m_counter->ReleaseWeak();
    m_ptr = ptr.m_ptr;
    m_counter = ptr.m_counter;
    m_counter->AddWeak();
    return *this;
  }
  WeakPtr& operator=(const WeakPtr& ptr)
  {
    if (m_counter != nullptr)
      m_counter->ReleaseWeak();
    m_ptr = ptr.m_ptr;
    m_counter = ptr.m_counter;
    m_counter->AddWeak();
    return *this;
  }

  SharedPtr<T> lock() const
  {

  }

  bool expired()
  {
    return m_counter->UseCount() == 0;
  }
};
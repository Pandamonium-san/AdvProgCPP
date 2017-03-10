#pragma once
#include "stdafx.h"
#include "SharedPtr.h"

template<class T>
SharedPtr<T>::SharedPtr()
{
  m_ptr = nullptr;
  m_counter = nullptr;
}
template<class T>
SharedPtr<T>::SharedPtr(std::nullptr_t nullp)
{
  m_ptr = nullptr;
  m_counter = nullptr;
}
template<class T>
SharedPtr<T>::SharedPtr(T* ptr)
{
  m_ptr = ptr;
  if (ptr == nullptr)
    m_counter = nullptr;
  else
    m_counter = new RCounter();
}
template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr& other)
{
  m_ptr = other.m_ptr;
  m_counter = other.m_counter;
  if (m_counter != nullptr)
    m_counter->Add();
}
template<class T>
SharedPtr<T>::SharedPtr(SharedPtr&& other)
{
  m_ptr = nullptr;
  m_counter = nullptr;
  swap(other);
}
template<class T>
template<class U>
SharedPtr<T>::SharedPtr(const WeakPtr<U>& other)
{
  if (other.expired())
    throw "std::bad_weak_ptr";
  m_ptr = other.m_ptr;
  m_counter = other.m_counter;
  if (m_counter != nullptr)
    m_counter->Add();
}
template<class T>
SharedPtr<T>::~SharedPtr()
{
  if (m_counter != nullptr) {
    if (m_counter->Release() == 0)
      delete m_ptr;
  }
}
template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& rhs)
{
  SharedPtr<T>(rhs).swap(*this);
  return *this;
}
template<class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& rhs)
{
  SharedPtr<T>(std::move(rhs)).swap(*this);
  return *this;
}
template<class T>
void SharedPtr<T>::swap(SharedPtr<T>& other)
{
  T* temp = m_ptr;
  RCounter* temp2 = m_counter;
  m_ptr = other.m_ptr;
  m_counter = other.m_counter;
  other.m_ptr = temp;
  other.m_counter = temp2;
}
template<class T>
void SharedPtr<T>::reset(T* ptr = nullptr)
{
  SharedPtr<T>(ptr).swap(*this);
}


template<class T>
WeakPtr<T>::WeakPtr()
{
  m_ptr = nullptr;
  m_counter = nullptr;
}
template<class T>
template<class U>
WeakPtr<T>::WeakPtr(const SharedPtr<U>& ptr)
{
  m_ptr = ptr.m_ptr;
  m_counter = ptr.m_counter;
  if (m_counter != nullptr)
    m_counter->AddWeak();
}
template<class T>
template<class U>
WeakPtr<T>::WeakPtr(const WeakPtr<U>& ptr)
{
  m_ptr = ptr.m_ptr;
  m_counter = ptr.m_counter;
  if (m_counter != nullptr)
    m_counter->AddWeak();
}
template<class T>
WeakPtr<T>::~WeakPtr()
{
  if (m_counter != nullptr)
    m_counter->ReleaseWeak();
}
template<class T>
template<class U>
WeakPtr<T>& WeakPtr<T>::operator=(const SharedPtr<U>& ptr)
{
  if (m_counter != nullptr)
    m_counter->ReleaseWeak();
  m_ptr = ptr.m_ptr;
  m_counter = ptr.m_counter;
  if (m_counter != nullptr)
    m_counter->AddWeak();
  return *this;
}
template<class T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr& ptr)
{
  if (m_counter != nullptr)
    m_counter->ReleaseWeak();
  m_ptr = ptr.m_ptr;
  m_counter = ptr.m_counter;
  if (m_counter != nullptr)
    m_counter->AddWeak();
  return *this;
}
template<class T>
bool WeakPtr<T>::expired() const
{
  if (m_counter == nullptr)
    return true;
  if (m_counter->UseCount() == 0) {
    return true;
  }
  return false;
}
template<class T>
SharedPtr<T> WeakPtr<T>::lock() const
{
  if (expired()) {
    return SharedPtr<T>();
  }
  else {
    return SharedPtr<T>(*this);
  }
}

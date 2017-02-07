#pragma once
#include "stdafx.h"
#include "Link.h"

template <class T>
Link<T>::Link()
{
  next = nullptr;
  prev = nullptr;
}

template<class T>
T * Link<T>::Next()
{
  return dynamic_cast<T*>(next);
}

template<class T>
const T * Link<T>::Next() const
{
  return dynamic_cast<T*>(next);
}

template<class T>
T * Link<T>::Prev()
{
  return dynamic_cast<T*>(prev);
}

template<class T>
const T * Link<T>::Prev() const
{
  return dynamic_cast<T*>(prev);
}

template<class T>
T* Link<T>::InsertAfter(T * TToInsert)
{
  next->prev = TToInsert;
  TToInsert->next = next;
  TToInsert->prev = this;
  next = TToInsert;
  return TToInsert;
}

template<class T>
T* Link<T>::InsertBefore(T * TToInsert)
{
  prev->next = TToInsert;
  TToInsert->prev = prev;
  TToInsert->next = this;
  prev = TToInsert;
  return TToInsert;
}

template<class T>
T* Link<T>::DeleteAfter()
{
  T* deleted = Next();
  if (deleted == nullptr)
    return nullptr;
  next = next->next;
  next->prev = this;
  return deleted;
}

template<class T>
T * Link<T>::DeleteBefore()
{
  T* deleted = Prev();
  if (deleted == nullptr)
    return nullptr;
  prev = prev->prev;
  prev->next = this;
  return deleted;
}

template<class T>
template<class X>
T * Link<T>::Find(const X& searchFor) const
{
  for (const T* it = Next(); it != nullptr; it = it->Next())
  {
    if (*it == searchFor)
      return const_cast<T*>(it);
  }
  return nullptr;
}

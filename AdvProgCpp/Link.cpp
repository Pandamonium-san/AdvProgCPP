#pragma once
#include "stdafx.h"
#include "Link.h"

template <class ValueType>
Link<ValueType>::Link()
{
  next = nullptr;
  prev = nullptr;
}

template<class ValueType>
ValueType * Link<ValueType>::Next()
{
  return dynamic_cast<ValueType*>(next);
}

template<class ValueType>
const ValueType * Link<ValueType>::Next() const
{
  return dynamic_cast<ValueType*>(next);
}

template<class ValueType>
ValueType * Link<ValueType>::Prev()
{
  return dynamic_cast<ValueType*>(prev);
}

template<class ValueType>
const ValueType * Link<ValueType>::Prev() const
{
  return dynamic_cast<ValueType*>(prev);
}

template<class ValueType>
ValueType* Link<ValueType>::InsertAfter(ValueType * TToInsert)
{
  next->prev = TToInsert;
  TToInsert->next = next;
  TToInsert->prev = this;
  next = TToInsert;
  return TToInsert;
}

template<class ValueType>
ValueType* Link<ValueType>::InsertBefore(ValueType * TToInsert)
{
  prev->next = TToInsert;
  TToInsert->prev = prev;
  TToInsert->next = this;
  prev = TToInsert;
  return TToInsert;
}

template<class ValueType>
ValueType* Link<ValueType>::DeleteAfter()
{
  ValueType* deleted = Next();
  if (deleted == nullptr)
    return nullptr;
  next = next->next;
  next->prev = this;
  return deleted;
}

template<class ValueType>
ValueType * Link<ValueType>::DeleteBefore()
{
  ValueType* deleted = Prev();
  if (deleted == nullptr)
    return nullptr;
  prev = prev->prev;
  prev->next = this;
  return deleted;
}

template<class ValueType>
template<class X>
ValueType * Link<ValueType>::Find(const X & searchFor)
{
  for (ValueType* it = Next(); it != nullptr; it = it->Next())
  {
    if (*it == searchFor)
      return it;
  }
  return nullptr;
}

template<class ValueType>
template<class X>
const ValueType * Link<ValueType>::Find(const X& searchFor) const
{
  for (const ValueType* it = Next(); it != nullptr; it = it->Next())
  {
    if (*it == searchFor)
      return it;
  }
  return nullptr;
}

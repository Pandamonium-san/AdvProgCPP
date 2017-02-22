#pragma once
#include "stdafx.h"
#include "List.h"
#include "Link.cpp"

template<class ValueType>
List<ValueType>::List()
{
  next = this;
  prev = this;
}

template<class ValueType>
List<ValueType>::~List()
{
  ValueType* next2;
  for (ValueType* it = Next(); it != nullptr;)
  {
    next2 = it->Next();
    delete it;
    it = next2;
  }
}

template<class ValueType>
ValueType * List<ValueType>::First() 
{
  return dynamic_cast<ValueType*>(next);
}

template<class ValueType>
const ValueType * List<ValueType>::First() const
{
  return dynamic_cast<ValueType*>(next);
}

template<class ValueType>
ValueType * List<ValueType>::Last() 
{
  return dynamic_cast<ValueType*>(prev);
}

template<class ValueType>
const ValueType * List<ValueType>::Last() const
{
  return dynamic_cast<ValueType*>(prev);
}

template<class ValueType>
ValueType* List<ValueType>::InsertFirst(ValueType* item)
{
  return InsertAfter(item);
}

template<class ValueType>
ValueType* List<ValueType>::PopFirst()
{
  return DeleteAfter();
}

template<class ValueType>
ValueType* List<ValueType>::InsertLast(ValueType* item)
{
  return InsertBefore(item);
}

template<class ValueType>
void List<ValueType>::Check() const {
  const Link<ValueType> *node = this, *nextNode = next;
  do {
    assert(node->next == nextNode && nextNode->prev == node);
    node = nextNode;
    nextNode = nextNode->next;
  } while (node != this);
}

template<class ValueType>
std::ostream & List<ValueType>::Print(std::ostream & cout) const
{
  for (const Link<ValueType>* item = First(); item; item = item->Next())
  {
    item->Print(cout) << ' ';
  }
  cout << '\n';
  return cout;
}



#pragma once
#include "stdafx.h"
#include "List.h"
#include "Link.cpp"

template<class T>
List<T>::List()
{
  next = this;
  prev = this;
}

template<class T>
List<T>::~List()
{
  T* next2;
  for (T* it = Next(); it != nullptr;)
  {
    next2 = it->Next();
    delete it;
    it = next2;
  }
}

template<class T>
T * List<T>::First() 
{
  return dynamic_cast<T*>(next);
}

template<class T>
const T * List<T>::First() const
{
  return dynamic_cast<T*>(next);
}

template<class T>
T * List<T>::Last() 
{
  return dynamic_cast<T*>(prev);
}

template<class T>
const T * List<T>::Last() const
{
  return dynamic_cast<T*>(prev);
}

template<class T>
T* List<T>::InsertFirst(T* item)
{
  return InsertAfter(item);
}

template<class T>
T* List<T>::PopFirst()
{
  return DeleteAfter();
}

template<class T>
T* List<T>::InsertLast(T* item)
{
  return InsertBefore(item);
}

template<class T>
void List<T>::Check() const {
  const Link<T> *node = this, *nextNode = next;
  do {
    assert(node->next == nextNode && nextNode->prev == node);
    node = nextNode;
    nextNode = nextNode->next;
  } while (node != this);
}

template<class T>
std::ostream & List<T>::Print(std::ostream & cout) const
{
  for (const Link<T>* item = First(); item; item = item->Next())
  {
    item->Print(cout) << ' ';
  }
  cout << '\n';
  return cout;
}



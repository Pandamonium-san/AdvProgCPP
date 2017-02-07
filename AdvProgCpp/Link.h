#pragma once
#include <assert.h>
#include <iostream>
template <class T>
class List;

template <class T>
class Link {
  Link* next; Link* prev;
  friend class List<T>;
public:
  Link();
  virtual ~Link() = default;
  T* Next();
  const T* Next() const;
  T* Prev();
  const T* Prev() const;
  T* InsertAfter(T * TToInsert);
  T* InsertBefore(T * TToInsert);
  T* DeleteAfter();
  T* DeleteBefore();
  template <class X>
  T* Find(const X& searchFor) const;
  virtual std::ostream& Print(std::ostream& cout) const { return cout; }
};

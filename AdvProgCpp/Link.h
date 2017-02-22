#pragma once
#include <iostream>
template <class ValueType>
class List;

template <class ValueType>
class Link {
  Link* next; Link* prev;
  friend class List<ValueType>;
public:
  Link();
  virtual ~Link() = default;
  ValueType* Next();
  const ValueType* Next() const;
  ValueType* Prev();
  const ValueType* Prev() const;
  ValueType* InsertAfter(ValueType * TToInsert);
  ValueType* InsertBefore(ValueType * TToInsert);
  ValueType* DeleteAfter();
  ValueType* DeleteBefore();
  template <class X>
  ValueType* Find(const X& searchFor);
  template <class X>
  const ValueType* Find(const X& searchFor) const;
  virtual std::ostream& Print(std::ostream& cout) const { return cout; }
};

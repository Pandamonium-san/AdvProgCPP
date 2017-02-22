#pragma once
#include "Link.h"

template <class ValueType>
class List : public Link<ValueType>{
  friend class Link<ValueType>;
public:
  List();
  ~List();
  ValueType * First() ;
  const ValueType * First() const;
  ValueType * Last() ;
  const ValueType * Last() const;
  ValueType * InsertFirst(ValueType* item);
  ValueType * PopFirst();
  ValueType * InsertLast(ValueType* item);

  friend std::ostream& operator<<(std::ostream& cout, List<ValueType>& list) {
    return list.Print(cout);
  }
  void Check() const;
private:
  std::ostream& Print(std::ostream& cout) const;
};



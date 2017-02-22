#pragma once
#include "Link.h"

template<class ValueType>
class Node : public Link<Node<ValueType>>
{
public:
  ValueType data;
  Node(ValueType item);

  virtual std::ostream& Print(std::ostream& cout) const {
    return cout << data;
  }

  bool operator == (ValueType searchFor) const {
    return data == searchFor;
  }
};

#pragma once
#include "Link.h"

template<class T>
class Node : public Link<Node<T>>
{
public:
  T data;
  Node(T item);

  virtual std::ostream& Print(std::ostream& cout) const {
    return cout << data;
  }

  bool operator == (T searchFor) const {
    return data == searchFor;
  }
};

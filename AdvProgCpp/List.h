#pragma once
#include "Link.h"

template <class T>
class List : public Link<T>{
  friend class Link<T>;
public:
  List();
  ~List();
  T * First() ;
  const T * First() const;
  T * Last() ;
  const T * Last() const;
  T * InsertFirst(T* item);
  T * PopFirst();
  T * InsertLast(T* item);

  friend std::ostream& operator<<(std::ostream& cout, List<T>& list) {
    return list.Print(cout);
  }
  void Check() const;
  static void TestDLL();
private:
  std::ostream& Print(std::ostream& cout) const;
};



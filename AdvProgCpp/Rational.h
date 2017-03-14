#pragma once
#include <iostream>
#include "GCD.h"

template<class T_int>
class Rational
{
public:
  T_int P, Q;
  friend std::ostream& operator<< (std::ostream & cout, Rational<T_int> R) {
    cout << R.P << '/' << R.Q;
    return cout;
  }
  Rational() : P(0), Q(1) {};
  template<class U>
  Rational(U p) :P(p), Q(1) {};
  template<class U, class V>
  Rational(U p, V q) :P(p), Q(q) {
    Reduce(P, Q);
  }
  template<class R>
  Rational(const Rational<R>& other) : P(other.P), Q(other.Q) {};

  template<class R>
  bool operator==(const Rational<R>& other) { return P == other.P && Q == other.Q; }
  template<class R>
  bool operator<(const Rational<R>& other) { return P*other.Q < other.P*Q; }

  template<class R>
  bool operator==(const R& other) { return P / Q == other && P % Q == 0; }
  template<class R>
  bool operator<(const R& other) { return P / Q < other; }

  template <class R> bool operator!=(const R& rhs) { return !(*this == rhs); }
  template <class R> bool operator>(const R& rhs) { return (rhs < *this); }
  template <class R> bool operator>=(const R& rhs) { return !(*this < rhs); }
  template <class R> bool operator<=(const R& rhs) { return !(rhs < *this); }

  Rational operator+(const Rational rhs) const {
    return Rational(P*rhs.Q + rhs.P*Q, Q*rhs.Q);
  }
};


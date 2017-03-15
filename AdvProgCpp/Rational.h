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

  bool operator==(const Rational& other) { return P == other.P && Q == other.Q; }
  bool operator<(const Rational& other) { return P*other.Q < other.P*Q; }

  //template<class R>
  //bool operator==(const Rational<R>& other) { return P == other.P && Q == other.Q; }
  //template<class R>
  //bool operator<(const Rational<R>& other) { return P*other.Q < other.P*Q; }

  //template<class R>
  //bool operator==(const R& other) { return P / Q == other && P % Q == 0; }
  //template<class R>
  //bool operator<(const R& other) { return P / Q < other; }

  template <class R> bool operator!=(const R& rhs) { return !(*this == rhs); }
  template <class R> bool operator>(const R& rhs) { return (rhs < *this); }
  template <class R> bool operator>=(const R& rhs) { return !(*this < rhs); }
  template <class R> bool operator<=(const R& rhs) { return !(rhs < *this); }

  template<class R>
  Rational operator+(const R& other) const { return Rational(P * other + other * Q, Q * other); }
  template<class R>
  Rational operator+(const Rational<R>& other) const { return Rational(P * other.Q + other.P * Q, Q * other.Q); }
//  Rational& operator+=(const Rational& other) { this = this + other; return *this; }
  //template<class R>
  //Rational& operator+=(const Rational<R>& other) { this = this + other; return *this; }
  //template<class R>
  //Rational& operator+=(const R& other) { this = this + other; return *this; }
};


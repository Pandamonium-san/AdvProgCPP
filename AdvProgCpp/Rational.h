#pragma once
#include <iostream>
#include "GCD.h"

template <typename T, typename R> bool operator!=(const T& lhs, const R& rhs) { return !(lhs == rhs); }
template <typename T, typename R> bool operator>(const T& lhs, const R& rhs) { return (rhs < lhs); }
template <typename T, typename R> bool operator>=(const T& lhs, const R& rhs) { return !(lhs < rhs); }
template <typename T, typename R> bool operator<=(const T& lhs, const R& rhs) { return !(rhs < lhs); }

template<typename T_int, class = typename std::enable_if<std::is_integral<T_int>::value>::type>
class Rational
{
public:
  T_int P, Q;

  Rational() : P(0), Q(1) {};
  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  Rational(T p) : P(p), Q(1) {}
  template <typename T, typename U, class = typename std::enable_if<std::is_integral<T>::value && std::is_integral<U>::value>::type>
  Rational(T p, U q) {
    long long lp = p, lq = q;
    Reduce(lp, lq);
    P = lp;
    Q = lq;
    if (Q < 0) {
      Q *= -1;
      P *= -1;
    }
  }
  template<typename R>
  Rational(const Rational<R>& other) : P(other.P), Q(other.Q) {};

  template<class T>
  friend typename std::enable_if<(sizeof(T_int) >= sizeof(T) && std::is_integral<T>::value), Rational<T_int>>::type
    operator+(const Rational<T_int>& lhs, const Rational<T>& rhs)
  {
    return Rational<T_int>(lhs.P*rhs.Q + rhs.P*lhs.Q, lhs.Q*rhs.Q);
  }
  template<class T>
  friend typename std::enable_if<(sizeof(T_int) < sizeof(T) && std::is_integral<T>::value), Rational<T>>::type
    operator+(const Rational<T_int>& lhs, const Rational<T>& rhs)
  {
    return Rational<T>(lhs.P*rhs.Q + rhs.P*lhs.Q, lhs.Q*rhs.Q);
  }

  template<class T>
  friend typename std::enable_if<(sizeof(T_int) >= sizeof(T) && std::is_integral<T>::value), Rational<T_int>>::type
    operator+(const T_int& lhs, const Rational<T>& rhs)
  {
    return Rational<T_int>(lhs*rhs.Q + rhs.P, rhs.Q);
  }
  template<class T>
  friend typename std::enable_if<(sizeof(T_int) < sizeof(T) && std::is_integral<T>::value), Rational<T>>::type
    operator+(const T_int& lhs, const Rational<T>& rhs)
  {
    return Rational<T>(lhs*rhs.Q + rhs.P, rhs.Q);
  }

  template<class T>
  friend typename std::enable_if<(sizeof(T_int) >= sizeof(T) && std::is_integral<T>::value), Rational<T_int>>::type
    operator+(const Rational<T_int>& lhs, const T& rhs)
  {
    return Rational<T_int>(lhs.P + rhs*lhs.Q, lhs.Q);
  }
  template<class T>
  friend typename std::enable_if<(sizeof(T_int) < sizeof(T) && std::is_integral<T>::value), Rational<T>>::type
    operator+(const Rational<T_int>& lhs, const T& rhs)
  {
    return Rational<T>(lhs.P + rhs*lhs.Q, lhs.Q);
  }

  template<typename R>
  Rational& operator+=(const Rational<R>& other) { *this = *this + other; return *this; }
  Rational& operator+=(const T_int& other) { *this = *this + other; return *this; }
  Rational& operator++() { return *this += 1; }
  Rational operator++(int) { auto temp(*this); *this += 1; return temp; }
  Rational operator-() const { return Rational(-P, Q); }

  template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  explicit operator T() const { return (T)(P / Q); }

  bool operator==(const Rational& other) const { return P == other.P && Q == other.Q; }
  bool operator<(const Rational& other) const { return P*other.Q < other.P*Q; }

  template <typename R>
  friend bool operator==(const T_int& lhs, const Rational<R>& rhs) { return lhs*rhs.Q == rhs.P; }
  template <typename R>
  friend bool operator<(const T_int& lhs, const Rational<R>& rhs) { return lhs*rhs.Q < rhs.P; }

  friend std::ostream& operator<< (std::ostream & cout, Rational R) {
    cout << R.P << '/' << R.Q;
    return cout;
  }
  friend std::istream& operator >> (std::istream & cin, Rational& R) {
    cin >> R.P;
    cin.ignore(1);
    cin >> R.Q;
    return cin;
  }
  bool Invariant() {
    return Q > 0;
  }
};


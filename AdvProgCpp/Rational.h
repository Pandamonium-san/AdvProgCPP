#pragma once
#include <iostream>
#include "GCD.h"

template <typename T, typename R> bool operator!=(const T& lhs, const R& rhs) { return !(lhs == rhs); }
template <typename T, typename R> bool operator>(const T& lhs, const R& rhs) { return (rhs < lhs); }
template <typename T, typename R> bool operator>=(const T& lhs, const R& rhs) { return !(lhs < rhs); }
template <typename T, typename R> bool operator<=(const T& lhs, const R& rhs) { return !(rhs < lhs); }

template<class T> struct next_size { typedef T type; };
template<> struct next_size<short> { typedef int type; };
template<> struct next_size<int> { typedef long long type; };

template<typename T_int, class = typename std::enable_if<std::is_integral<T_int>::value>::type>
class Rational
{
public:
  T_int P, Q;

  Rational() : P(0), Q(1) {};
  Rational(T_int p) : P(p), Q(1) {}
  Rational(T_int p, T_int q) {
    Reduce(p, q);
    P = p;
    Q = q;
    if (Q < 0) {
      Q *= -1;
      P *= -1;
    }
  }
  template<typename R>
  Rational(const Rational<R>& other) : P(other.P), Q(other.Q) {};
  ~Rational() { assert(Invariant()); }

  template<class T>
  friend typename std::enable_if<(sizeof(T_int) >= sizeof(T) && std::is_integral<T>::value), Rational<T_int>>::type
    operator+(const Rational<T_int>& lhs, const Rational<T>& rhs)
  {
    return Rational<T_int>(lhs) += rhs;
  }
  template<class T>
  friend typename std::enable_if<(sizeof(T_int) < sizeof(T) && std::is_integral<T>::value), Rational<T>>::type
    operator+(const Rational<T_int>& lhs, const Rational<T>& rhs)
  {
    return Rational<T>(lhs) += rhs;
  }
  template<class T>
  friend typename std::enable_if<(sizeof(T_int) >= sizeof(T) && std::is_integral<T>::value), Rational<T_int>>::type
    operator+(const T& lhs, const Rational<T_int>& rhs)
  {
    return Rational<T_int>(lhs) += rhs;
  }
  template<class T>
  friend typename std::enable_if<(sizeof(T_int) < sizeof(T) && std::is_integral<T>::value), Rational<T>>::type
    operator+(const T& lhs, const Rational<T_int>& rhs)
  {
    return Rational<T>(lhs) += rhs;
  }
  template<class T>
  friend typename std::enable_if<(sizeof(T_int) >= sizeof(T) && std::is_integral<T>::value), Rational<T_int>>::type
    operator+(const Rational<T_int>& lhs, const T& rhs)
  {
    return Rational<T_int>(lhs) += rhs;
  }
  template<class T>
  friend typename std::enable_if<(sizeof(T_int) < sizeof(T) && std::is_integral<T>::value), Rational<T>>::type
    operator+(const Rational<T_int>& lhs, const T& rhs)
  {
    return Rational<T>(lhs) += rhs;
  }

  template<typename T>
  Rational& operator+=(const Rational<T>& rhs) {
    next_size<T_int>::type p = P, q = Q;
    p = p * rhs.Q + rhs.P*q;
    q = q * rhs.Q;
    Reduce(p, q);
    P = p;
    Q = q;
    return *this;
  }
  template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  Rational& operator+=(const T& rhs) {
    next_size<T_int>::type p = P, q;
    p = p + rhs*Q;
    q = Q;
    Reduce(p, q);
    P = p;
    Q = q;
    return *this;
  }

  Rational& operator++() { return *this += 1; }
  Rational operator++(int) { auto temp(*this); *this += 1; return temp; }
  Rational operator-() const { return Rational(-P, Q); }

  template<typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  explicit operator T() const { return (T)P / (T)Q; }

  bool operator==(const Rational& other) const { return P == other.P && Q == other.Q; }
  bool operator<(const Rational& other) const { return P*other.Q < other.P*Q; }

  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  friend bool operator==(const Rational& lhs, const T& rhs) { return rhs*lhs.Q == lhs.P; }
  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  friend bool operator==(const T& lhs, const Rational& rhs) { return lhs*rhs.Q == rhs.P; }

  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  friend bool operator<(const Rational& lhs, const T& rhs) { return rhs*lhs.Q < lhs.P; }
  template <typename T, class = typename std::enable_if<std::is_integral<T>::value>::type>
  friend bool operator<(const T& lhs, const Rational& rhs) { return lhs*rhs.Q < rhs.P; }

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
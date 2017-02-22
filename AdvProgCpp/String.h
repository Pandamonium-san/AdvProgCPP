#pragma once
#include <iostream>
#include "StringItr.h"


class String
{
  int m_capacity;
  char* m_begin;
  char* m_end;

  inline void Copy(const char* from, int len, bool remove);
  bool Invariant() const;
public:
  typedef strItr<char> iterator;
  typedef strItr<const char> const_iterator;

  String();
  ~String();
  String(const String& rhs);
  String(String&& rhs); //VG
  String(const char* cstr);
  String(const char c);

  String& operator=(const String& rhs);
  String& operator=(String&& rhs); //VG
  String& operator+=(const String& rhs);
  explicit operator bool();

  char& at(size_t i);
  const char& at(size_t i) const;
  char& operator[](size_t i);
  const char& operator[](size_t i) const;
  const char* data() const;
  int size() const;
  void reserve(size_t n);
  void resize(size_t n);
  int capacity() const;
  void shrink_to_fit();
  void push_back(char c);

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  friend bool operator==(const String& lhs, const String& rhs);
  friend bool operator!=(const String& lhs, const String& rhs);
  friend String operator+(const String& lhs, const String& rhs);
  friend std::ostream& operator<<(std::ostream& cout, const String& str);
};


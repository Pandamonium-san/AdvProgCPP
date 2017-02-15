#pragma once
#include <iostream>
extern int g_ops;
class String
{
  int m_capacity;
  char* m_begin = nullptr;
  char* m_end = nullptr;

  inline void Copy(const char* from);
  inline void Copy(const String& from);
public:
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

  friend bool operator==(const String& lhs, const String& rhs);
  friend bool operator!=(const String& lhs, const String& rhs);
  friend String operator+(const String& lhs, const String& rhs);
  friend std::ostream& operator<<(std::ostream& cout, const String& str);
};


#pragma once
#include <iostream>

class String
{
  char* m_cstr = nullptr;

  inline void CopyCstring(const char* from);
  inline void CopyCstring(char* to, const char* from);
public:
  String();
  ~String();
  String(const String& rhs);
  String(const String&& rhs); //VG
  String(const char* cstr);

  String& operator=(const String& rhs);
  String& operator=(const String&& rhs); //VG
  String& operator=(const char* cstr);
  String& operator=(const char ch);
  String& operator+=(const String& rhs);
  String& operator+=(const char* cstr);
  String operator+(const String& rhs) const;
  String operator+(const char* cstr) const;

  char& at(size_t i) const;
  char& operator[](size_t i) const;
  const char* data() const;
  int size() const;
  void reserve(size_t n);
  void resize(size_t n);
  friend bool operator==(const String& lhs, const String& rhs);
  friend bool operator==(const String& lhs, const char* rhs);
  friend std::ostream& operator<<(std::ostream& cout, const String& str);
};


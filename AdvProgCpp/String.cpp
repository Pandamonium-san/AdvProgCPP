#include "stdafx.h"
#include "String.h"

int g_ops;

String::String()
{
}


String::~String()
{
  delete m_begin;
}

String::String(const String & rhs)
{
  Copy(rhs.m_begin);
}

String::String(String && rhs)
{
  this->m_begin = rhs.m_begin;
  this->m_end = rhs.m_end;
  this->m_capacity = rhs.m_capacity;
  rhs.m_begin = nullptr;
  rhs.m_end = nullptr;
}

String::String(const char * cstr)
{
  Copy(cstr);
}

String & String::operator=(const String & rhs)
{
  Copy(rhs.m_begin);
  return *this;
}

String & String::operator=(String && rhs)
{
  delete m_begin;
  m_begin = rhs.m_begin;
  m_end = rhs.m_end;
  m_capacity = rhs.m_capacity;
  rhs.m_begin = nullptr;
  return *this;
}

String & String::operator=(const char * cstr)
{
  Copy(cstr);
  return *this;
}

String & String::operator=(const char ch)
{
  char* temp = new char[2]; // can throw
  delete m_begin;
  this->m_capacity = 2;
  m_begin = temp;
  m_begin[0] = ch;
  m_begin[1] = '\0';
  m_end = &m_begin[1];
  return *this;
}

String & String::operator+=(const String & rhs)
{
  *this = *this + rhs;
  return *this;
}

String & String::operator+=(const char * cstr)
{
  *this = *this + cstr;
  return *this;
}

String String::operator+(const String & rhs) const
{
  int len = size();
  int length = len + rhs.size();
  String result;
  result.reserve(length);
  char * rItr = result.m_begin;
  for (const char* itr = m_begin; itr != m_end; itr++)
    *rItr++ = *itr;
  for (const char* itr = rhs.m_begin; itr != rhs.m_end; itr++)
    *rItr++ = *itr;
  result[length] = '\0';
  result.m_end = &result[length];
  return result;
}

String String::operator+(const char * cstr) const
{
  int len = size();
  int length = len + strlen(cstr);
  String result;
  result.reserve(length);
  char * rItr = result.m_begin;
  for (const char* itr = m_begin; itr != m_end; itr++)
    *rItr++ = *itr;
  for (const char* itr = cstr; *itr != '\0'; itr++)
    *rItr++ = *itr;
  result.m_end = &result[length];
  return result;
}

char & String::at(size_t i)
{
  return const_cast<char&>(const_cast<const String*>(this)->at(i));
}

const char & String::at(size_t i) const
{
  if (i > size() - 1 || i < 0)
    throw std::out_of_range("String.at()");
  else
    return m_begin[i];
}

char & String::operator[](size_t i)
{
  return m_begin[i];
}

const char & String::operator[](size_t i) const
{
  return m_begin[i];
}

const char * String::data() const
{
  return m_begin;
}

int String::size() const
{
  return strlen(m_begin);
}

void String::reserve(size_t n)
{
  if (m_begin != nullptr && size() >= n)
  {
    shrink_to_fit();
    return;
  }
  resize(n);
}

int String::capacity() const
{
  return m_capacity;
}

void String::shrink_to_fit()
{
  if (size() == m_capacity)
    return;
  resize(size());
}
void String::push_back(char c)
{
  int len = size();
  if (len == m_capacity)
  {
    reserve(1 + len * 2);
    g_ops += len;
  }
  m_begin[len] = c;
  m_begin[len + 1] = '\0';
  m_end++;
}

void String::resize(size_t n)
{
  char* temp = new char[n + 1]; // can throw
  if (m_begin != nullptr)
  {
    for (int i = 0; i < n || &m_begin[i] == m_end; i++)
      temp[i] = m_begin[i];
    delete m_begin;
  }
  m_begin = temp;
  m_end = &temp[n];
  *m_end = '\0';
  m_capacity = n;
}

bool operator==(const String & lhs, const String & rhs)
{
  return lhs == rhs.m_begin;
}

bool operator==(const String & lhs, const char * rhs)
{
  const char *itrL = lhs.m_begin;
  const char *itrR = rhs;
  while (itrL != lhs.m_end && *itrR != '\0')
  {
    if (*itrL++ != *itrR++)
      return false;
  }
  return true;
}

std::ostream & operator<<(std::ostream & cout, const String & str)
{
  cout << str.m_begin;
  return cout;
}

void String::Copy(const char * from)
{
  int cap = strlen(from) + 1;
  char* temp = new char[cap]; // can throw
  delete m_begin;
  this->m_capacity = cap;
  m_begin = temp;
  int i = 0;
  for (const char* itr = from; *itr != '\0'; itr++)
  {
    m_begin[i++] = *itr;
  }
  m_begin[i] = '\0';
  m_end = &m_begin[i];
}

//void String::Copy(const String& from)
//{
//  delete m_begin;
//  int cap = from.size() + 1;
//  this->m_capacity = cap;
//  m_begin = new char[cap];
//  int i = 0;
//  for (const char* itr = from.m_begin; itr != from.m_end; itr++)
//  {
//    m_begin[i++] = *itr;
//  }
//  m_begin[i] = '\0';
//  m_end = &m_begin[i];
//}


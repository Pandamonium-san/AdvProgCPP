#include "stdafx.h"
#include "String.h"

int g_ops;

String::String()
{
  m_begin = new char[4];
  m_end = m_begin;
  *m_end = '\0';
  m_capacity = 3;
}


String::~String()
{
  delete m_begin;
}

String::String(const String & rhs)
{
  Copy(rhs);
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

String::String(const char ch)
{
  char* temp = new char[2]; // can throw
  delete m_begin;
  this->m_capacity = 2;
  m_begin = temp;
  m_begin[0] = ch;
  m_begin[1] = '\0';
  m_end = &m_begin[1];
}

String & String::operator=(const String & rhs)
{
  Copy(rhs);
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

String & String::operator+=(const String & rhs)
{
  *this = *this + rhs;
  return *this;
}

String::operator bool()
{
  return size() > 0;
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
  int size = 0;
  for (const char* itr = m_begin; itr != m_end; itr++)
    ++size;
  return size;
}

void String::reserve(size_t n)
{
  if (m_begin != nullptr && size() >= n)
  {
    shrink_to_fit();
    return;
  }

  char* temp = (char*)malloc(sizeof(char)*n + 1);
  temp[n] = '\0';
  m_capacity = n;

  int i = 0;
  const char* itr = m_begin;
  while (i < n && itr != m_end)
  {
    temp[i++] = *itr++;
  }
  delete m_begin;
  m_end = &temp[i];
  *m_end = '\0';
  m_begin = temp;
}

void String::resize(size_t n)
{
  char* temp = new char[n + 1]; // can throw
  temp[n] = '\0';
  m_capacity = n;

  int i = 0;
  const char* itr = m_begin;
  while (i < n && itr != m_end)
  {
     temp[i++] = *itr++;
  }
  delete m_begin;
  m_end = &temp[n];
  m_begin = temp;
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

bool operator==(const String & lhs, const String & rhs)
{
  const char *itrL = lhs.m_begin;
  const char *itrR = rhs.m_begin;
  while (itrL != lhs.m_end && itrR != rhs.m_end)
  {
    if (*itrL++ != *itrR++)
      return false;
  }
  if (*itrL++ != *itrR++)
    return false;
  return true;
}

bool operator!=(const String & lhs, const String & rhs)
{
  return !(lhs == rhs);
}

String operator+(const String & lhs, const String & rhs)
{
  int len = lhs.size();
  int length = len + rhs.size();
  String result;
  result.reserve(length);
  char * rItr = result.m_begin;
  for (const char* itr = lhs.m_begin; itr != lhs.m_end; itr++)
    *rItr++ = *itr;
  for (const char* itr = rhs.m_begin; itr != rhs.m_end; itr++)
    *rItr++ = *itr;
  result[length] = '\0';
  result.m_end = &result[length];
  return result;
}

std::ostream & operator<<(std::ostream & cout, const String & str)
{
  for (const char* itr = str.m_begin; itr != str.m_end; itr++)
  {
    cout << *itr;
  }
  return cout;
}

void String::Copy(const char * from)
{
  int cap = strlen(from) + 1;
  if (m_capacity < cap)
  {
    char* temp = new char[cap]; // can throw
    delete m_begin;
    m_begin = temp;
    this->m_capacity = cap - 1;
  }
  int i = 0;
  for (const char* itr = from; *itr != '\0'; itr++)
  {
    m_begin[i++] = *itr;
  }
  m_begin[i] = '\0';
  m_end = &m_begin[i];
}

void String::Copy(const String& from)
{
  if (m_capacity < from.m_capacity)
  {
    char* temp = new char[from.m_capacity + 1]; // can throw
    delete m_begin;
    m_begin = temp;
    this->m_capacity = from.m_capacity;
  }
  int i = 0;
  for (const char* itr = from.m_begin; itr != from.m_end; itr++)
  {
    m_begin[i++] = *itr;
  }
  m_begin[i] = '\0';
  m_end = &m_begin[i];
}

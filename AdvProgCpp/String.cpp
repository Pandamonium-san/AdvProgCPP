#include "stdafx.h"
#include "String.h"

String::String()
{
}


String::~String()
{
  delete m_cstr;
}

String::String(const String & rhs)
{
  CopyCstring(rhs.m_cstr);
}

String::String(const String && rhs)
{
  CopyCstring(rhs.m_cstr);
}

String::String(const char * cstr)
{
  CopyCstring(cstr);
}

String & String::operator=(const String & rhs)
{
  CopyCstring(rhs.m_cstr);
  return *this;
}

String & String::operator=(const String && rhs)
{
  CopyCstring(rhs.m_cstr);
  return *this;
}

String & String::operator=(const char * cstr)
{
  CopyCstring(cstr);
  return *this;
}

String & String::operator=(const char ch)
{
  delete m_cstr;
  m_cstr = new char(ch);
  return *this;
}

String & String::operator+=(const String & rhs)
{
  *this = *this + rhs.m_cstr;
  return *this;
}

String & String::operator+=(const char * cstr)
{
  *this = *this + cstr;
  return *this;
}

String String::operator+(const String & rhs) const
{
  return String(*this + rhs.m_cstr);
}

String String::operator+(const char * cstr) const
{
  int size = this->size();
  int length = size + strlen(cstr);
  String result;
  result.reserve(length);
  //result.m_cstr = new char[length + 1];
  for (int i = 0; i < size; i++)
  {
    result[i] = m_cstr[i];
  }
  for (int i = size; i < size + strlen(cstr); i++)
  {
    result[i] = cstr[i - size];
  }
  result[length] = '\0';
  return String(result);
}

char & String::at(size_t i) const
{
  if (i > size() || i < 0)
    throw std::out_of_range("String.at()");
  else
    return m_cstr[i];
}

char & String::operator[](size_t i) const
{
  return m_cstr[i];
}

const char * String::data() const
{
  return m_cstr;
}

int String::size() const
{
  return strlen(m_cstr);
}

void String::reserve(size_t n)
{
  if (m_cstr != nullptr && strlen(m_cstr) >= n)
    return;
  resize(n);
}

void String::resize(size_t n)
{
  if (m_cstr == nullptr)
  {
    m_cstr = new char[n + 1];
    m_cstr[n] = '\0';
    return;
  }
  char* temp = new char[n + 1];   // [h][e][y][\0] resize(2)
  for (int i = 0; i < n; i++)
  {
    if (m_cstr[i] == '\0')
      break;
    temp[i] = m_cstr[i];
  }
  temp[n] = '\0';
  delete m_cstr;
  m_cstr = temp;
}

bool operator==(const String & lhs, const String & rhs)
{
  return *lhs.m_cstr == *rhs.m_cstr;
}

bool operator==(const String & lhs, const char * rhs)
{
  return *lhs.m_cstr == *rhs;
}

std::ostream & operator<<(std::ostream & cout, const String & str)
{
  cout << str.m_cstr;
  return cout;
}

void String::CopyCstring(const char * from)
{
  delete m_cstr;
  m_cstr = new char[strlen(from) + 1];
  int i = 0;
  for (const char* itr = from; *itr != '\0'; itr++)
  {
    m_cstr[i++] = *itr;
  }
  m_cstr[i] = '\0';
}

void String::CopyCstring(char * to, const char * from)
{
  delete to;
  to = new char[strlen(from) + 1];
  int i = 0;
  for (const char* itr = from; *itr != '\0'; itr++)
  {
    to[i++] = *itr;
  }
  to[i] = '\0';
}
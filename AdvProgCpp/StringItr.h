#pragma once
#include <iterator>
template<typename ValueType, bool r = false>
class strItr : public std::iterator<
  std::bidirectional_iterator_tag,
  ValueType,
  int,
  ValueType*,
  ValueType&>
{
  ValueType* m_ptr;
public:
  strItr(ValueType* ptr = nullptr) { this->m_ptr = ptr; }
  strItr(const strItr& other) { this->m_ptr = other.m_ptr; }
  ~strItr() {}

  bool operator==(const strItr& rhs) const { return m_ptr == rhs.m_ptr; }
  bool operator!=(const strItr& rhs) const { return m_ptr != rhs.m_ptr; }
  bool operator<(const strItr& rhs) const { return m_ptr < rhs.m_ptr; }

  strItr& operator=(const strItr& rhs) = default;
  strItr& operator+=(int i) { m_ptr += i; return *this; }
  strItr& operator-=(int i) { m_ptr -= i; return *this; }
  strItr& operator++() { ++m_ptr; return *this; }
  strItr& operator--() { --m_ptr; return *this; }
  strItr operator++(int) { auto temp(m_ptr++); return temp; }
  strItr operator--(int) { auto temp(m_ptr--); return temp; }
  strItr operator+(int i) const {
    auto temp(m_ptr + i);
    return temp;
  }
  strItr operator-(int i) const {
    auto temp(m_ptr - i);
    return temp;
  }

  ValueType& operator*() { return *m_ptr; }
  ValueType& operator[](int i) { return *(m_ptr + i); }
  const ValueType& operator*() const { return *m_ptr; }
  const ValueType& operator[](int i) const { return *(m_ptr + i); }

  operator strItr<ValueType const>() const { this = const_cast<strItr<ValueType const>(*this); }
};


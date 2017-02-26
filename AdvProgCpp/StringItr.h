#pragma once
#include <iterator>

template<typename ValueType>
class strItr : public std::iterator<
  std::bidirectional_iterator_tag,
  ValueType,
  ptrdiff_t,
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
  //bool operator<(const strItr& rhs) const { return m_ptr < rhs.m_ptr; }

  strItr& operator=(const strItr& rhs) = default;
  strItr& operator+=(ptrdiff_t i) { m_ptr += i; return *this; }
  strItr& operator-=(ptrdiff_t i) { m_ptr -= i; return *this; }
  strItr& operator++() { ++m_ptr; return *this; }
  strItr& operator--() { --m_ptr; return *this; }
  strItr operator++(ptrdiff_t) { auto temp(m_ptr++); return temp; }
  strItr operator--(ptrdiff_t) { auto temp(m_ptr--); return temp; }
  strItr operator+(ptrdiff_t i) const {
    auto temp(m_ptr + i);
    return temp;
  }
  strItr operator-(ptrdiff_t i) const {
    auto temp(m_ptr - i);
    return temp;
  }
  ptrdiff_t operator-(const strItr& rhs) { return this->m_ptr - rhs.m_ptr; }

  ValueType& operator*() { return *m_ptr; }
  ValueType& operator[](ptrdiff_t i) { return *(m_ptr + i); }
  const ValueType& operator*() const { return *m_ptr; }
  const ValueType& operator[](ptrdiff_t i) const { return *(m_ptr + i); }

  //operator strItr<ValueType const>() const { this = const_cast<strItr<ValueType const>(*this); }
};

template<typename ValueType>
class r_strItr : public std::iterator<
  std::bidirectional_iterator_tag,
  ValueType,
  ptrdiff_t,
  ValueType*,
  ValueType&>
{
  ValueType* m_ptr;
public:
  r_strItr(ValueType* ptr = nullptr) { this->m_ptr = ptr; }
  r_strItr(const r_strItr& other) { this->m_ptr = other.m_ptr; }
  ~r_strItr() {}

  bool operator==(const r_strItr& rhs) const { return m_ptr == rhs.m_ptr; }
  bool operator!=(const r_strItr& rhs) const { return m_ptr != rhs.m_ptr; }
  //bool operator<(const r_strItr& rhs) const { return m_ptr < rhs.m_ptr; }

  r_strItr& operator=(const r_strItr& rhs) = default;
  r_strItr& operator+=(ptrdiff_t i) { m_ptr -= i; return *this; }
  r_strItr& operator-=(ptrdiff_t i) { m_ptr += i; return *this; }
  r_strItr& operator++() { --m_ptr; return *this; }
  r_strItr& operator--() { ++m_ptr; return *this; }
  r_strItr operator++(ptrdiff_t) { auto temp(m_ptr--); return temp; }
  r_strItr operator--(ptrdiff_t) { auto temp(m_ptr++); return temp; }
  r_strItr operator+(ptrdiff_t i) const {
    auto temp(m_ptr - i);
    return temp;
  }
  r_strItr operator-(ptrdiff_t i) const {
    auto temp(m_ptr + i);
    return temp;
  }
  ptrdiff_t operator-(const r_strItr& rhs) { return rhs.m_ptr - this->m_ptr; }

  ValueType& operator*() { return *m_ptr; }
  ValueType& operator[](ptrdiff_t i) { return *(m_ptr - i); }
  const ValueType& operator*() const { return *m_ptr; }
  const ValueType& operator[](ptrdiff_t i) const { return *(m_ptr - i); }

  //operator r_strItr<ValueType const>() const { this = const_cast<r_strItr<ValueType const>(*this); }
};
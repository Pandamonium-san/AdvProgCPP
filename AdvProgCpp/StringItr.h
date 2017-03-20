#pragma once
#include <iterator>

template<typename ValueType, int step>
class baseItr : public std::iterator<
  std::bidirectional_iterator_tag,
  ValueType,
  ptrdiff_t,
  ValueType*,
  ValueType&>
{
protected:
  ValueType* m_ptr;
public:
  baseItr(ValueType* ptr = nullptr) { this->m_ptr = ptr; }
  baseItr(const baseItr& other) = default;
  virtual ~baseItr() {}

  baseItr& operator=(const baseItr& rhs) = default;
  bool operator==(const baseItr& rhs) const { return m_ptr == rhs.m_ptr; }
  bool operator!=(const baseItr& rhs) const { return m_ptr != rhs.m_ptr; }
  ValueType& operator*() const { return *m_ptr; }

  baseItr& operator+=(ptrdiff_t i) { m_ptr += i*step; return *this; }
  baseItr& operator-=(ptrdiff_t i) { m_ptr -= i*step; return *this; }
  baseItr& operator++() { m_ptr += step; return *this; }
  baseItr& operator--() { m_ptr -= step; return *this; }
  baseItr operator++(int) { auto temp(m_ptr); m_ptr += step; return temp; }
  baseItr operator--(int) { auto temp(m_ptr); m_ptr -= step;  return temp; }
  baseItr operator+(ptrdiff_t i) const { auto temp(m_ptr + i*step); return temp; }
  baseItr operator-(ptrdiff_t i) const { auto temp(m_ptr - i*step); return temp; }
  ptrdiff_t operator-(const baseItr& rhs) const { return (this->m_ptr - rhs.m_ptr) * step; }

  ValueType& operator[](ptrdiff_t i) const { return *(m_ptr + i * step); }
  operator baseItr<ValueType const, step>() const { return baseItr<ValueType const, step>(m_ptr); }
  friend bool operator<(const baseItr& lhs, const baseItr& rhs) { return (lhs.m_ptr - rhs.m_ptr)*step < 0; }
  friend bool operator>(const baseItr& lhs, const baseItr& rhs) { return (lhs.m_ptr - rhs.m_ptr)*step > 0; }
};

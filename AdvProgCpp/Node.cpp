#pragma once
#include "stdafx.h"
#include "Node.h"

template<class ValueType>
Node<ValueType>::Node(ValueType item)
{
  this->data = item;
}

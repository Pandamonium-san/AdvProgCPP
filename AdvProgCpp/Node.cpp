#pragma once
#include "stdafx.h"
#include "Node.h"

template<class T>
Node<T>::Node(T item)
{
  this->data = item;
}

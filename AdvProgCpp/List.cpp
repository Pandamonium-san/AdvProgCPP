#pragma once
#include "stdafx.h"
#include "List.h"
#include "Link.cpp"

template<class T>
List<T>::List()
{
  next = this;
  prev = this;
}

template<class T>
List<T>::~List()
{
  T* next2;
  for (T* it = Next(); it != nullptr;)
  {
    next2 = it->Next();
    delete it;
    it = next2;
  }
}

template<class T>
T * List<T>::First() 
{
  return dynamic_cast<T*>(next);
}

template<class T>
const T * List<T>::First() const
{
  return dynamic_cast<T*>(next);
}

template<class T>
T * List<T>::Last() 
{
  return dynamic_cast<T*>(prev);
}

template<class T>
const T * List<T>::Last() const
{
  return dynamic_cast<T*>(prev);
}

template<class T>
T* List<T>::InsertFirst(T* item)
{
  return InsertAfter(item);
}

template<class T>
T* List<T>::PopFirst()
{
  return DeleteAfter();
}

template<class T>
T* List<T>::InsertLast(T* item)
{
  return InsertBefore(item);
}

template<class T>
void List<T>::Check() const {
  const Link<T> *node = this, *nextNode = next;
  do {
    assert(node->next == nextNode && nextNode->prev == node);
    node = nextNode;
    nextNode = nextNode->next;
  } while (node != this);
}

template<class T>
std::ostream & List<T>::Print(std::ostream & cout) const
{
  for (const Link<T>* item = First(); item; item = item->Next())
  {
    item->Print(cout) << ' ';
  }
  cout << '\n';
  return cout;
}

template<class T>
void List<T>::TestDLL() {
  List<Node<int>> myList;
  myList.Check();
  myList.InsertFirst(new Node<int>(5));
  myList.Check();
  myList.InsertFirst(new Node<int>(4));
  myList.Check();
  Node<int> * node3 = myList.InsertFirst(new Node<int>(3));
  myList.InsertFirst(new Node<int>(2));
  myList.InsertFirst(new Node<int>(1));
  myList.InsertFirst(new Node<int>(5));
  myList.InsertFirst(new Node<int>(4));
  myList.InsertFirst(new Node<int>(3));
  myList.InsertFirst(new Node<int>(2));
  myList.InsertFirst(new Node<int>(1));
  myList.Check();
  std::cout << myList;
  node3->Next();
  Node<int> * temp2 = myList.Find(2);
  Node<int> * temp3 = temp2->Find(1);
  Node<int> * temp5 = temp3->DeleteAfter();   //ta bort andra 2:an
  myList.Check();
  assert(temp5->data == 2);
  std::cout << myList;
  delete temp5;

  Node<int> * tmpx = myList.Find(5);
  delete tmpx->DeleteAfter();
  myList.Check();
  std::cout << myList;
  tmpx = myList.Find(3);
  tmpx = tmpx->Find(3);
  tmpx->InsertBefore(new Node<int>(2))->InsertBefore(new Node<int>(1));
  std::cout << myList;
  myList.Check();
  for (int i = 1; i < 6; i++)
  {
    Node<int> * node = myList.PopFirst();
    assert(node->data == i);
    delete node;
  }
  //assert(myList.PopFirst()->data == 1);
  //assert(myList.PopFirst()->data == 2);
  //assert(myList.PopFirst()->data == 3);
  //assert(myList.PopFirst()->data == 4);
  //assert(myList.PopFirst()->data == 5);
  myList.Check();
  for (int i = 1; i < 6; i++)
  {
    Node<int> * node = myList.PopFirst();
    assert(node->data == i);
    delete node;
  }
  //assert(myList.PopFirst()->data == 1);
  //assert(myList.PopFirst()->data == 2);
  //assert(myList.PopFirst()->data == 3);
  //assert(myList.PopFirst()->data == 4);
  //assert(myList.PopFirst()->data == 5);
  assert(myList.PopFirst() == nullptr);
  assert(myList.PopFirst() == nullptr);
  std::cout << myList << "end";
  myList.Check();
  std::cin.get();
}

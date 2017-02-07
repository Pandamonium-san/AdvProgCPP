// AdvProgCpp.cpp : Defines the entry point for the console application.
//

#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#define _CRTDBG_MAP_ALLOC
#include "stdafx.h"
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "List.cpp"
#include "Node.cpp"
#include "String.h"

using namespace std;

void TestString()
{
  String str("hello"), str2(str);
  str = "sup";
  assert(str == "sup");
  assert(str2 == "hello");
  str = str2;
  assert(str == str);
  str = String("blue");
  assert(str == "blue");

  String a("hey");
  assert(a[0] == 'h');
  assert(a[1] == 'e');
  assert(a[2] == 'y');
  assert(a[3] == '\0');
  a.reserve(20);
  assert(a.size() == 20);
  try {
    char c = a.at(21);
  }
  catch (const out_of_range& oor)
  {
    cout << "Index out of range: " << oor.what() << endl;
  }

  String b("Hello"), c("world!");
  a = b + c;
  a = b + " " + c;
  assert(a == "Hello world!");

  const char* p = a.data();
  assert(p == a);

  b += " ";
  b += c;
  assert(b == "Hello world!");
}

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  //List<Node<float>> LL;
  //LL.InsertFirst(new Node<float>(5));
  //LL.TestDLL();
  TestString();
  std::cin.get();
  return 0;
}


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
  String a("char");
  assert(a == "char");
  String b(a);
  assert(b == "char");
  assert(b.size() == 4);
  String c(a + b);
  assert(c == "charchar");
  cout << c << endl;
  b = c;
  assert(b == "charchar");
  b = "Hello";
  assert(c == "charchar");
  a = '!';
  assert(a == "!");
  c = b + a + " Hi";
  assert(c == "Hello! Hi");
  cout << c << endl;
  c += a;
  c += "..?";
  assert(c == "Hello! Hi!..?");
  cout << c << endl;
  c[9] = '.';
  c.at(c.size() - 1) = '!';
  assert(c == "Hello! Hi...!");
  cout << c << endl;
  try {
    char x = c.at(21);
  }
  catch (const out_of_range& oor)
  {
    cout << "Index out of range: " << oor.what() << endl;
  }
  assert(c == "Hello! Hi...!");
  cout << c << endl;

  const char* d = c.data();
  cout << d << endl;
  assert(d == c);
  c = "12345";
  c.reserve(50);
  assert(c.capacity() == 50);
  c.push_back('!');
  assert(c == "12345!");
  c.shrink_to_fit();
  cout << "String: '" << c << '\'' << endl;
  cout << "Size: " << c.size() << endl;
  cout << "Capacity: " << c.capacity() << endl;

  c.resize(5);
  assert(c == "12345");
  c.push_back('!');
  cout << "String: '" << c << '\'' << endl;
  cout << "Size: " << c.size() << endl;
  cout << "Capacity: " << c.capacity() << endl;

  const String str = "boohoo";
  //str.at(0) = 'a';  // compiler error
  //str[0] = 'a';     // compiler error

  String str2("");
  assert(str2.size() == 0);
  str2 += "";
  assert(str2 == "");

  for (int i = 0; i < 1000; i++)
    str2.push_back('0');
  cout << "Number of chars copied: " << g_ops << endl;
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


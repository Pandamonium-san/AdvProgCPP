#include <stdlib.h>
#include "stdafx.h"
#include "Tests.h"
#include "List.cpp"
#include "Node.cpp"
#include "String.h"
#include "Algorithms.h"
#include <vector>
#include <time.h>
#include <algorithm>
#include <numeric>
#include <forward_list>
#include <string>

using namespace std;

#define VG

namespace Tests
{
  void TestDLL() {
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

    std::cout << "DLL test passed" << endl << endl;
    std::cin.get();
  }
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
    //char& ch = str[0];// compiler error

    String str2("");
    assert(str2.size() == 0);
    str2 += "";
    assert(str2 == "");

    for (int i = 0; i < 100; i++)
      str2.push_back('\0');
    str2.push_back('W');
    a = str2;
    cout << a << endl;
    cout << str2 << endl;

    a = "hej";
    a.push_back('\0');
    a.push_back('\0');
    a.push_back('a');
    a.push_back('b');
    b = a;
    b.push_back('c');
    assert(a != b);
    cout << a << endl;
    cout << b << endl;

    String x("bae");
    String y = x;
    x.reserve(10);
    y.resize(20);
    x.push_back('b');
    y.push_back('b');
    y.push_back('\0');
    y.push_back('b');
    cout << x << endl;
    cout << y << endl;
    assert(x == "baeb");
    assert(x.capacity() == 10);
    assert(y.size() > 10);
    assert(y.capacity() > 10);


    cout << "String test passed" << endl << endl;
  }

  void TestPushBackReallocation() {
    String str("hej");
    assert(str.size() <= str.capacity());

#ifdef VG
    //If VG we try to take 20 empty places: (size+1 < capacity)
    //we push_back one more until it is more then 20 places left (or sting to big)
    while (str.size() + 20 >= str.capacity() && str.size() < 1000)
      str.push_back('A' + rand() % 32);
    assert(str.size() < 1000);	//If this fail it prbably the case that capacity is increased with a constant.
#endif //VG

    auto internalBuf = str.data();
    auto cap = str.capacity();
    auto siz = str.size();
    int i;
    for (i = siz + 1; i <= cap; ++i) {
      str.push_back(char(i) + 'a');
      assert(internalBuf == str.data());
      assert(cap == str.capacity());
      assert(i == str.size());
    }
    str.push_back(char(i));
    assert(internalBuf != str.data());
    assert(cap < str.capacity());
    assert(i == str.size());

    assert(str.size() != str.capacity());
    internalBuf = str.data();
    cap = str.capacity();
    siz = str.size();
    str.shrink_to_fit();
    assert(internalBuf != str.data());
    assert(str.size() == str.capacity());
    assert(i == str.size());
  }
  void TestStringG() {
    //-	String()
    String str0;
    String str00("");
    assert(str0 == str00);
    str0 != str00;
    //-	String(Str舅g str舅g)
    String s1("foo"); assert(s1 == "foo");
    String str(s1); assert(str == "foo");
    String s3("bar");  assert(s3 == "bar");

    //-	~String() Kom ih虍 destruktorn!
    delete new String("hej");

    //	-	operator =(Str舅g str舅g)
    assert((str = s3) == s3);
    assert((str = str) == s3);	//self assignment


    String str1("foo"), str2("bar"), str3("hej");
    str3 = str = str1;
    assert(str3 == str);
    assert(str1 == str);

    // operator bool

    assert(String("huj"));
    assert(!String(""));

    //-	operator== 
    //testas erallt!


    //-	operator[](int i) som indexerar utan range check.
    str = "bar";
    str[-1]; str[1000];	//No error
    assert(str[1] == 'a');
    str[1] = 'y';
    assert(str[1] == 'y');

    const String sc(str);
    assert(sc[1] == 'y');
    assert(std::is_const<std::remove_reference< decltype(sc[1])>::type>::value); //Kolla att det blir en const resultat av indexering

                                                                                 //-	push_back(char c) l臠ger till ett tecken sist.
    str = "bar";
    str.push_back('a');
    assert(str == "bara");

    //-	size(), capacity() and reloccation test;
    TestPushBackReallocation();

    cout << String("hej\n");
    cout << "Om det står hej på föregående rad så är TestFöGodkänt klar\n";

  }
  void TestStringVG() {
#ifdef VG
    String str("bar");

    //-	at(int i) som indexerar med range check
    try {
      str.at(-1);
      assert(false);
    }
    catch (std::out_of_range&) {};
    try {
      str.at(3);
      assert(false);
    }
    catch (std::out_of_range&) {};

    //- at indexerar

    //-	at(int i) 
    str = "bar";
    assert(str.at(1) == 'a');
    str.at(1) = 'y';
    assert(str.at(1) == 'y');

    const String strC(str);
    assert(strC.at(1) == 'y');
    assert(std::is_const<std::remove_reference< decltype(strC.at(1))>::type>::value); //Kolla att det blir en const resultat av indexering

                                                                                      // ConvertToChars
    const char* temp = strC.data();
    assert(strC.size() == 3);
    assert(std::memcmp(temp, strC.data(), strC.size()) == 0);
    assert(temp[strC.size()] == '\0');

    //	reserve()
    auto internalBuf = str.data();
    auto cap = str.capacity();
    auto siz = str.size();

    str.reserve(cap);
    assert(internalBuf == str.data());
    assert(cap == str.capacity());
    assert(siz == str.size());

    str.reserve(cap + 1);
    assert(internalBuf != str.data());
    assert(cap + 1 == str.capacity());
    assert(siz == str.size());

    /////////////////
    //-	operator+=(Str舅g str舅g) som tolkas som konkatenering.
    //foo, bar, hej
    String str1("foo"), str2("bar"), str3("hej");
    ((str = "xyz") += str1) += (str3 += str1);
    assert(str3 == "hejfoo" && str == "xyzfoohejfoo" && str1 == "foo");

    //+= som f蚌 plats;
    str = "bar";
    str.reserve(10);
    str += "foo";
    assert(str == "barfoo");

    //+= som inte f蚌 plats;
    str.reserve(10);
    str = "";
    int i;
    for (i = 0; str.size() < str.capacity(); ++i)
      str.push_back('0' + i);
    str1 = "bar";
    str += str1;
    for (int k = 0; k < i; ++k)
      assert(str[k] == '0' + k);
    assert(str[i] == 'b');
    //+= Sj舁v assignment	//Borde testa med att capacity tar slut!
    str = "foo";
    str += str;
    assert(str == "foofoo");

    //-	operator+
    str = "bar";
    assert(str + String("foo") == "barfoo");

    //move
    const char* strdata = str.data();
    String mStr(std::move(str));
    assert(strdata == mStr.data());
    assert(nullptr == str.data());

    str = std::move(mStr);
    assert(strdata == str.data());
    assert(nullptr == mStr.data());

    cout << "\nTestFörVälGodkänt klar\n";
#endif //VG
  }

  void TestAlgorithmsUppg1()
  {
    srand(time(NULL));

    // sort std::vector
      //initialize
    std::vector<int> alg1;
    for (size_t i = 0; i < 25; i++)
      alg1.push_back(rand() % 100);
      //print
    cout << "Initial std:vector<int>" << endl;
    for (size_t i = 0; i < 25; i++)
      cout << alg1[i] << '\t';
    cout << endl;
      //sort
    std::sort(alg1.begin(), alg1.end());
      //print
    cout << "Sorted std:vector<int>" << endl;
    for (size_t i = 0; i < 25; i++)
      cout << alg1[i] << '\t';
    cout << "\n\n\n";
      //assert
    for (size_t i = 0; i < 24; i++)
      assert(alg1[i] <= alg1[i + 1]);

    // sort int
      //initialize
    int alg2[25];
    iota(alg2, &alg2[25], 0);
    random_shuffle(alg2, &alg2[25]);
      //print
    cout << "Initial int[]" << endl;
    for (size_t i = 0; i < 25; i++)
      cout << alg2[i] << '\t';
    cout << endl;
      //sort
    std::sort(alg2, &alg2[25]);
      //print
    cout << "Sorted int[]" << endl;
    for (size_t i = 0; i < 25; i++)
      cout << alg2[i] << '\t';
    cout << "\n\n\n";
      //assert
    for (size_t i = 0; i < 24; i++)
      assert(alg2[i] <= alg2[i + 1]);

    // sort std::vector in reverse
    std::vector<int> alg3;
    for (size_t i = 0; i < 25; i++)
      alg3.push_back(rand() % 100);
    cout << "Initial std:vector<int>" << endl;
    for (size_t i = 0; i < 25; i++)
      cout << alg3[i] << '\t';
    cout << endl;
    std::sort(alg3.rbegin(), alg3.rend());
    cout << "Sorted std:vector<int> descending" << endl;
    for (size_t i = 0; i < 25; i++)
      cout << alg3[i] << '\t';
    cout << "\n\n\n";
    for (size_t i = 0; i < 24; i++)
      assert(alg3[i] >= alg3[i + 1]);

    // sort int[] in reverse
    int alg4[25];
    iota(alg4, &alg4[25], 0);
    random_shuffle(alg4, &alg4[25]);
    cout << "Initial int[]" << endl;
    for (size_t i = 0; i < 25; i++)
      cout << alg4[i] << '\t';
    cout << endl;
    std::sort(alg4, &alg4[25], [](int a, int b) {return a > b; });
    cout << "Sorted int[] descending" << endl;
    for (size_t i = 0; i < 25; i++)
      cout << alg4[i] << '\t';
    cout << "\n\n\n";
    for (size_t i = 0; i < 24; i++)
      assert(alg4[i] >= alg4[i + 1]);
  }
  void TestAlgorithmsUppg2()
  {
    srand(time(NULL));
    std::vector<int> cont;
    for (size_t i = 0; i < 25; i++)
      cont.push_back(rand() % 100);
    cout << "Initial" << endl;
    for (size_t i = 0; i < 25; i++)
      cout << cont[i] << '\t';
    cout << "\n";
    cont.erase(
      std::remove_if(cont.begin(), cont.end(), [](int i) {return i % 2 == 0; }),
      cont.end());
    cout << "Removed evens" << endl;
    for (std::vector<int>::iterator itr = cont.begin(); itr != cont.end(); itr++)
      cout << *itr << '\t';
    cout << "\n\n\n";
    for (std::vector<int>::iterator itr = cont.begin(); itr != cont.end(); itr++)
      assert(*itr % 2 == 1);
  }
  void TestAlgorithmsUppg3()
  {
    srand(23);
    forward_list<int> fl;
    for (size_t i = 0; i < 25; i++)
      fl.push_front(rand()%100);

    cout << "Initial forward list" << endl;
    for (forward_list<int>::iterator itr = fl.begin(); itr != fl.end(); itr++)
    {
      cout << *itr << '\t';
    }
    cout << endl;
    Algorithms::ForwardSort(fl.begin(), fl.end());
    cout << "Sorted forward list" << endl;
    for (forward_list<int>::iterator itr = fl.begin(); itr != fl.end(); itr++)
    {
      cout << *itr << '\t';
    }
    cout << "\n\n\n";
  }

  void TestStringItr()
  {
    const String str = "foobar2000";
    String::const_iterator itr = str.cbegin();
    cout << str << endl;
    while(itr != str.cend())
    cout << *(itr++) << endl;
    
  }

}
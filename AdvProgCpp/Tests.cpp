#include <stdlib.h>
#include "stdafx.h"
#include "Tests.h"
#include "List.cpp"
#include "Node.cpp"
#include "String.h"
#include "Algorithms.h"
#include "SharedPtr.cpp"
#include <vector>
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
    unsigned int i;
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
    forward_list<int> fl;
    for (size_t i = 0; i < 25; i++)
      fl.push_front(rand() % 100);

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
    String str = "foobar2000";
    String::const_iterator itr = str.begin();   //iterator->const_iterator conversion
    //String::iterator itr2 = str.cbegin();     //const_iterator->iterator conversion compile error
    String::const_reverse_iterator itr3 = str.rbegin();
    //String::reverse_iterator itr4 = str.crbegin();
    if (itr > str.begin())
      cout << *itr << endl;
    cout << *itr << endl;
    cout << str << endl;
    while (itr != str.end())
      cout << *(itr++);
    cout << endl;
    std::random_shuffle(str.begin(), str.end());
    cout << str << endl;
  }
  void TestItt() {
    //-	typdefs f iterator, const_iterator,  reverse_iterator och const_revers_iterator
    String::iterator Str;
    String::reverse_iterator rStr;

    //-	funktionerna begin, end, cbegin, cend, rbegin, rend, crbegin och crend.

    TestIttPart();
    TestIttPartR();
#ifdef VG
    String::const_iterator cStr;
    String::const_reverse_iterator crStr;
    TestIttPartC();
    TestIttPartCR();
#endif VG
    TestIttInAlg();
    TestRevIttInAlg();

    //-	default constructor, copy constructor och tilldelning (=) 
    String s("foobar");
    Str = s.begin();
    rStr = s.rbegin();

#ifdef VG
    cStr = s.cbegin();
    crStr = s.crbegin();
#endif VG

    *Str = 'a';
    //	*(cStr+1)='b';	//Sak ge kompileringsfel!
    *(rStr + 2) = 'c';
    //	*(crStr+3)='d';	//Sak ge kompileringsfel!
    assert(s == "aoocar");

    cout << "\nTestItt G klar";
#ifdef VG
    cout << "\nTestItt VG klar\n";
#endif VG
  }
  void TestIttInAlg() {

    static const int N = 26;
    String v;
    v.reserve(N);
    for (int i = 0; i < N; ++i) {
      v.push_back('a' + i);
    }
    v.begin();
    auto b = std::begin(v);
    auto e = std::end(v);

    std::random_shuffle(b, e);

    cout << v << endl;
    std::stable_sort(b, e);

    cout << v << endl;
    assert(v == "abcdefghijklmnopqrstuvwxyz");
  }
  void TestRevIttInAlg() {

    static const int N = 26;
    String v;
    v.reserve(N);
    for (int i = 0; i < N; ++i) {
      v.push_back('a' + i);
    }
    auto b = std::rbegin(v);
    auto e = std::rend(v);

    std::random_shuffle(b, e);

    cout << v << endl;
    std::stable_sort(b, e);

    cout << v << endl;
    assert(v == "zyxwvutsrqponmlkjihgfedcba");
  }
  /*	*it, ++it, it++, (it+i), it[i], == och !=	*/
  void TestIttPart() {
    String s1("foobar");
    for (auto i = s1.begin(); i != s1.end(); i++)
      cout << *i;
    cout << endl;
    auto it = s1.begin();
    assert(*it == 'f');
    assert(*(it++) == 'f' && *it == 'o');
    ++it;
    assert(*++it == 'b');
    assert(*(it + 1) == 'a');
    assert(it[2] == 'r');
  }
  void TestIttPartR() {
    String s1("foobar");
    for (auto i = s1.rbegin(); i != s1.rend(); i++)
      cout << *i;
    cout << endl;
    s1 = "raboof";
    auto it = s1.rbegin();
    assert(*it == 'f');

    assert(*(it++) == 'f' && *it == 'o');
    ++it;
    assert(*++it == 'b');
    assert(*(it + 1) == 'a');
    assert(it[2] == 'r');
  }
#ifdef VG
  void TestIttPartC() {
    String s1("foobar");
    for (auto i = s1.cbegin(); i != s1.cend(); i++)
      cout << *i;
    cout << endl;
    auto it = s1.cbegin();
    assert(*it == 'f');
    assert(*(it++) == 'f' && *it == 'o');
    ++it;
    assert(*++it == 'b');
    assert(*(it + 1) == 'a');
    assert(it[2] == 'r');
  }
  void TestIttPartCR() {
    String s1("foobar");
    for (auto i = s1.crbegin(); i != s1.crend(); i++)
      cout << *i;
    cout << endl;
    s1 = "raboof";
    auto it = s1.crbegin();
    assert(*it == 'f');
    assert(*(it++) == 'f' && *it == 'o');
    ++it;
    assert(*++it == 'b');
    assert(*(it + 1) == 'a');
    assert(it[2] == 'r');
  }
#endif VG

  struct C {
    float value;
    C(float value) :value(value) {};
  };
  struct D : C {
    D(float value) :C(value) { }
  };
  void TestSharedPtr() {
    SharedPtr<C> sp;
    assert(!sp);
    SharedPtr<C> sp2(nullptr);
    assert(!sp2);
    SharedPtr<C> sp3(new C(3));
    assert(sp3);

    assert(sp3.unique());
    SharedPtr<C> sp4(sp3);
    assert(sp4);
    assert(!sp3.unique());

    sp4 = sp3;
    assert(sp4);

    sp4 = sp4;
    assert(sp4);

    SharedPtr<C> sp5(new C(31));
    assert(sp == nullptr);
    assert(sp < sp3);
    assert(!(sp3 < sp));
    assert(sp4 == sp3);
    assert(!(sp4 == sp5));
    assert((sp4 < sp5) || (sp5 < sp4));

    SharedPtr<C> sp41(new C(41));
    SharedPtr<C> sp42(new C(42));
    assert((sp41->value) == (sp41.get()->value));
    assert((sp41->value) != (sp42.get()->value));
    assert(&(*sp41) == (sp41.get()));

    //move
    SharedPtr<C> sp51(std::move(sp41));
    assert(sp51->value == 41);
    assert(!sp41);

    sp51.reset();
    assert(!sp51);
    sp51.reset();
    SharedPtr<C> sp91(new C(11));
    for (size_t i = 0; i < 100; i++)
    {
      SharedPtr<C> shptr(SharedPtr<C>(sp91));
    }
    sp91 = SharedPtr<C>();
  }
#ifdef VG
  void TestSharedPtrVG() {
    //Weak pointer skall ha det som det står VG på nedan
    //-	Konstruktor som tar:		
    //	o	inget	G	VG
    //	o	En SharedPtr	G	VG
    //	o	En WeakPtr	VG	VG

    WeakPtr<C> wp11;
    assert(wp11.expired());
    SharedPtr<C> sp12(new C(12));
    WeakPtr<C> wp13(wp11);
    assert(wp13.expired());
    WeakPtr<C> wp14(sp12);
    assert(!wp14.expired());

    SharedPtr<C> sp17(wp14);
    assert(sp17);

    //-	Destruktor	G	VG
    //	It will test itself
    //-	Tilldelning från en		
    //	o	En SharedPtr	G	VG
    //	o	En WeakPtr			VG
    WeakPtr<C> wp15;
    wp14 = wp11;
    assert(wp14.expired());

    SharedPtr<C> sp33(new C(33));
    wp14 = sp33;
    assert(!wp14.expired());
    wp14 = wp14;
    assert(!wp14.expired());

    sp33.reset();
    assert(!sp33);
    assert(wp14.expired());

    //Shared(weak)
    try {
      SharedPtr<C> slask(wp14);
      assert(false);
    }
    catch (const char* const except) {
      assert(except == "std::bad_weak_ptr");
    }

    //-	funktioner:		
    //	o	lock()		VG
    auto sp51 = wp11.lock();
    assert(!sp51);

    SharedPtr<C>  sp55(new C(55));
    wp14 = sp55;
    sp51 = wp14.lock();
    assert(sp51);
    ////	o	expired()		VG	Redan testat

    //move
    SharedPtr<C> sp61(std::move(sp51));
    assert(sp61->value == 55);
    assert(!sp51);

    sp51 = std::move(sp61);
    sp51 = std::move(sp51);
    assert(sp51->value == 55);
  }
#endif VG

}
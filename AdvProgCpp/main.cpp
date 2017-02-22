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

#include "Tests.h"

using namespace std;
using namespace Tests;

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  //TestDLL();
  /*TestString();
  TestStringG();
  TestStringVG();*/
  /*TestAlgorithmsUppg1();
  TestAlgorithmsUppg2();
  TestAlgorithmsUppg3();*/
  TestStringItr();

  std::cin.get();
  return 0;
}


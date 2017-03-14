#pragma once
#include <assert.h>

namespace Tests 
{
  void TestDLL();

  void TestString();
  void TestPushBackReallocation();
  void TestStringG();
  void TestStringVG();

  void TestAlgorithmsUppg1();
  void TestAlgorithmsUppg2();
  void TestAlgorithmsUppg3();

  void TestStringItr();
  void TestItt();
  void TestIttPart();
  void TestIttPartR();
  void TestIttPartC();
  void TestIttPartCR();
  void TestIttInAlg();
  void TestRevIttInAlg();

  void TestSharedPtr();
  void TestSharedPtrVG();
 
  bool TestAccuracy();
  void TestRationalG();
  void TestRationalVG();

  void TestRational();
}
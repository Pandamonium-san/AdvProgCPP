#pragma once
#include <stdlib.h>
#include <iterator>

namespace Algorithms
{
  template<class FwdItr>
  void Merge(FwdItr begin1, FwdItr end1, FwdItr begin2, FwdItr end2)
  {
    if (begin1 > begin2)
    {

    }
  }

  template<class FwdItr>
  void MergeSort(FwdItr begin, FwdItr end)
  {
    size_t n = distance(begin, end);
    if (n < 4)
    {
      ForwardSort(begin, end);
      return;
    }
    FwdItr mid = begin;
    std::advance(mid, n / 2);

    MergeSort(begin, mid);
    MergeSort(mid, end);
    Merge(begin, mid, mid, end);

  }

  //bubble sort
  template<class FwdItr>
  void ForwardSort(FwdItr begin, FwdItr end)
  {
    bool modified = true;
    while (modified)
    {
      modified = false;
      FwdItr prev = begin;
      for (FwdItr itr = begin; itr != end; itr++)
      {
        FwdItr current = itr;
        if (*current < *prev)
        {
          std::swap(*current, *prev);
          modified = true;
        }
        prev = current;
      }
    }
  }

}
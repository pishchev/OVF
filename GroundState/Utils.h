#pragma once
#include <iostream>

namespace Utils
{
  static double Df(double(*iFunc)(double),double iX, double iDelta = 0.01) 
  {
    return (iFunc(iX + iDelta) - iFunc(iX)) / iDelta;
  }
}
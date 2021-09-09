#include <iostream>
#include <functional>
#include "GNUDrawLib.h"

int main()
{
  GNUDrawer gnuDrawer;

  auto range = Utils::GenerateRange(0, 10, 0.01);
  auto arr = Arrays::Construct();
  arr->Add("x", range);
  arr->Add("sqrt", Utils::GenerateArray(std::function<double(double)>(sqrtl), range));
  gnuDrawer.Add(arr);

  auto arr1 = Arrays::Construct();
  arr1->Add("x", range);
  arr1->Add("atan", Utils::GenerateArray(std::function<double(double)>(atanl), range));
  gnuDrawer.Add(arr1);

  auto form = Formula::Construct("sin(x*2)");
  gnuDrawer.Add(form);
  auto line = VerticalLine::Construct(4);
  gnuDrawer.Add(line);

  gnuDrawer.Draw();
  return 0;
}
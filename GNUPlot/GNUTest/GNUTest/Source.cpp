#include <iostream>
#include "GNUDrawLib.h"

int main()
{
  GNUDrawer gnuDrawer;

  auto range = Generator::GenerateRange(0, 10, 0.01);
  auto arr = Arrays::Construct();
  arr->Add("x", range);
  arr->Add("sqrt", Generator::GenerateArray(sqrt, range));
  gnuDrawer.Add(arr);

  auto arr1 = Arrays::Construct();
  arr1->Add("x", range);
  arr1->Add("atan", Generator::GenerateArray(atan, range));
  gnuDrawer.Add(arr1);

  auto form = Formula::Construct("sin(x*2)");
  gnuDrawer.Add(form);
  auto line = VerticalLine::Construct(4);
  gnuDrawer.Add(line);

  gnuDrawer.Draw();
  return 0;
}
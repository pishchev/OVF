#include <iostream>
#include "GNUDraw.h"
#include "Generator.h"

int main()
{
  GNUDrawer gnuDrawer;
  
  auto range = Generator::GenerateRange(0, 10, 0.01);

  Collumn coll1("x", range);
  gnuDrawer.AddCollumn(coll1);
  Collumn coll2("sin", Generator::GenerateArray(sin, range));
  gnuDrawer.AddCollumn(coll2);
  Collumn coll3("cos", Generator::GenerateArray(cos, range));
  gnuDrawer.AddCollumn(coll3);
  Collumn coll4("sqrt", Generator::GenerateArray(sqrt, range));
  gnuDrawer.AddCollumn(coll4);

  gnuDrawer.Draw();
  return 0;
}
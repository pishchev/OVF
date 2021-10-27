#include <iostream>
#include "GNUDrawLib.h"

double dxdt(double x, double y){
  return 10 * x - 2 * x*y;
}

double dydt(double x, double y){
  return 2 * x * y - 10 * y;
}

void RungeKutta2(const std::vector<double>& iRange, double iStart1, double iStart2 , std::vector<double>& resX, std::vector<double>& resY)
{
  resX = {iStart1};
  resY = {iStart2};
  double step = iRange[1] - iRange[0];
  for (size_t i = 0; i < iRange.size() - 1; i++)
  {
    resX.push_back(resX[i] + step * dxdt(resX[i] + step / 2 * dxdt(resX[i], resY[i]), resY[i] + step / 2 * dydt(resX[i], resY[i])));
    resY.push_back(resY[i] + step * dydt(resX[i] + step / 2 * dxdt(resX[i], resY[i]), resY[i] + step / 2 * dydt(resX[i], resY[i])));
  }
}

int main()
{
  auto range = Utils::GenerateRange(0, 4, 0.01);
  std::vector<double> X, Y;
  RungeKutta2(range, 3, 5 , X, Y);

  GNUDrawer gnuDraw1;
  auto solution = Arrays::Construct();
  solution->Add("x", range);
  solution->Add("X", X);
  solution->Add("Y", Y);
  gnuDraw1.Add(solution);
  gnuDraw1.Draw();

  GNUDrawer gnuDraw2;
  auto phase = Arrays::Construct();
  phase->Add("x", X);
  phase->Add("Phase", Y);
  gnuDraw2.Add(phase);
  gnuDraw2.Draw();

  return 0;
}
#include <iostream>
#include "GNUDrawLib.h"

#include <vector>
#include <functional>

#define KPACUBO false

double origFunc(double iX)
{
  return std::expl(-iX);
}

double dxdt(double iX)
{
  return -iX;
}

std::vector<double> Euler(const std::vector<double>& iRange, double iStart)
{
  std::vector<double> resVec = { iStart };
  double step = iRange[1] - iRange[0];
  for (size_t i = 0; i < iRange.size()-1; i++)
  {
    resVec.push_back(resVec[i] + dxdt(resVec[i])*step);
  }
  return resVec;
}

std::vector<double> RungeKutta2(const std::vector<double>& iRange, double iStart)
{
  double a = 0.5;

  std::vector<double> resVec = { iStart };
  double step = iRange[1] - iRange[0];
  double h = step;
  for (size_t i = 0; i < iRange.size() - 1; i++)
  {
    resVec.push_back(resVec[i] + h * ((1 - 1 / (2 * a))*dxdt(resVec[i]) + 1 / (2 * a) *dxdt(resVec[i] + a * h*dxdt(resVec[i]))));
  }
  return resVec;
}

std::vector<double> RungeKutta4(const std::vector<double>& iRange, double iStart)
{
  std::vector<double> resVec = { iStart };
  double step = iRange[1] - iRange[0];
  for (size_t i = 0; i < iRange.size() - 1; i++)
  {
    double k1 = dxdt(resVec[i]);
    double k2 = dxdt(resVec[i] + step/2 * k1);
    double k3 = dxdt(resVec[i] + step/2 * k2);
    double k4 = dxdt(resVec[i] + step * k3);

    resVec.push_back(resVec[i] + step / 6 * (k1 + 2 * k2 + 2 * k3 + k4));
  }
  return resVec;
}

int main()
{
  auto range = Utils::GenerateRange(0, 10, 0.01);
  auto origFuncArr = Utils::GenerateArray(origFunc, range);
  auto EulerArr = Euler(range, 1);
  auto RungeKutta2Arr = RungeKutta2(range, 1);
  auto RungeKutta4Arr = RungeKutta4(range, 1);

  auto diffEuler = Utils::DiffVector(origFuncArr, EulerArr);
  auto diffRungeKutta2 = Utils::DiffVector(origFuncArr, RungeKutta2Arr);
  auto diffRungeKutta4 = Utils::DiffVector(origFuncArr, RungeKutta4Arr);

  auto arr = Arrays::Construct();
  arr->Add("x", range);


  if (KPACUBO) {
    arr->Add("DiffEuler", diffEuler);
    arr->Add("DiffRungeKutta2", diffRungeKutta2);
    arr->Add("DiffRungeKutta4", diffRungeKutta4);
  }
  else {
    arr->Add("Exp", origFuncArr);
    arr->Add("Euler", EulerArr);
    arr->Add("RungeKutta2", RungeKutta2Arr);
    arr->Add("RungeKutta4", RungeKutta4Arr);
  }

  GNUDrawer gnuDrawer;
  gnuDrawer.Add(arr);
  gnuDrawer.Draw();

  return 0;
}
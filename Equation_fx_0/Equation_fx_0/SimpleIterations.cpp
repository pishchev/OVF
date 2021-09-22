#include "SimpleIterations.h"
#include "Utils.h"
#include <thread>

SimpleIterationsPtr SimpleIterations::Construct(std::function<double(double)> iFunction, double iX0)
{
  return SimpleIterationsPtr(new SimpleIterations(iFunction,iX0));
}

double SimpleIterations::Solve(GNUDrawer & iDrawer)
{
  iDrawer.Add(VerticalLine::Construct(_x0));

  double xn1 = _x0;
  double xn2 = _x0;
  int i = 0;
  while (abs(Phi(xn1) - xn2) >= 10 * std::numeric_limits<double>::epsilon()) {
    xn2 = Phi(xn1);
    xn1 = xn2;

    i++;
    iDrawer.Add(VerticalLine::Construct(xn1));
    iDrawer.Add(Formula::Construct(std::to_string(xn2), "iter" + std::to_string(i)));
  }
  return xn2;
}

void SimpleIterations::DrawPreparing(GNUDrawer & iDrawer)
{
  auto range = Utils::GenerateRange(_x0 - 100, _x0 + 100, 0.01);
  auto x = Utils::GenerateArray([](double iX) {return iX;}, range);
  auto phiValues = Utils::GenerateArray([this](double iX) {return this->Phi(iX);}, range);
  auto arr = Arrays::Construct();
  arr->Add("x", range);
  arr->Add("X", x);
  arr->Add("Phi", phiValues);

  iDrawer.Add(arr);
}

SimpleIterations::SimpleIterations(std::function<double(double)> iFunction, double iX0)
  : _function(iFunction), _x0(iX0)
{
  _k = 0.1;
}

double SimpleIterations::Phi(double iX)
{
  return iX + _k *_function(iX);
}

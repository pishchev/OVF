#include <iostream>
#include "GNUDrawLib.h"

double dxdt(double x, double y) {
  return 998 * x + 1998 * y;
}

double dydt(double x, double y) {
  return - 999 * x - 1999 * y;
}

double u(double t) {
  return 4 * exp(-t) - 3 * exp(-1000 * t);
}
double v(double t) {
  return 3 * exp(-1000*t) - 2 * exp(-t);
}

void EulerClear(const std::vector<double>& iRange, double iStart1, double iStart2, std::vector<double>& X, std::vector<double>& Y)
{
  X = {iStart1};
  Y = {iStart2};
  double step = iRange[1] - iRange[0];
  double h = step;
  for (size_t i = 0; i < iRange.size() - 1; i++)
  {
    X.push_back(X[i] + dxdt(X[i], Y[i])*h);
    Y.push_back(Y[i] + dydt(X[i], Y[i])*h);
  }
}

void EulerHidden(const std::vector<double>& iRange, double iStart1, double iStart2, std::vector<double>& X, std::vector<double>& Y)
{
  X = { iStart1 };
  Y = { iStart2 };
  double step = iRange[1] - iRange[0];
  double h = step;

  double A1 = 999 * h;
  double A2 = 998 * h - 1;
  double B1 = 1999 * h + 1;
  double B2 = 1998 * h;

  for (size_t i = 0; i < iRange.size() - 1; i++)
  {
    Y.push_back((A2*Y[i] + A1 * X[i]) / (B1*A2 - A1 * B2));
    X.push_back(-(B2*Y[i + 1] + X[i]) / A2);
  }
}

int main()
{
  if (1) {
    auto range = Utils::GenerateRange(0, 2, 0.01);
    std::vector<double> X, Y;
    EulerClear(range, 1,1, X, Y);
    GNUDrawer gnuDraw("Clear");
    auto solution = Arrays::Construct();
    solution->Add("x", range);

    solution->Add("U", Utils::GenerateArray(u, range));
    solution->Add("V", Utils::GenerateArray(v, range));

    solution->Add("X", X);
    solution->Add("Y", Y);
    gnuDraw.Add(solution);
    gnuDraw.Draw();
  }
  if(1){
    auto range = Utils::GenerateRange(0, 2, 0.01);
    std::vector<double> X, Y;
    EulerHidden(range, 1, 1, X, Y);
    GNUDrawer gnuDraw("Hidden");
    auto solution = Arrays::Construct();
    solution->Add("x", range);

    solution->Add("U", Utils::GenerateArray(u, range));
    solution->Add("V", Utils::GenerateArray(v, range));

    solution->Add("X", X);
    solution->Add("Y", Y);
    gnuDraw.Add(solution);
    gnuDraw.Draw();
  }
  if(0){
    auto range = Utils::GenerateRange(0, 1, 0.0001);
    std::vector<double> X, Y;
    EulerClear(range, 1, 5, X, Y);
    GNUDrawer gnuDraw("ClearPhase");
    auto solution = Arrays::Construct();
    solution->Add("x", X);
    solution->Add("Phase", Y);
    gnuDraw.Add(solution);
    gnuDraw.Draw();
  }
  if (0) {
    auto range = Utils::GenerateRange(0, 1, 0.0001);
    std::vector<double> X, Y;
    EulerHidden(range, 1, 1, X, Y);
    GNUDrawer gnuDraw("HiddenPhase");
    auto solution = Arrays::Construct();
    solution->Add("x", X);
    solution->Add("Phase", Y);
    gnuDraw.Add(solution);
    gnuDraw.Draw();
  }
  

  return 0;
}
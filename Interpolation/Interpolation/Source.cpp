#include <iostream>
#include "GNUDrawlib.h"

#include <functional>
#include <vector>

#define KPACUBO false

int n = 4;

double xk(double k)
{
  return 1 + k / n;
}

double yk(double xk)
{
  return std::log(xk);
}

double li(double x, double i)
{
  double res = 1;
  for (int j = 0; j <= n ; j++)
  {
    if (j == i)continue;
    res *= x - xk(j);
  }
  return res;
}

double Pn(double x)
{
  double res = 0;
  for (int j = 0; j <= n; j++)
  {
    res += yk(xk(j))*li(x,j)/ li(xk(j), j);
  }
  return res;
}

int main()
{
  auto arr = Arrays::Construct();
  auto range = Utils::GenerateRange(1, 2, 0.01);
  auto ln = Utils::GenerateArray(logf, range);
  arr->Add("x", range);
  if (!KPACUBO) arr->Add("ln", ln);

  for (int i = 4; i <= 15; i++)
  {
    n = i;
    auto P = Utils::GenerateArray(Pn, range);
    auto diffVec = Utils::DiffVector(ln, P);

    if (!KPACUBO) arr->Add("Pn" + std::to_string(i), P);
    if ( KPACUBO) arr->Add("Difference" + std::to_string(i), diffVec);
  }


  GNUDrawer gnuDrawer;
  gnuDrawer.Add(arr);

  gnuDrawer.Draw();

  return 0;
}
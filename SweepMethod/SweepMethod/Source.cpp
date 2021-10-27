#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <vector>
#include <functional>
#include "GNUDrawLib.h"

double secDer(double x) {
  return std::sin(x);
}

//ct1*y(a) + ct2*y'(a) = ct
//dt1*y(b) + dt2*y'(b) = dt

double ct1 = 1;
double ct2 = 0;
double ct  = 0;
double dt1 = 1;
double dt2 = 0;
double dt  = 0;

std::vector<double> Sweep(const std::vector<double>& iRange, double iStart)
{
  double h = iRange[1] - iRange[0];

  //y(j-1) = y(j)*eps(j)+nu(j); j=n,n-1...2

  //eps(k+1) = ck/(bk - ak*eps(k)); k = 1, n-1
  //nu(k+1) = (nk*ak - dk)/(bk - ak*eps(k)); k = 1, n-1

  //eps1 = 

  double a = 1 / (h*h);
  double b = 2 / (h*h);
  double c = 1 / (h*h);

  std::vector<double> eps = { -ct2 / (ct1*h - ct2) };
  std::vector<double> nu = { (ct *h) / (ct1*h - ct2) };

  for (int i = 0; i < iRange.size()-1; ++i)
  {
    eps.push_back(c / (b - a * eps[i]));
    nu.push_back((nu[i] * a - secDer(iRange[i])) / (b - a * eps[i]));
  }

  std::vector<double> Y;
  Y.resize(iRange.size());
  Y[Y.size() - 1] = (dt2 * nu.back() - dt * h) / (dt2 * (1 - eps.back()) + dt1 * h);

  for (int i = iRange.size() - 1; i > 0 ; --i)
  {
    Y[i - 1] = Y[i] * eps[i] + nu[i];
  }

  return Y;
}

int main()
{
  auto range = Utils::GenerateRange(0, M_PI, 0.001);
  auto arr = Arrays::Construct();
  arr->Add("x", range);
  arr->Add("Y", Sweep(range, 0));

  GNUDrawer gnuDraw;
  gnuDraw.Add(arr);
  gnuDraw.Draw();

  return 0;
}
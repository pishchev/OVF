#include <iostream>
#include "GNUDrawLib.h"

#include <vector>

std::vector<double> x;
std::vector<double> t;

double L = 1;

double u_0_t = 0;
double u_L_t = 0;

double u_x_0(double x) 
{
  return x * (1 - x / L)*(1 - x / L);
}

double r = 0;
double a = 0;
double b = 0;
double c = 0;

std::vector<std::vector<double>> u;

double di(size_t n, size_t i) 
{
  return r * u[i + 1][n] + (1 - 2 * r)*u[i][n] + r * u[i - 1][n];
}

void init()
{
  x = Utils::GenerateRange(0, L, 0.02);
  t = Utils::GenerateRange(0, 1, 0.02);

  u.resize(x.size());
  for (size_t i = 0; i < u.size(); i++) {
    u[i].resize(t.size());
    u[i][0] = u_x_0(x[i]);
  }

  r = (t[1] - t[0]) / (2 * (x[1] - x[0]) * (x[1] - x[0]));
  a = -r;
  b = (1 + 2 * r);
  c = -r;
}

double csharp(size_t i)
{
  if (i == 1) return c/b;
  return c / (b - a * csharp(i - 1));
}

double dsharp(size_t n, size_t i)
{
  if (i == 1) return di(n - 1, i) / b;
  return (di(n - 1, i) - a * dsharp(n, i - 1)) / (b - a * csharp(i - 1));
}

void U_n_plus_1(size_t n) {
  std::vector<double> csharpVec;
  std::vector<double> dsharpVec;
  std::vector<double> tn;

  size_t N = x.size() - 2;

  for (size_t i = 1; i < N; i++) {
    csharpVec.push_back(csharp(i));
  }
  for (size_t i = 1; i <= N; i++) {
    dsharpVec.push_back(dsharp(n, i));
    tn.push_back(dsharpVec[i- 1]);
  }
  for (size_t i = N - 1 ; i >= 1; i--) {
    tn[i-1] = dsharpVec[i-1] - csharpVec[i-1] * tn[i];
  }
  for (size_t i = 1; i < u.size()-1; i++) {
    u[i][n] = tn[i - 1];
  }
}

std::vector<double> maxTemp() 
{
  std::vector<double> maxT;
  maxT.resize(u[0].size());
  for (size_t x = 0; x < u.size(); x++) 
  {
    for (size_t t = 0; t < u[0].size(); t++) 
    {
      maxT[t] = std::fmax(u[x][t], maxT[t]);
    }
  }
  return maxT;
}

int main()
{
  init();
  for (size_t i = 1; i < t.size(); i++)
    U_n_plus_1(i);
  u;
  auto maxT = maxTemp();
  ArraysPtr arr = Arrays::Construct();
  arr->Add("x", t);
  arr->Add("Max temperature", maxT);

  GNUDrawer gnuDrawer;
  gnuDrawer.Add(arr);
  gnuDrawer.Draw();

  return 0;
}
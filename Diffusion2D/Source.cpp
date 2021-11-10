#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>
#include "GNUDrawLib.h"

#include <vector>

std::vector<std::vector<std::vector<double>>> u;

std::vector<double> x; 
std::vector<double> y;
std::vector<double> t;

double L = 1;

double xBoundFunction(double t) {
  return std::sin(2 * M_PI*t);
}

double yBoundFunction(double t) {
  return 0;
}

double tStartDistribution(double x, double y) {
  return 0;
}

double aX, aY;
double bX, bY;
double cX, cY;

double X, Y;

double diX(size_t ix, size_t iy, size_t it)
{
  return Y * u[ix][iy + 1][it] + (1 - 2 * Y)*u[ix][iy][it] + Y * u[ix][iy - 1][it];
}

double diY(size_t ix, size_t iy, size_t it)
{
  return X * u[ix + 1][iy][it] + (1 - 2 * X)*u[ix][iy][it] + X * u[ix - 1][iy][it];
}

void init()
{
  //первоначальная инициализация
  x = Utils::GenerateRange(0, L, 0.1);
  y = Utils::GenerateRange(0, L, 0.1);
  t = Utils::GenerateRange(0, 1, 0.01);

  //подготовка массива
  //размеры + начальное распределение по t
  u.resize(x.size());
  for (size_t ix = 0; ix < x.size(); ix++) {
    u[ix].resize(y.size());
    for (size_t iy = 0; iy < y.size(); iy++) {
      u[ix][iy].resize(t.size());
      u[ix][iy][0] = tStartDistribution(x[ix], y[iy]);
    }
  }

  //граничное условие по х
  for (size_t iy = 0; iy < y.size(); iy++) {
    for (size_t it = 0; it < t.size(); it++) {
      u[0][iy][it] = xBoundFunction(t[it]);
      u[x.size() - 1][iy][it] = xBoundFunction(t[it]);
    }
  }

  //граничное условие по y
  for (size_t ix = 0; ix < x.size(); ix++) {
    for (size_t it = 0; it < t.size(); it++) {
      u[ix][0][it] = yBoundFunction(t[it]);
      u[ix][y.size() - 1][it] = yBoundFunction(t[it]);
    }
  }


  //определить коэфициенты
  double dT = t[1] - t[0];
  double dX = x[1] - x[0];
  double dY = y[1] - y[0];

  X = dT / (2 * dX*dX);
  Y = dT / (4 * dY*dY);

  aX = -X;
  bX = 1 + 2 * X;
  cX = -X;

  aY = -Y;
  bY = 1 + 2 * Y;
  cY = -Y;
}

double csharpX(size_t i)
{
  if (i == 1) return cX / bX;
  return cX / (bX - aX * csharpX(i - 1));
}

double csharpY(size_t i)
{
  if (i == 1) return cY / bY;
  return cY / (bY - aY * csharpY(i - 1));
}

double dsharpX(size_t ix, size_t iy, size_t it)
{
  if (ix == 1) return diX(ix, iy, it - 1) / bX;
  return (diX(ix, iy, it - 1) - aX * dsharpX(ix - 1, iy, it)) / (bX - aX * csharpX(ix - 1));
}

double dsharpY(size_t ix, size_t iy, size_t it)
{
  if (iy == 1) return diY(ix, iy, it - 1) / bY;
  return (diY(ix, iy, it - 1) - aY * dsharpY(ix, iy - 1, it)) / (bY - aY * csharpY(iy - 1));
}

void U_n_plus_1_2(size_t iy, size_t it) {
  std::vector<double> csharpVec;
  std::vector<double> dsharpVec;
  std::vector<double> xn;

  size_t N = x.size() - 2;

  for (size_t i = 1; i < N; i++) {
    csharpVec.push_back(csharpX(i));
  }
  for (size_t i = 1; i <= N; i++) {
    dsharpVec.push_back(dsharpX(i, iy, it));
    xn.push_back(dsharpVec[i - 1]);
  }
  for (size_t i = N - 1; i >= 1; i--) {
    xn[i - 1] = dsharpVec[i - 1] - csharpVec[i - 1] * xn[i];
  }
  for (size_t i = 1; i < x.size() - 1; i++) {
    u[i][iy][it] = xn[i - 1];
  }
}

void U_n_plus_1(size_t ix, size_t it) {
  std::vector<double> csharpVec;
  std::vector<double> dsharpVec;
  std::vector<double> yn;

  size_t N = y.size() - 2;

  for (size_t i = 1; i < N; i++) {
    csharpVec.push_back(csharpY(i));
  }
  for (size_t i = 1; i <= N; i++) {
    dsharpVec.push_back(dsharpY(ix, i, it));
    yn.push_back(dsharpVec[i - 1]);
  }
  for (size_t i = N - 1; i >= 1; i--) {
    yn[i - 1] = dsharpVec[i - 1] - csharpVec[i - 1] * yn[i];
  }
  for (size_t i = 1; i < x.size() - 1; i++) {
    u[ix][i][it] = yn[i - 1];
  }
}

void calculate()
{
  size_t ts = t.size() - 1;

  for (size_t it = 1; it < t.size(); it++) {

    std::cout << "Calculating " << it << "/" << ts << "\r";

    for (size_t iy = 1; iy < y.size() - 1; iy++) {
      U_n_plus_1_2(iy, it);
    }

    it++;

    for (size_t ix = 1; ix < x.size() - 1; ix++) {
      U_n_plus_1(ix, it);
    }
  }
}

std::vector<std::vector<double>> temperatureMap(size_t it) {
  std::vector<std::vector<double>> tempMap;

  tempMap.resize(u.size());
  for (auto it = tempMap.begin(); it != tempMap.end(); ++it) {
    it->resize(u[0].size());
  }

  for (size_t ix = 0; ix < tempMap.size(); ix++) {
    for (size_t iy = 0; iy < tempMap[ix].size(); iy++) {
      tempMap[ix][iy] = u[ix][iy][it];
    }
  }

  return tempMap;
}

int main()
{
  init();
  calculate();

  GNUDrawer gnuDrawer;
  for (int i = t.size() - 1; i >= 0 ; i--) {
    std::vector<std::vector<double>> temp = temperatureMap(i);
    gnuDrawer.Add(Matrix::Construct(temp));
  }
  gnuDrawer.Draw();

  return 0;
}
#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "GNUDrawLib.h"
#include "Integrator.h"
#include <functional>
#include <algorithm>

double stepX = M_PI/ 100;
double stepIntegral = M_PI / 1000;
double delta = 1e-5;
auto intRange = Utils::GenerateRange(0, M_PI, stepIntegral);

std::function<double(double)> IntegralFunction(double iM, double iX)
{
  return [iM, iX](double iT) { return  std::cosl(iM * iT - iX * std::sinl(iT)); };
}
double Bessel(double iM, double iX, std::vector<double> iRange)
{
  return 1 / M_PI * Integrate(Simpson::Construct(IntegralFunction(iM, iX), iRange));
}
std::function<double(double)> GenFunction(double iM)
{
  return [iM](double iX) {return Bessel(iM, iX, intRange); };
}
std::vector<double> PseudoDerivatives(const std::vector<double>& iArray)
{
  std::function<double(double)> f = GenFunction(0);
  std::vector<double> derivatives;
  derivatives.push_back((f(iArray[0] + delta) - f(iArray[0])) / delta);
  for (size_t i = 1; i < iArray.size() - 1; i++) {
    derivatives.push_back(  (f(iArray[i] + delta) - f(iArray[i] - delta))/ (2*delta));
  }
  derivatives.push_back(derivatives.back());
  return derivatives;
}
std::vector<double> operator+(const std::vector<double>& Vec1, const std::vector<double>& Vec2)
{
  std::vector<double> sumVec;
  for (size_t i = 0; i < Vec1.size(); i++) {
    sumVec.push_back(Vec1[i] + Vec2[i]);
  }
  return sumVec;
}
double Max(std::vector<double> iVec)
{
  double res = 0;
  for (auto it = ++iVec.begin(); it != --iVec.end(); ++it) {
    //std::cout << std::abs(*it) << std::endl;
    if (*it > res)
      res = *it;
  }
  return res;
}

int main()
{
  if (true) {
    auto range = Utils::GenerateRange(0, 2 * M_PI, stepX);
    auto J1 = Utils::GenerateArray(GenFunction(1), range);
    std::cout << "J1 is computed" << std::endl;
    auto J0 = Utils::GenerateArray(GenFunction(0), range);
    std::cout << "J0 is computed" << std::endl;
    auto J0Der = PseudoDerivatives(range);
    auto J0DerAndJ1 = J0Der + J1;

    std::cout << "Max difference: " << Max(J0DerAndJ1) << std::endl;

    GNUDrawer gnuDraw;

    auto arr = Arrays::Construct();
    arr->Add("x", range);
    arr->Add("J0", J0);
    arr->Add("J1", J1);
    arr->Add("J0Der", J0Der);
    arr->Add("J0Der + J1", J0DerAndJ1);

    gnuDraw.Add(arr);
    gnuDraw.Draw();
  }

  return 0;
}
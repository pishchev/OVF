#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "GNUDrawLib.h"
#include "Integrator.h"

// M_PI/2
double Func1(double iX) {
  return 1 / (1 + iX * iX);
}

double Func2(double iX) {
  return std::powl(iX,1/3) * std::expl(std::sinl(iX));
}

int start = 4;
int end = 32;

void TestTrapezeAbsolute()
{
  GNUDrawer drawer("Trapeze Absolute");

  auto arrs = Arrays::Construct();
  std::vector<double> bottom, top, middle;
  std::vector<double> stepsRange = Utils::GenerateGeometricProgression(start, end, 2);

  for (int i = start; i <= end; i*=2) {
    auto range = Utils::GenerateRange(-1, 1, 1/static_cast<double>(i));
    bottom.push_back(std::abs( Integrate(Trapezoid::Construct(Func1, range, Trapezoid::Bottom)) - M_PI_2));
    top.push_back(std::abs(Integrate(Trapezoid::Construct(Func1, range, Trapezoid::Top)) - M_PI_2));
    middle.push_back(std::abs(Integrate(Trapezoid::Construct(Func1, range, Trapezoid::Middle)) - M_PI_2));
  }
  arrs->Add("x", stepsRange);
  arrs->Add("bottom", bottom);
  arrs->Add("top", top);
  arrs->Add("middle", middle);

  drawer.Add(arrs);
  drawer.Draw();
}

void TestTrapezeRelative()
{
  GNUDrawer drawer("Trapeze Relative");
  auto arrs = Arrays::Construct();
  std::vector<double> bottom, top, middle;
  std::vector<double> stepsRange = Utils::GenerateGeometricProgression(start, end, 2);

  for (int i = start; i <= end; i *= 2) {
    auto range = Utils::GenerateRange(-1, 1, 1 / static_cast<double>(i));
    bottom.push_back(Integrate(Trapezoid::Construct(Func2, range, Trapezoid::Bottom)));
    top.push_back(Integrate(Trapezoid::Construct(Func2, range, Trapezoid::Top)));
    middle.push_back(Integrate(Trapezoid::Construct(Func2, range, Trapezoid::Middle)));
  }
  for (int i = 0; i < bottom.size()-1; i++) {
    bottom[i] = std::abs(bottom[i + 1] - bottom[i]);
    top[i] = std::abs(top[i + 1] - top[i]);
    middle[i] = std::abs(middle[i + 1] - middle[i]);
  }
  stepsRange.pop_back();
  bottom.pop_back();
  top.pop_back();
  middle.pop_back();

  arrs->Add("x", stepsRange);
  arrs->Add("bottom", bottom);
  arrs->Add("top", top);
  arrs->Add("middle", middle);

  drawer.Add(arrs);
  drawer.Draw();
}

void TestSimpsonAbsolute()
{
  GNUDrawer drawer("Simpson Absolute");
  auto arrs = Arrays::Construct();
  std::vector<double> bottom, top, middle;
  std::vector<double> stepsRange = Utils::GenerateGeometricProgression(start, end, 2);

  for (int i = start; i <= end; i *= 2) {
    auto range = Utils::GenerateRange(-1, 1, 1 / static_cast<double>(i));
    bottom.push_back(std::abs(Integrate(Simpson::Construct(Func1, range)) - M_PI_2));
    top.push_back(std::abs(Integrate(Simpson::Construct(Func1, range)) - M_PI_2));
    middle.push_back(std::abs(Integrate(Simpson::Construct(Func1, range)) - M_PI_2));
  }
  arrs->Add("x", stepsRange);
  arrs->Add("bottom", bottom);
  arrs->Add("top", top);
  arrs->Add("middle", middle);

  drawer.Add(arrs);
  drawer.Draw();
}

void TestSimpsonRelative()
{
  GNUDrawer drawer("Simpson Relative");
  auto arrs = Arrays::Construct();
  std::vector<double> bottom, top, middle;
  std::vector<double> stepsRange = Utils::GenerateGeometricProgression(start, end, 2);

  for (int i = start; i <= end; i *= 2) {
    auto range = Utils::GenerateRange(-1, 1, 1 / static_cast<double>(i));
    bottom.push_back(Integrate(Simpson::Construct(Func2, range)));
    top.push_back(Integrate(Simpson::Construct(Func2, range)));
    middle.push_back(Integrate(Simpson::Construct(Func2, range)));
  }
  for (int i = 0; i < bottom.size() - 1; i++) {
    bottom[i] = std::abs(bottom[i + 1] - bottom[i]);
    top[i] = std::abs(top[i + 1] - top[i]);
    middle[i] = std::abs(middle[i + 1] - middle[i]);
  }
  stepsRange.pop_back();
  bottom.pop_back();
  top.pop_back();
  middle.pop_back();

  arrs->Add("x", stepsRange);
  arrs->Add("bottom", bottom);
  arrs->Add("top", top);
  arrs->Add("middle", middle);

  drawer.Add(arrs);
  drawer.Draw();
}

int main()
{
  TestTrapezeAbsolute();
  TestTrapezeRelative();

  TestSimpsonAbsolute();
  TestSimpsonRelative();
  
  return 0;
}
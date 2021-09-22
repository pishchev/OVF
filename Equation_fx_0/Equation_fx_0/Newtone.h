#pragma once
#include "Solver.h"
#include <iostream>

class Newtone;
typedef std::shared_ptr<Newtone> NewtonePtr;

class Newtone : public Method
{
public:
  static NewtonePtr Construct(std::function<double(double)> iFunction, double iX0);
  virtual double Solve(GNUDrawer& iDrawer);
  virtual void DrawPreparing(GNUDrawer& iDrawer);

private:
  Newtone(std::function<double(double)> iFunction, double iX0);
  double Phi(double iX);
  double _x0;
  std::function<double(double)> _function;
};


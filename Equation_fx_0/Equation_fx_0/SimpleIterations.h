#pragma once
#include "Solver.h"
class SimpleIterations;
typedef std::shared_ptr<SimpleIterations> SimpleIterationsPtr;

class SimpleIterations : public Method
{
public:
  static SimpleIterationsPtr Construct(std::function<double(double)> iFunction, double iX0);
  //bool ValidateFunction();
  virtual double Solve(GNUDrawer& iDrawer);
  virtual void DrawPreparing(GNUDrawer& iDrawer);

private:
  SimpleIterations(std::function<double(double)> iFunction, double iX0);
  double Phi(double iX);
  double _x0;
  double _k;
  std::function<double(double)> _function;
};


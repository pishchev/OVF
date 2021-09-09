#pragma once
#include "Solver.h"
class SimpleIterations;
typedef std::shared_ptr<SimpleIterations> SimpleIterationsPtr;

class SimpleIterations : public Method
{
public:
  static SimpleIterationsPtr Construct(double(*iFunction)(double), double iX0);
  //bool ValidateFunction();
  virtual double Solve(GNUDrawer& iDrawer);
  virtual void DrawPreparing(GNUDrawer& iDrawer);

private:
  SimpleIterations(double(*iFunction)(double), double iX0);
  double Phi(double iX);
  double _x0;
  double _k;
  double(*_function)(double);
};


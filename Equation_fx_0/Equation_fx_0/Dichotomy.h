#pragma once
#include "Solver.h"
#include "GNUDrawLib.h"

class Dichotomy;
typedef std::shared_ptr<Dichotomy> DichotomyPtr;

class Dichotomy : public Method
{
public:
  static DichotomyPtr Construct(std::function<double(double)> iFunction, double iLeftBoard, double iRightBoard);
  bool ValidateFunction();
  virtual double Solve(GNUDrawer& iDrawer);
  virtual void DrawPreparing(GNUDrawer& iDrawer);

private:
  Dichotomy(std::function<double(double)> iFunction, double iLeftBoard, double iRightBoard);
  double _left, _right;
  std::function<double(double)> _function;
};
#pragma once
#include <iostream>
#include "GNUDrawLib.h"

class Method;
typedef std::shared_ptr<Method> MethodPtr;

class Method
{
public:
  virtual double Solve(GNUDrawer& iDrawer) = 0;
  virtual void DrawPreparing(GNUDrawer& iDrawer) = 0;
};

class Solver
{
public:
  Solver(const MethodPtr& iMethod, GNUDrawer& iDrawer);
  double Solve();
private:
  MethodPtr _methodPtr;
  GNUDrawer& _drawer;
};
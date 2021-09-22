#include "Solver.h"

Solver::Solver(const MethodPtr& iMethod, GNUDrawer& iDrawer)
  : _methodPtr(std::move(iMethod)), _drawer(iDrawer)
{
  _methodPtr->DrawPreparing(iDrawer);
}

double Solver::Solve()
{
  return _methodPtr->Solve(_drawer);
}

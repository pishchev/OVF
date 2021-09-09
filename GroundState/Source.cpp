#include <iostream>
#include "GNUDrawLib.h"
#include "Dichotomy.h"
#include "SimpleIterations.h"
#include "Newtone.h"
#include <functional>

double U0 = 1000;
double a = 10;

double GroundStateEnergy(double x) {
  double ctgSqrtArg = 2 * a*a*U0*(1 + x / U0);
  double ctgArg = sqrt(ctgSqrtArg);
  double ctg = 1 / tan(ctgArg);

  double rightArg = -U0 / x - 1;
  double right = sqrt(rightArg);

  return ctg - right;
}

std::string strA = std::to_string(a);
std::string strU0 = std::to_string(U0);
std::string GroundStateFunction = "1/tan(sqrt(2*"+ strA +"*"+ strA +"*"+strU0+"*(1 + x/"+strU0+"))) - sqrt(-" + strU0 + "/x -1)";

void OutputResult(std::function<double(double)> iFunc, double iValue)
{
  std::cout << "X = " << iValue << "; Y(X) = " << iFunc(iValue) << std::endl;
}

int main()
{
  GNUDrawer gnuDrawer;
  
  std::function<double(double)> function = GroundStateEnergy;

  //Solver solver(Dichotomy::Construct(function, -4.7 , -4), gnuDrawer);
  //Solver solver(SimpleIterations::Construct(function, -4.7), gnuDrawer);
  Solver solver(Newtone::Construct(function, -4.7), gnuDrawer);

  OutputResult(function, solver.Solve());
  
  gnuDrawer.Add(Formula::Construct(GroundStateFunction, "function"));
  gnuDrawer.Draw();
  return 0;
}
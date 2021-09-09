#include "Newtone.h"
#include "Utils.h"

NewtonePtr Newtone::Construct(double(*iFunction)(double), double iX0)
{
  return NewtonePtr(new Newtone(iFunction,iX0));
}

double Newtone::Solve(GNUDrawer & iDrawer)
{
  iDrawer.Add(VerticalLine::Construct(_x0));

  double xn1 = _x0;
  double xn2 = _x0;
  int i = 0;

  while (abs(Phi(xn1) - xn2) >= 10000 * std::numeric_limits<double>::epsilon()) {
    xn2 = Phi(xn1);

    i++;
    std::string strX = std::to_string(xn2);
    std::string strTan = std::to_string(Utils::Df(_function, xn1, 0.0001));
    std::string count = std::to_string(i);

    xn1 = xn2;

    iDrawer.Add(Formula::Construct("(x-"+ strX +")*"+strTan , "tangency" + count));
    iDrawer.Add(VerticalLine::Construct(xn1));
  }
  return xn2;
}

void Newtone::DrawPreparing(GNUDrawer & iDrawer)
{
  auto range = Generator::GenerateRange(_x0 - 3, _x0 + 1, 0.01);
  auto funcValues = Generator::GenerateArray(_function, range);
  auto arr = Arrays::Construct();
  arr->Add("x", range);
  arr->Add("function", funcValues);
  //iDrawer.Add(arr);
}

Newtone::Newtone(double(*iFunction)(double), double iX0)
  : _function(iFunction), _x0(iX0)
{
}

double Newtone::Phi(double iX)
{
  return iX - _function(iX) / Utils::Df(_function, iX, 0.0001);
}

#include "Dichotomy.h"

Dichotomy::Dichotomy(double(*iFunction)(double), double iLeftBoard, double iRightBoard)
  : _left(iLeftBoard), _right(iRightBoard), _function(iFunction)
{
}

DichotomyPtr Dichotomy::Construct(double(*iFunction)(double), double iLeftBoard, double iRightBoard)
{
  return DichotomyPtr(new Dichotomy(iFunction, iLeftBoard, iRightBoard));
}

bool Dichotomy::ValidateFunction()
{
  return _function(_right) * _function(_left) < 0;
}

double Dichotomy::Solve(GNUDrawer& iDrawer)
{
  double midX = 0;
  while (_right - _left >=  10 * std::numeric_limits<double>::epsilon()) {
    midX = (_left + _right) / 2;
    double midF = _function(midX);
    if (_function(_left) * midF <= 0)
      _right = midX;
    else
      _left = midX;

    iDrawer.Add(VerticalLine::Construct(midX));
  }
  return midX;
}

void Dichotomy::DrawPreparing(GNUDrawer & iDrawer)
{
  iDrawer.Add(VerticalLine::Construct(_left));
  iDrawer.Add(VerticalLine::Construct(_right));

  auto range = Generator::GenerateRange(_left, _right, 0.1);
  auto funcValues = Generator::GenerateArray(_function, range);
  auto arr = Arrays::Construct();
  arr->Add("x", range);
  arr->Add("function", funcValues);
  //iDrawer.Add(arr);
}

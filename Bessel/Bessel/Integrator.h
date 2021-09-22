#pragma once
#include <iostream>
#include <functional>
#include <vector>

class IntMethod;
class Trapezoid;
class Simpson;

typedef std::shared_ptr<IntMethod> IntMethodPtr;
typedef std::shared_ptr<Trapezoid> TrapezoidPtr;
typedef std::shared_ptr<Simpson> SimpsonPtr;

class IntMethod
{
public:
  virtual double Integrate() = 0;
};

class Trapezoid : public IntMethod
{
public:
  enum Type
  {
    Bottom,
    Top,
    Middle
  };

  static TrapezoidPtr Construct(std::function<double(double)> iFunction, std::vector<double> iRange, Type iType)
  {
    return TrapezoidPtr(new Trapezoid(iFunction, iRange, iType));
  }

  virtual double Integrate() override
  {
    size_t indX1 = 0;
    size_t indX2 = 1;
    double sum = 0;
    for (; indX2 < _range.size(); ++indX1, ++indX2) {
      sum += Calculate(_range[indX1], _range[indX2]);
    }
    return sum;
  }
private:
  Trapezoid(std::function<double(double)> iFunction, std::vector<double> iRange, Type iType) : _function(iFunction), _range(iRange), _type(iType){}

  double Calculate(double iX0, double iX1)
  {
    double diff = std::abs(iX0 - iX1);
    double f1 = _function(iX0);
    double f2 = _function(iX1);
    switch (_type) {
    case Trapezoid::Bottom:
      return f1 > f2 ? diff * f2 : diff * f1;
    case Trapezoid::Top:
      return f1 < f2 ? diff * f2 : diff * f1;
    case Trapezoid::Middle: 
      return (f1 + f2) / 2 * diff;
    }
    return 0;
  }
  
  Type _type;
  std::function<double(double)> _function;
  std::vector<double> _range;
};

class Simpson : public IntMethod
{
public:
  static SimpsonPtr Construct(std::function<double(double)> iFunction, std::vector<double> iRange)
  {
    return SimpsonPtr(new Simpson(iFunction, iRange));
  }
  static SimpsonPtr Construct(std::function<double(double)> iFunction, double iBegin, double iEnd, double iStep)
  {
    return SimpsonPtr(new Simpson(iFunction, iBegin, iEnd, iStep));
  }

  virtual double Integrate() override
  {
    double sum = 0;
    if (!_range.empty()) {
      size_t indX1 = 0;
      size_t indX2 = 1;
      for (; indX2 < _range.size(); ++indX1, ++indX2) {
        sum += Calculate(_range[indX1], _range[indX2]);
      }   
    }
    else {
      for (double i = _begin; i < _end; i+= _step) {
        sum += Calculate(i, i+_step);
      }
    }
    return sum;
  }
private:

  double Calculate(double iX0, double iX1)
  {
    return (iX1 - iX0) / 6 * (_function(iX0) + 4 * _function((iX0 + iX1) / 2) + _function(iX1));
  }

  Simpson(std::function<double(double)> iFunction, std::vector<double> iRange) : _function(iFunction), _range(iRange) {}
  Simpson(std::function<double(double)> iFunction, double iBegin,double iEnd,double iStep) : _function(iFunction), _begin(iBegin), _end(iEnd), _step(iStep) {}
  std::function<double(double)> _function;
  std::vector<double> _range;
  double _begin, _end, _step;
};

namespace
{
  double Integrate(const IntMethodPtr& _intMet)
  {
    return _intMet->Integrate();
  }
}

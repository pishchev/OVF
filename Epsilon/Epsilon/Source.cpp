#include <iostream>
#include <iomanip>
#include <iomanip>

template <class T>
T SearchEpsilon() {
  T leftValue(0);
  T rightValue(4);
  T epsilon;

  bool find = false;
  while (!find)
  {
    T midValue = (rightValue + leftValue) / 2;
    if (1 + midValue / 2 != 1)
      rightValue = midValue;
    else if (1 + midValue == 1)
      leftValue = midValue;
    else {
      epsilon = midValue;
      find = true;
    }
  }
  return epsilon;
}

template<class T>
int MinPow() {
  int counter = 0;
  T number(1);
  while (number != 0) {
    counter++;
    number /= 10;
  }
  return -counter;
}

template <class T>
size_t MaxPow() {
  size_t counter = 0;
  T number(1);
  while (number * 10 > number) {
    counter++;
    number *= 10;
  }
  return counter;
}

template <class T>
size_t MaxMantissaPow() {
  T number(1);
  size_t counter = 0;
  do {
    counter++;
    number = 1 + pow(static_cast<T>(10), -static_cast<int>(counter));
  } while (1!= number);
  return counter;
}

template <class T>
void Compare() {
  std::cout << "    1 : " << std::setprecision(std::numeric_limits<T>::max_digits10) << 1 << std::endl;
  std::cout << "    1 + e/2: " << std::setprecision(std::numeric_limits<T>::max_digits10) << 1 + std::numeric_limits<T>::epsilon() / 2 << std::endl;
  std::cout << "    1 + e: " << std::setprecision(std::numeric_limits<T>::max_digits10) << 1 + std::numeric_limits<T>::epsilon() << std::endl;
  std::cout << "    1 + e + e/2: " << std::setprecision(std::numeric_limits<T>::max_digits10) << 1 + std::numeric_limits<T>::epsilon() + std::numeric_limits<T>::epsilon() / 2 << std::endl;
}

int main()
{
  std::cout << "Float epsilon: " << SearchEpsilon<float>() << std::endl;
  std::cout << "Double epsilon: " << SearchEpsilon<double>() << std::endl;

  std::cout << "Min pow for float: " << MinPow<float>() <<  std::endl;
  std::cout << "Min pow for double: " << MinPow<double>() << std::endl;

  std::cout << "Max pow for float: " << MaxPow<float>() << std::endl;
  std::cout << "Max pow for double: " << MaxPow<double>() << std::endl;

  std::cout << "Mantissa size for float: " << MaxMantissaPow<float>() << std::endl;
  std::cout << "Mantissa size for double: " << MaxMantissaPow<double>() << std::endl;

  std::cout << "Compare float: " << std::endl;
  Compare<float>();
  std::cout << "Compare double: " << std::endl;
  Compare<double>();
  

  system("pause");
  return 0;
}
#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

class Collumn 
{
public:
  Collumn() = default;
  Collumn(const std::string& iName);
  Collumn(const std::string& iName, const std::vector<double>& iValues);
  size_t Size() const;

  friend class GNUDrawer;
private:
  std::vector<double> _values = {};
  std::string _name;
};

class GNUDrawer
{
public:
  GNUDrawer() = default;
  void Draw() const;
  void AddCollumn(const Collumn& iCollumn);
  void WriteToFile(const std::string& iFile) const;
private:

  size_t _collumnSize = 0;
  std::vector<Collumn> _collumn = {};
};
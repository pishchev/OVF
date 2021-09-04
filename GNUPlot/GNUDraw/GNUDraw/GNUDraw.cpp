#include "GNUDraw.h"

Collumn::Collumn(const std::string & iName)
  : _name(iName)
{
}

Collumn::Collumn(const std::string & iName, const std::vector<double>& iValues)
  : _name(iName), _values(iValues)
{
}

size_t Collumn::Size() const
{
  return _values.size();
}

void GNUDrawer::Draw() const
{
  WriteToFile("tmp.json");

  FILE *gpipe = _popen("gnuplot.exe -persist", "w");
  if (!gpipe)
    throw "Pipe creation error";

  fprintf(gpipe, "set terminal win\n");
  fprintf(gpipe, "set grid xtics ytics mxtics mytics\n");
  for (size_t i = 1; i < _collumn.size(); ++i) {
    std::stringstream command;
    if (i > 1)
      command << "re";
    command << "plot \"tmp.json\" u 1:" << i+1 << " w l t '" << _collumn[i]._name.data() << "(x)'\n";
    fprintf(gpipe, command.str().data());
  }
  fprintf(gpipe, "exit\n");

  _pclose(gpipe);
  std::remove("tmp.json");
}

void GNUDrawer::AddCollumn(const Collumn & iCollumn)
{
  if (_collumn.empty())
    _collumnSize = iCollumn.Size();
  else if (iCollumn.Size() != _collumnSize)
    throw "Collumn sizes are not equal";

  _collumn.push_back(iCollumn);
}

void GNUDrawer::WriteToFile(const std::string & iFile) const
{
  std::ofstream fstream;
  fstream.open(iFile.data(), 'w');
  if (!fstream)
    throw "Can not open file";

  for (auto it = _collumn.begin(); it != _collumn.end(); ++it)
    fstream << std::left << std::setw(20) << it->_name << " ";
  fstream << std::endl;

  for (size_t i = 0; i < _collumnSize; ++i) {
    for (auto it = _collumn.begin(); it != _collumn.end(); ++it)
      fstream << std::left << std::setw(20) << it->_values[i] << " ";
    fstream << std::endl;
  }

  fstream.close();
}

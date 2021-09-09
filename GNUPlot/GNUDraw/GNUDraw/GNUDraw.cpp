#include "GNUDraw.h"

void GNUDrawer::Draw() const
{
  FILE* gPipe = PreparePipe();
  PreparePlot(gPipe);
  DrawPrimitives(gPipe);
}

void GNUDrawer::Add(const PrimitivePtr& iPrimitive)
{
  _primitives.push_back(iPrimitive);
}

void GNUDrawer::DrawPrimitives(FILE * iPipe) const
{
  for (auto it = _primitives.begin(); it != _primitives.end(); ++it) {
    (*it)->Draw(iPipe);
  }
}

FILE * GNUDrawer::PreparePipe() const
{
  FILE *gPipe = _popen("gnuplot.exe -persist", "w");
  if (!gPipe)
    throw "Pipe creation error";
  return gPipe;
}

void GNUDrawer::PreparePlot(FILE * iPipe) const
{
  fprintf(iPipe, "set terminal win\n");
  fprintf(iPipe, "set grid xtics ytics mxtics mytics\n");
  fprintf(iPipe, "plot 0 notitle\n");
}

void GNUDrawer::ClosePipe(FILE * iPipe) const
{
}

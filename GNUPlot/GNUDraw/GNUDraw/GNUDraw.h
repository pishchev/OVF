#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "Primitive.h"


class GNUDrawer
{
public:
  GNUDrawer() = default;
  void Draw() const;
  void Add(const PrimitivePtr& iPrimitive);
private:
  void DrawPrimitives(FILE* iPipe) const;

  FILE* PreparePipe() const;
  void PreparePlot(FILE* iPipe) const;
  void ClosePipe(FILE* iPipe) const;

  std::vector<PrimitivePtr> _primitives = {};
};
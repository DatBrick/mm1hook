#pragma once

#include "Base.h"

struct Callback
{
  unsigned int Type;
  Base *pClass;
  void *pFunc;
  void *pFirstParam;
  void *pSecondParam;
};


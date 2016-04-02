#pragma once

#include "row_col.h"

class board;

struct move
{
  move() {}
  move(const row_col& f, const row_col& t) : from(f), to(t) {}

  void print(const board& b);

  row_col from, to;
};


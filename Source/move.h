#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include "row_col.h"

class board;

struct move
{
  move() {}
  move(const row_col& f, const row_col& t) : from(f), to(t) {}

  void print(const board& b);

  row_col from, to;
};

std::ostream& operator<<(std::ostream& os, move& m);


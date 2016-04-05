#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include "row_col.h"
#include "square.h"

class board;

struct move
{
  move() : from_sq(EMPTY), to_sq(EMPTY) {}

  move(const row_col& f, const row_col& t, const board& b);

  // From/to coords
  row_col from, to;

  // Contents of from and to squares (before this move is performed)
  square from_sq, to_sq;
};

std::ostream& operator<<(std::ostream& os, move& m);


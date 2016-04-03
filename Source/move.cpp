// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include "board.h"
#include "move.h"

std::ostream& operator<<(std::ostream& os, move& m)
{
  // TODO put contents of from and to squares in move type
  return os << m.from << "-" << m.to;
}

void move::print(const board& b)
{
  square f = b.get(from);
  square t = b.get(to);

  if (is_empty(t))
    std::cout << from << "-" << to << "\n";
  else
    std::cout << from << "x" << to << "\n";
}


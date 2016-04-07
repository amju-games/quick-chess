// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include "board.h"
#include "move.h"

move::move(const row_col& f, const row_col& t, const board& b) :
  from(f), to(t), from_sq(b.get(f)), to_sq(b.get(t)), score(0)
{
}

std::ostream& operator<<(std::ostream& os, move& m)
{
  if (get_piece_colour(m.from_sq) == BLACK_PIECE)
    os << "...";

  char PIECES[] = ".pRNBKQ";

  int pt = (int)get_piece_type(m.from_sq);
  if (pt > (int)PAWN)
    os << PIECES[pt]; 

  os << m.from;

  if (is_empty(m.to_sq))
    os << "-";
  else
    os << "x";

  pt = (int)get_piece_type(m.to_sq);
  if (pt > (int)PAWN)
    os << PIECES[pt];

  return os << m.to;
}


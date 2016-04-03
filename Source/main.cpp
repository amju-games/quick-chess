// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include "board.h"
#include "eval.h"
#include "gen_moves.h"
#include "search.h"

int main()
{
  board b;
  b.print();

  evaluator e;
  e.add(new eval_material);
  e.add(new eval_control_centre);

  piece_colour pc = WHITE_PIECE;
  for (int k = 0; k < 100; k++)
  {
    move m;
    find_best_move(e, b, pc, &m);

    // Print move text, prefixed by move number, and "..." if it's black's move.
    std::cout << k / 2 + 1 << ". " << ((k & 1) ? "..." : "") << m << "\n";

    // Do move
    b.do_move(m);
    b.print();

    // Switch player
    pc = (pc == WHITE_PIECE) ? BLACK_PIECE : WHITE_PIECE;

    std::cin.get();
  }
  return 0;
}


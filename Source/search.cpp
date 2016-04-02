// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include "board.h"
#include "eval.h"
#include "gen_moves.h"
#include "search.h"

bool find_best_move(board& b, piece_colour pc, move* m)
{
  // Find all moves for the given piece colour
  move movelist[500];  // there can't be this many moves, right?
  int n = 0;
  gen_moves(b, pc, movelist, n);

  // Evaluate each move
  int alpha = -99999;
  move best_move;
  for (int i = 0; i < n; i++)
  {
    move& m = movelist[i];
//    std::cout << "Move " << i + 1 << ": ";
//    m.print(b);
    b.do_move(m);

    //b.print();

    int score = eval_material().calc_score(b, pc);
    if (score > alpha)
    {
      alpha = score;
      best_move = m;
    }

    b.undo_move();

    //std::cout << "After undo:\n";
    //b.print();
  }
  std::cout << "Best move: ";
  best_move.print(b);
  *m = best_move; 
  std::cout << " Best score: " << alpha << "\n";
  return true;
}


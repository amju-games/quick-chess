// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include "board.h"
#include "eval.h"
#include "gen_moves.h"
#include "search.h"

static const int MAX_DEPTH = 2;

bool find_best_move_depth_first(int depth, evaluator& e, board& b, piece_colour pc, move* m)
{
  if (depth > MAX_DEPTH)
    return true;

  // Find all moves for the given piece colour
  // https://www.chess.com/forum/view/fun-with-chess/what-chess-position-has-the-most-number-of-possible-moves
  move movelist[200];  
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

    int score = e.calc_score(b, pc);
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

bool find_best_move(evaluator& e, board& b, piece_colour pc, move* m)
{
  return find_best_move_depth_first(0, e, b, pc, m);
}


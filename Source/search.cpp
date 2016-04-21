// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include "board.h"
#include "eval.h"
#include "gen_moves.h"
#include "search.h"

// Prints lots of messages!
//#define _DEBUG

#define INF 9999999

static const int MAX_DEPTH = 10;

static std::string name(piece_colour pc)
{
  return (pc == WHITE_PIECE) ? "white" : "black";
}

static std::string sp(int d)
{
  return std::string(d * 4, ' ');
}

// Collect the principal variation as we search.
// http://brucemo.com/compchess/programming/pv.htm
struct line
{
  line() : n(0) {}

  int n;
  move moves[MAX_DEPTH + 1];
};

// Minimax with alpha-beta pruning
// Return score for current position of board b with respect to the player
//  'eval_wrt'. 
int minimax(
  int depth, 
  evaluator& e, piece_colour eval_wrt, board& b, piece_colour pc, 
  line& pv,
  int alpha, int beta,
  int& num_evals
  )
{
  // TODO Also terminate recursion if game is over
  if (depth == 0)
  {
    // Evaluate pos
    pv.n = 0;
    num_evals++;
    int score = e.calc_score(b, eval_wrt);
    return score; 
  }

  line this_line;

  // Find all moves for the given piece colour
  // https://www.chess.com/forum/view/fun-with-chess/what-chess-position-has-the-most-number-of-possible-moves
  move movelist[200];  
  int n = 0;
  gen_moves(b, pc, movelist, n);
 
  // Evaluate the moves and sort, to improve alpha-beta pruning. Evaluation is wrt the player 
  //  whose turn (ply) it currently is.
  eval_and_sort(e, b, pc, movelist, n);

  move best_move;

  // Min or max?
  if (pc == eval_wrt) 
  {
    // Maximising
    for (int i = 0; i < n; i++)
    {
      move& m = movelist[i];

      b.do_move(m);
      int score = minimax(depth - 1, e, eval_wrt, b, flip(pc), this_line, alpha, beta, num_evals);
      b.undo_move();

      if (score > alpha)
      {
        alpha = score;
        best_move = m;
//moves[depth] = best_move; 
//std::cout << sp(depth) << "Depth " << depth << ", Setting move at depth " << depth << " to " << best_move << "\n";

        pv.moves[0] = m;
        memcpy(pv.moves + 1, this_line.moves, this_line.n * sizeof(move));
        pv.n = this_line.n + 1;
      }

      if (beta <= alpha)
      {
        break;
      }
    }
  }
  else 
  {
    // Minimising
    for (int i = 0; i < n; i++)
    {
      move& m = movelist[i];

      b.do_move(m);
      int score = minimax(depth - 1, e, eval_wrt, b, flip(pc), this_line, alpha, beta, num_evals);
      b.undo_move();

      if (score < beta)
      {
        beta = score;
        best_move = m;
//moves[depth] = best_move; 
//std::cout << sp(depth) << "Depth " << depth << ", Setting move at depth " << depth << " to " << best_move << "\n";

        pv.moves[0] = m;
        memcpy(pv.moves + 1, this_line.moves, this_line.n * sizeof(move));
        pv.n = this_line.n + 1;
      }
      if (beta <= alpha)
      {
        break;
      }
    } 
  }

#ifdef _DEBUG
  std::cout << sp(depth) << "Best move: " << best_move << " for " << name(pc) << "\n";
std::cout << sp(depth) << "Depth " << depth << ", Setting move at depth " << depth << " to " << best_move << "\n";

//pv.moves[depth] = best_move; 

#endif

  return (pc == eval_wrt) ? alpha : beta;
}

bool find_best_move(int max_depth, evaluator& e, board& b, piece_colour pc, move* m)
{
  bool ret = false;

  // Number of positions evaluated in total
  int num_evals = 0;

  // Iterative deepening. Increase the max depth by 1 each time, so we search deeper.
  // TODO We should be able to interrupt this, or time out.
 
  // Cap max_depth at real absolute maximum
  max_depth = std::min(max_depth, MAX_DEPTH);
  std::cout << "Max depth: " << max_depth << ".\n";

  for (int depth = 1; depth <= max_depth; depth++)
  {
    std::cout << "Depth " << depth << ": ";

    int alpha = -INF;
    int beta = INF;
    line pv; // principal variation at this depth
    ret = minimax(depth, e, pc, b, pc, pv, alpha, beta, num_evals);

    std::cout << num_evals << " positions evaluated. ";

    // Show the principal variation
    std::cout << "PV: ";
    for (int i = 0; i < depth; i++)
    {
      std::cout << pv.moves[i] << (i < (depth - 1) ? ", " : "\n");
    }

    *m = pv.moves[0];
  }
  return ret;
}


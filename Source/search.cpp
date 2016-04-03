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

static const int MAX_DEPTH = 3;

static std::string name(piece_colour pc)
{
  return (pc == WHITE_PIECE) ? "white" : "black";
}

static std::string sp(int d)
{
  return std::string(d * 4, ' ');
}

static piece_colour flip(piece_colour pc)
{
  return (pc == WHITE_PIECE) ? BLACK_PIECE : WHITE_PIECE;
}

// Simple depth first minimax, no alpha beta yet
// Return score for current position of board b with respect to the player
//  'eval_wrt'. 
int minimax(
  int depth, 
  evaluator& e, piece_colour eval_wrt, board& b, piece_colour pc, move* m,
  int alpha, int beta,
  int& num_evals
  )
{
  // TODO Also terminate recursion if game is over
  if (depth > MAX_DEPTH)
  {
    // Evaluate pos
    num_evals++;
    int score = e.calc_score(b, eval_wrt);
    return score; 
  }

  // Find all moves for the given piece colour
  // https://www.chess.com/forum/view/fun-with-chess/what-chess-position-has-the-most-number-of-possible-moves
  move movelist[200];  
  int n = 0;
  gen_moves(b, pc, movelist, n);

  move best_move;

  // Min or max?
  if (pc == eval_wrt) 
  {
    // Maximising
    int best = -INF;
    for (int i = 0; i < n; i++)
    {
      move& m = movelist[i];

      b.do_move(m);
      int score = minimax(depth + 1, e, eval_wrt, b, flip(pc), nullptr, alpha, beta, num_evals);
      b.undo_move();

      if (score > best)
      {
        best = score;
//        best_move = m;
      } 

      if (best > alpha)
      {
        alpha = best;
        best_move = m;
      }
      if (beta <= alpha)
      {
//std::cout << "Wow, alpha cut off\n";
        break;
      }
    }
  }
  else 
  {
    // Minimising
    int best = INF;
    for (int i = 0; i < n; i++)
    {
      move& m = movelist[i];

      b.do_move(m);
      int score = minimax(depth + 1, e, eval_wrt, b, flip(pc), nullptr, alpha, beta, num_evals);
      b.undo_move();

      if (score < best)
      {
        best = score;
//        best_move = m;
      } 

      if (best < beta)
      {
        beta = best;
        best_move = m;
      }
      if (beta <= alpha)
      {
//std::cout << "Wow, alpha cut off\n";
        break;
      }
    } 
  }

#ifdef _DEBUG
  std::cout << sp(depth) << "Best move: " << best_move << " for " << name(pc) << "\n";
#endif

  if (m)
    *m = best_move; 
  return (pc == eval_wrt) ? alpha : beta;
}

bool find_best_move(evaluator& e, board& b, piece_colour pc, move* m)
{
  int alpha = -INF;
  int beta = INF;
  int num_evals = 0;
  bool ret = minimax(0, e, pc, b, pc, m, alpha, beta, num_evals);

std::cout << num_evals << " positions evaluated. Max depth: " << MAX_DEPTH << "\n";
 
////std::cout << "Alpha: " << alpha << ", beta: " << beta << "\n";

  return ret;
}


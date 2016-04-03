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

static const int MAX_DEPTH = 1;

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
// Return score for current position of board b for player pc
int minimax(
  int depth, 
  evaluator& e, piece_colour eval_wrt, board& b, piece_colour pc, move* m
  )
{
  // TODO Also terminate recursion if game is over
  if (depth > MAX_DEPTH)
  {
    // Evaluate pos
    int score = e.calc_score(b, eval_wrt);
    return score; 
  }

  // Find all moves for the given piece colour
  // https://www.chess.com/forum/view/fun-with-chess/what-chess-position-has-the-most-number-of-possible-moves
  move movelist[200];  
  int n = 0;
  gen_moves(b, pc, movelist, n);

//  const int N = 2;// TODO TEMP TEST
//  if (n > N) n = N; // TODO TEMP TEST

  // Evaluate each move, always wrt the player whose move we are searching for - not
  //  the player at this depth.
  move best_move;
  int alpha = -INF;
  int beta = INF;
  for (int i = 0; i < n; i++)
  {
    move& m = movelist[i];

#ifdef _DEBUG
    std::cout << sp(depth) << "Depth " << depth << ": Trying move: " << m << " for " << name(pc) << "\n";
#endif

    b.do_move(m);

    // Min or max?
    if (pc == eval_wrt) //(depth & 1) == 0)
    {
      int score = minimax(depth + 1, e, eval_wrt, b, flip(pc), nullptr);

#ifdef _DEBUG
std::cout << sp(depth) << "(Max) Depth: " << depth << " move " << m << " scores " << score <<  " wrt " << name(eval_wrt);
#endif

      // Player ply: goal is to maximise 
      if (score > alpha)
      {
#ifdef _DEBUG
std::cout << " - BEST!";
#endif

        alpha = score;
        best_move = m;
      }
#ifdef _DEBUG
std::cout << "\n";
#endif
    }
    else //if ((depth & 1) == 1)
    {
      int score = minimax(depth + 1, e, eval_wrt, b, flip(pc), nullptr);

#ifdef _DEBUG
std::cout << sp(depth) << "(Min) Depth: " << depth << " move " << m << " scores " << score <<  " wrt " << name(eval_wrt);
#endif

      // Opponent ply: goal is to minimise beta
      if (score < beta)
      {
#ifdef _DEBUG
std::cout << " - BEST!";
#endif

        beta = score;
        best_move = m;
      }
#ifdef _DEBUG
std::cout << "\n";
#endif
    } 
    b.undo_move();
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
  bool ret = minimax(0, e, pc, b, pc, m);
 
////std::cout << "Alpha: " << alpha << ", beta: " << beta << "\n";

  return ret;
}


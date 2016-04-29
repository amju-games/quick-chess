// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include "board.h"
#include "eval.h"
#include "gen_moves.h"
#include "search.h"

#define YES_USE_THREADS

// Prints lots of messages!
//#define _DEBUG

// Starting values for alpha and beta
#define INF 9999999

// For allocating arrays where each element represents one ply. Currently 
//  searching 10 plies deep would take ages so is a safe max value.
//  (The search space is ~36**10 positions!)
static const int MAX_DEPTH = 10;

static std::string name(piece_colour pc)
{
  return (pc == WHITE_PIECE) ? "white" : "black";
}

// Make a string of d * 4 spaces, used to indent the debug output according to depth.
static std::string sp(int d)
{
  return std::string(d * 4, ' ');
}

// We collect the principal variation as we search.
// This uses the approach from http://brucemo.com/compchess/programming/pv.htm.

// This type represents one line, i.e. one sequence of moves (plies) from the 
//  current position to some max look-ahead depth. The principal variation is
//  the line we get if both players play optimally - but this is skewed by the
//  'horizon effect' of having a max depth.
struct line
{
  line() : n(0) {}

  int n;
  move moves[MAX_DEPTH + 1];
};

searcher::searcher() : m_max_depth(1), m_pc(WHITE_PIECE)
{
}

searcher::~searcher()
{
  // TODO Join if joinable, to prevent termination. See EMC++ Item 37
}

// Minimax with alpha-beta pruning
// Return score for current position of board b with respect to the player
//  'eval_wrt'. 
int searcher::minimax(
  int depth, 
  evaluator& e, piece_colour eval_wrt, board& b, piece_colour pc, 
  line& pv,
  int alpha, int beta,
  int& num_evals
  )
{
  // We might be running on a thread, and should now stop.
  if (m_stopped)
  {
    return 0;
  }

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

  // Find all moves for the given piece colour. It looks like about 120 is the maximum.
  // https://www.chess.com/forum/view/fun-with-chess/
  //  what-chess-position-has-the-most-number-of-possible-moves
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
  std::cout << sp(depth) << "Depth " << depth << ", Setting move at depth " << 
    depth << " to " << best_move << "\n";

#endif

  return (pc == eval_wrt) ? alpha : beta;
}

bool searcher::find_best_move() ////int max_depth, evaluator& e, board& b, piece_colour pc, move* m)
{
  bool ret = false;

  // Iterative deepening. Increase the max depth by 1 each time, so we search deeper.
  // If running as a worker thread, we can stop the search by setting m_stopped.
 
  // Cap max_depth at real absolute maximum
  m_max_depth = std::min(m_max_depth, MAX_DEPTH);
//  std::cout << "Max depth: " << m_max_depth << ".\n";

  for (int depth = 1; depth <= m_max_depth; depth++)
  {
    // Number of positions evaluated at this depth
    int num_evals = 0;

    int alpha = -INF;
    int beta = INF;
    line pv; // principal variation at this depth
    ret = minimax(depth, m_eval, m_pc, m_board, m_pc, pv, alpha, beta, num_evals);

    std::cout << "Depth " << depth << ": ";
    std::cout << num_evals << " positions evaluated.\n";

    // We might be running on a thread, and should now stop.
    if (m_stopped)
    {
      // Don't set best move so far, as if we were stopped, we didn't properly
      //  evaluate it.
      return ret;
    }
    else
    {
      // Show the principal variation
      std::cout << "PV: ";
      for (int i = 0; i < depth; i++)
      {
        std::cout << pv.moves[i] << (i < (depth - 1) ? ", " : "\n");
      }

      // Lock and set best move member variable
      std::lock_guard<std::mutex> lock(m_mutex);
      m_best_move_so_far = pv.moves[0];
    }
  }
  return ret;
}

void searcher::start_search(int max_depth, const evaluator& e, const board& b, piece_colour pc)
{
  m_max_depth = max_depth;
  m_eval = e;
  m_board = b;
  m_pc = pc;

#ifdef YES_USE_THREADS
  start(); // Executes work() on another thread
#else
  // No-thread version for testing 
  work();
#endif
}

move searcher::get_result()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  return m_best_move_so_far;
}

void searcher::work()
{
//  std::cout << "Working...\n"; 
  find_best_move(); 
}


#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <mutex>
#include "board.h"
#include "eval.h"
#include "worker.h"

// One line (variation), i.e. one sequence of plies from the current position
struct line;

class searcher : public worker
{
public:
  searcher();

  // Start search using iterative deepening. The search happens on a worker 
  //  thread. Call get_result() to get best result found so far.
  void start_search(int max_depth, const evaluator& e, const board& b, piece_colour pc);

  // Get best move found so far. Protected by mutex 
  move get_result();
 
private:
  bool find_best_move(); //int max_depth, evaluator& e, board& b, piece_colour pc, move* m);

  int minimax(
    int depth,
    evaluator& e, piece_colour eval_wrt, board& b, piece_colour pc,
    line& pv,
    int alpha, int beta,
    int& num_evals
  );

  // Implement the thread work function to perform the search, 
  //  using iterative deepening alpha-beta. 
  // Periodically check if we should stop.
  virtual void work() override;

private:
  // Sync access to member vars, specifically m_best_move_so_far. It is written to
  //  during the search, and may also be read with a call to get_result();
  std::mutex m_mutex;

  move m_best_move_so_far; 
  int m_max_depth;
  evaluator m_eval;
  board m_board;
  piece_colour m_pc;
};


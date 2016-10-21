#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include <stack>
#include "row_col.h"
#include "square.h"
#include "move.h"

class board;

// Undo info for one square: the position (row, col) of the square, and
//  the contents it should be set to when we undo the move to which it
//  belongs.
struct undo_sq
{
  row_col m_pos;
  square m_sq;  

  undo_sq() : m_pos(-1, -1), m_sq(EMPTY) {}
  undo_sq(const row_col& p, square s) : m_pos(p), m_sq(s) {}

  bool is_valid() const { return m_pos.row != -1; }

  // Set the contents of the board position
  void do_it(board& b) const;
};

// Ouput, for debugging
std::ostream& operator<<(std::ostream& os, const undo_sq& u);

// Complete undo info for one move, comprised of up to 4 undo squares. 
class undo
{
public:
  // Ctors for up to 4 undo squares, for convenience
  undo() {}

  undo(const undo_sq& u1) { m_undo_sqs[0] = u1; }

  undo(const undo_sq& u1, const undo_sq& u2) 
  { 
    m_undo_sqs[0] = u1; m_undo_sqs[1] = u2; 
  }

  undo(const undo_sq& u1, const undo_sq& u2, const undo_sq& u3) 
  {
    m_undo_sqs[0] = u1; m_undo_sqs[1] = u2; m_undo_sqs[2] = u3; 
  }

  undo(const undo_sq& u1, const undo_sq& u2, const undo_sq& u3, const undo_sq& u4)
  {
    m_undo_sqs[0] = u1; m_undo_sqs[1] = u2; m_undo_sqs[2] = u3; m_undo_sqs[3] = u4;
  }

  void do_it(board& b) const;

  // Ouput, for debugging
  friend std::ostream& operator<<(std::ostream& os, const undo& u);

private:
  // Array of up to 4 undo squares; unused elements are invalid as default cted.
  undo_sq m_undo_sqs[4];
};

// Manages stack of undo info, so can take back all moves made on the board.
class undo_stack
{
public:
  // Push undo info for one move onto the stack
  void push(const undo& u);
 
  // Do the undo info at the top of the stack
  void do_top(board& b) const;

  // Pop element off the stack
  void pop();

  // Empty the stack
  void clear();

private:
  std::stack<undo> m_undo_stack;
};


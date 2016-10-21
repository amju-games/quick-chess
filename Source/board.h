#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include "row_col.h"
#include "square.h"
#include "move.h"
#include "undo_stack.h"

class board
{
public:
  board(); // resets the board

  // Reset the board to game start, clear undo stack
  void reset();

  // Set all squares to empty, clear undo stack
  void clear();

  // Apply the given move to the board, pushing it to the undo stack so it can
  //  be undone.
  void do_move(const move& m);

  // Undo last move made, popping stack of moves
  void undo_move(); 

  // Set the contents of a board position. Does not affect the undo stack, but 
  //  rather is used BY the undo stack to change the board.
  // Could also be used to set up an initial position.
  void set(const row_col& rc, square s);

  // Get the contents of a board position
  square get(const row_col& rc) const;

  // Pretty display
  void print() const;

private:
  // Calc index into 1D array from (row, col)
  int index(const row_col& rc) const;

  // No border, just an 8*8 array of squares. 
  static const int NUM_SQUARES = 8 * 8;
  square m_squares[NUM_SQUARES];

  undo_stack m_undo_stack;
};


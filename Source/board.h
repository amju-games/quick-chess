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
  board();

  void reset();

  void do_move(const move& m);

  // Undo last move made, popping stack of moves
  void undo_move(); 

  void set(const row_col& rc, square s);

  square get(const row_col& rc) const;

  void print() const;

private:
  // Calc index into 1D array from (row, col)
  int index(const row_col& rc) const;

  // Board includes border of 2 squares all around, so instead of 8*8,
  //  the board size is 12*12.
  static const int NUM_SQUARES = 12 * 12;
  square m_squares[NUM_SQUARES];

  undo_stack m_undo_stack;
};


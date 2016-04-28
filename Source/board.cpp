// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <assert.h>
#include <iostream>
#include "board.h"

// For testing, set up a simple position
//#define SIMPLE_BOARD_DEBUG
// Number of pawns for each player in simple position
#define NUM_PAWNS 2 

#ifndef WIN32
#define YES_COLOURS
#endif

board::board() 
{ 
  reset(); 
}

void board::reset()
{
  square INITIAL_POSITIONS[8] = { 
    W_ROOK,
    W_KNIGHT,
    W_BISHOP,
    W_QUEEN,
    W_KING,
    W_BISHOP,
    W_KNIGHT,
    W_ROOK,
  }; 

  for (int i = 0; i < 8; i++)
  {
#ifdef SIMPLE_BOARD_DEBUG
    // TEST only - simple board, with just a few pawns. Or you could set up
    //  some other test position here.
    for (int j = 0; j < 8; j++)
      set(row_col(j, i), EMPTY);
    if (i < NUM_PAWNS) set(row_col(1, i), W_PAWN);
    if (i < NUM_PAWNS) set(row_col(6, i), B_PAWN);
    continue;
#endif

    // Standard initial position
    set(row_col(0, i), INITIAL_POSITIONS[i]);
    set(row_col(1, i), W_PAWN);
    for (int j = 2; j < 6; j++)
      set(row_col(j, i), EMPTY);
    set(row_col(6, i), B_PAWN);
    set(row_col(7, i), (square)((int)INITIAL_POSITIONS[i] | BLACK));
  }
}
  
void board::do_move(const move& m)
{
  square s = get(m.from); // the piece we are moving
  square t = get(m.to); // the contents of the destination sq

  // Add undo data to stack
  // For a regular move, we store the state of the 'from' and 'to' squares
  m_undo_stack.push(undo(undo_sq(m.from, s), undo_sq(m.to, t)));

  set(m.to, s);
  set(m.from, EMPTY);
}

void board::undo_move()
{
  m_undo_stack.do_top(*this);
  m_undo_stack.pop();
}

void board::set(const row_col& rc, square s)
{
  m_squares[index(rc)] = s;
}

square board::get(const row_col& rc) const
{
  return m_squares[index(rc)];
}

void board::print() const
{
  char SQUARE_CHAR[] = " prnbkq**********PRNBKQ*********";

  for (int i = 0; i < 8; i++)
  {
    std::cout << 8 - i << " "; // row (rank) number 
    for (int j = 0; j < 8; j++)
    {
      square s = get(row_col(7 - i, j)); // so row 1 at bottom

      // Decide on colours
      int bg = 41;
      if ((j & 1) == (i & 1))
        bg = 47;

      int fg = 30;
      if (is_white_piece(s))
        fg = 36;

#ifdef YES_COLOURS
      // Set bold, foreground, background colours
      std::cout << "\E[1m\E[" << fg << "m\E[" << bg << "m"; 
      std::cout << " " << (char)SQUARE_CHAR[s] << " "; 
#else
      const char BLACK_SQ = ':';
      // No colours, so draw black squares with ascii art
      bool sq_is_black = ((i & 1) != (j & 1));
      char c = sq_is_black ? BLACK_SQ : ' '; // colon for black sq
      char d = SQUARE_CHAR[s];
      d = (d == ' ' && sq_is_black ? BLACK_SQ : d); 
      std::cout << c << d << c;
#endif
    }

#ifdef YES_COLOURS
    std::cout << "\E[0m\n"; // reset colours
#else 
    std::cout << "\n";
#endif
  }
  std::cout << "   a  b  c  d  e  f  g  h\n";
}

int board::index(const row_col& rc) const
{
  assert(rc.row >= 0);
  assert(rc.col >= 0);
  assert(rc.row < 8);
  assert(rc.col < 8);

  return rc.row * 8 + rc.col;
}


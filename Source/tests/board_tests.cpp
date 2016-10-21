// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "board.h"

void check_white_piece(square s, piece_type pt)
{
  ASSERT_TRUE(is_white_piece(s));
  ASSERT_FALSE(is_black_piece(s));
  ASSERT_TRUE(get_piece_colour(s) == WHITE_PIECE);
  ASSERT_TRUE(get_piece_type(s) == pt);
}

TEST(board, intial_state_white_pawns)
{
  board b;
  for (int i = 0; i < 7; i++)
  {
    square s = b.get(row_col(1, i));
    check_white_piece(s, PAWN); 
  }
}

TEST(board, initial_state_white_backrow)
{
  board b;
 
  {
    square s = b.get(row_col(0, 0));
    check_white_piece(s, ROOK);
  }

  {
    square s = b.get(row_col(0, 1));
    check_white_piece(s, KNIGHT);
  }

  {
    square s = b.get(row_col(0, 2));
    check_white_piece(s, BISHOP);
  }

  {
    square s = b.get(row_col(0, 3));
    check_white_piece(s, QUEEN);
  }

  {
    square s = b.get(row_col(0, 4));
    check_white_piece(s, KING);
  }

  {
    square s = b.get(row_col(0, 5));
    check_white_piece(s, BISHOP);
  }

  {
    square s = b.get(row_col(0, 6));
    check_white_piece(s, KNIGHT);
  }

  {
    square s = b.get(row_col(0, 7));
    check_white_piece(s, ROOK);
  }
}


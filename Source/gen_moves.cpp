// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <assert.h>
#include "gen_moves.h"

void pawn_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void rook_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void knight_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void bishop_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void queen_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void king_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);

void gen_moves(const board& b, piece_colour pc, move* movelist, int& num_moves)
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      row_col rc(i, j);
      square s = b.get(rc);
      if (pc == get_piece_colour(s))
      {
         piece_type pt = get_piece_type(s);
         switch (pt)
         {
         case NONE:
           assert(0); // only here if square contains one of our pieces
           break;
         case PAWN:
           pawn_moves(pc, rc, b, movelist, num_moves);
           break; 
         case KNIGHT:
           knight_moves(pc, rc, b, movelist, num_moves);
           break;
         case BISHOP:
           bishop_moves(pc, rc, b, movelist, num_moves);
           break;
         case ROOK:
           rook_moves(pc, rc, b, movelist, num_moves);
           break;
         case KING:
           king_moves(pc, rc, b, movelist, num_moves);
           break;
         case QUEEN:
           queen_moves(pc, rc, b, movelist, num_moves);
           break;
         }
      }
    }
  }
}

// For pawn capture move: move is only valid if there is an opponent piece
//  in the destination square.
bool try_opponent_only(
  piece_colour pc, const row_col& pos, const row_col& newpos,
  const board& b, move* movelist, int& num_moves)
{
  if (newpos.is_out_of_bounds())
    return false;

  square s = b.get(newpos);
  if (get_piece_colour(s) == pc)
    return false; // piece on destination square is the same as our colour
  
  if (is_empty(s))
    return false;

  movelist[num_moves] = move(pos, newpos, b);
  num_moves++;
  return true;
}

// For pawn move: new pos is valid only if square is on board and empty.
// Return true if this is the case.
bool try_empty_only(
  piece_colour pc, const row_col& pos, const row_col& newpos,
  const board& b, move* movelist, int& num_moves)
{
  if (newpos.is_out_of_bounds())
    return false;

  square s = b.get(newpos);
  if (get_piece_colour(s) == pc)
    return false; // piece on destination square is the same as our colour
  
  if (!is_empty(s))
    return false;

  movelist[num_moves] = move(pos, newpos, b);
  num_moves++;
  return true;
}

void pawn_moves(piece_colour pc, const row_col& pos, const board& b, move* movelist, int& num_moves)
{
  int fwd = (pc == WHITE_PIECE) ? 1 : -1; // pawn forward direction
  int first = (pc == WHITE_PIECE) ? 1 : 6; // start row for pawns of this colour
 
  if (try_empty_only(pc, pos, pos + row_col(fwd, 0), b, movelist, num_moves) &&
      pos.row == first) // on start row, so can also move 2 squares
    try_empty_only(pc, pos, pos + row_col(2 * fwd, 0), b, movelist, num_moves);

  // Try diagonal capture
  try_opponent_only(pc, pos, pos + row_col(fwd,  1), b, movelist, num_moves);
  try_opponent_only(pc, pos, pos + row_col(fwd, -1), b, movelist, num_moves);
}

// Tries new position to see if it is a valid move. The move is valid if the
//  destination square is on the board, and either empty or containing an 
//  opposing piece. Valid moves are added to the move list.
//
// Returns true if square is on the board and EMPTY. If it has an opposing piece,
//  the move is added to the move list, but we return false. Good for generating
//  moves for rook/bishop/queen.
//
bool try_square(
  piece_colour pc, const row_col& pos, const row_col& newpos,
  const board& b, move* movelist, int& num_moves)
{
  if (newpos.is_out_of_bounds())
    return false;

  square s = b.get(newpos);
  if (get_piece_colour(s) == pc)
    return false; // piece on destination square is the same as our colour

  movelist[num_moves] = move(pos, newpos, b);
  num_moves++;

  return is_empty(s);
}

void rook_moves(piece_colour pc, const row_col& pos, const board& b, move* movelist, int& num_moves)
{
  for (int i = 1; i < 7; i++)
    if (!try_square(pc, pos, pos + row_col( i, 0), b, movelist, num_moves))
      break;

  for (int i = 1; i < 7; i++)
    if (!try_square(pc, pos, pos + row_col(-i, 0), b, movelist, num_moves))
      break;

  for (int i = 1; i < 7; i++)
    if (!try_square(pc, pos, pos + row_col(0, i), b, movelist, num_moves))
      break;

  for (int i = 1; i < 7; i++)
    if (!try_square(pc, pos, pos + row_col(0, -i), b, movelist, num_moves))
      break;
}

void knight_moves(piece_colour pc, const row_col& pos, const board& b, move* movelist, int& num_moves)
{
  try_square(pc, pos, pos + row_col( 2,  1), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col( 2, -1), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col(-2,  1), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col(-2, -1), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col( 1,  2), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col( 1, -2), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col(-1,  2), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col(-1, -2), b, movelist, num_moves);
}

void bishop_moves(piece_colour pc, const row_col& pos, const board& b, move* movelist, int& num_moves)
{
  for (int i = 1; i < 7; i++)
    if (!try_square(pc, pos, pos + row_col(i, i), b, movelist, num_moves))
      break;

  for (int i = 1; i < 7; i++)
    if (!try_square(pc, pos, pos + row_col(-i, i), b, movelist, num_moves))
      break;

  for (int i = 1; i < 7; i++)
    if (!try_square(pc, pos, pos + row_col(-i, -i), b, movelist, num_moves))
      break;

  for (int i = 1; i < 7; i++)
    if (!try_square(pc, pos, pos + row_col(i, -i), b, movelist, num_moves))
      break;
}

void queen_moves(piece_colour pc, const row_col& pos, const board& b, move* movelist, int& num_moves)
{
  bishop_moves(pc, pos, b, movelist, num_moves);
  rook_moves(pc, pos, b, movelist, num_moves);
}

void king_moves(piece_colour pc, const row_col& pos, const board& b, move* movelist, int& num_moves)
{
  try_square(pc, pos, pos + row_col(-1, -1), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col( 0, -1), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col( 1, -1), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col(-1,  0), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col( 1,  0), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col(-1,  1), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col( 0,  1), b, movelist, num_moves);
  try_square(pc, pos, pos + row_col( 1,  1), b, movelist, num_moves);
}


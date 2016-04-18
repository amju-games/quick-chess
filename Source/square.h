#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

// Piece types
enum piece_type
{
  NONE =   0x00,
  PAWN =   0x01,
  ROOK =   0x02,
  KNIGHT = 0x03,
  BISHOP = 0x04,
  KING =   0x05,
  QUEEN =  0x06
};

// Bit positions for square contents 
enum
{
  BLACK = 0x10,
  MOVED = 0x20,
};

// All possible values for a square on the board, including around the edge
enum square
{
  EMPTY =    0x00,
  W_PAWN =   0x01,
  W_ROOK =   0x02,
  W_KNIGHT = 0x03,
  W_BISHOP = 0x04,
  W_KING =   0x05,
  W_QUEEN =  0x06,
  B_PAWN =   0x11,
  B_ROOK =   0x12,
  B_KNIGHT = 0x13,
  B_BISHOP = 0x14,
  B_KING =   0x15,
  B_QUEEN =  0x16,
  BORDER =   0x1f
};

enum piece_colour
{
  WHITE_PIECE,
  BLACK_PIECE,
  NO_PIECE
};

inline piece_colour flip(piece_colour pc) { return (pc == WHITE_PIECE) ? BLACK_PIECE : WHITE_PIECE; }

inline bool is_empty(square s) { return s == EMPTY || s == BORDER; }
inline bool is_white_piece(square s) { return s >= W_PAWN && s <= W_QUEEN; }
inline bool is_black_piece(square s) { return s >= B_PAWN && s <= B_QUEEN; }
inline piece_colour get_piece_colour(square s) { return is_empty(s) ? NO_PIECE : (is_white_piece(s) ? WHITE_PIECE : BLACK_PIECE); }
inline piece_type get_piece_type(square s) { return (piece_type)(s & 0x07); }


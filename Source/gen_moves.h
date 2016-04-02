#pragma once

#include "board.h"
#include "move.h"
#include "row_col.h"
#include "square.h"

// Doing it C-style
void gen_moves(const board& b, piece_colour pc, move* movelist, int& num_moves);

void pawn_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void rook_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void knight_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void bishop_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void queen_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);
void king_moves(piece_colour c, const row_col& pos, const board& b, move* movelist, int& num_moves);


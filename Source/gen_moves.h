#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include "board.h"
#include "move.h"
#include "row_col.h"
#include "square.h"

// Doing it C-style. No classes for the different piece types. 
// This generates a list of moves for the given board position, for the given
//  player colour.
// movelist is an arry big enough to store all possible moves (~110?)
// On return, num_moves is set to the number of valid elements in movelist.
// Not using vector here to avoid memory allocations during search.
void gen_moves(const board& b, piece_colour pc, move* movelist, int& num_moves);

// Check if move m is one of the moves generated for the given board/player
bool is_legal(const board& b, piece_colour pc, const move& m);

// Return true if player pc can take opponent king
bool can_take_opponent_king(const board& b, piece_colour pc); 

// Return true if player pc is check mated
bool mate_test(board& b, piece_colour pc);


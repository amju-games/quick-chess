#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

class evaluator;
class board;

// TODO TEMP TEST
// Should be a move finding class with attribs for depth/breadth, max depth,
//  evaluators, etc etc.
bool find_best_move(int max_depth, evaluator& e, board& b, piece_colour pc, move* m);


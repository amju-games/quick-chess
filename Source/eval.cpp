#include "eval.h"

int eval_material::calc_score(const board& b, piece_colour pc)
{
  // TODO allow these to be tuned?
  int MATERIAL_SCORE[] = { 0, 1, 5, 3, 3, 1000, 9 };

  int total = 0;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      square s = b.get(row_col(i, j));
      if (pc == get_piece_colour(s))
        total += MATERIAL_SCORE[get_piece_type(s)]; // our piece
      else if (!is_empty(s))
        total -= MATERIAL_SCORE[get_piece_type(s)]; // opponent piece
    }
  } 
  return total; 
}


#include <iostream>

#include "board.h"
#include "eval.h"
#include "gen_moves.h"
#include "search.h"

int main()
{
  board b;

  piece_colour pc = WHITE_PIECE;
  for (int k = 0; k < 4; k++)
  {
    b.print();

    move m;
    find_best_move(b, pc, &m);

    // Do move
    b.do_move(m);

    // Switch player
    pc = (pc == WHITE_PIECE) ? BLACK_PIECE : WHITE_PIECE;
  }
}


// TODO Delete this!
//std::cout <<"\xe2\x99\x94"<<std::endl;

/*
  // http://www.cplusplus.com/forum/unices/104540/
  // display the color table.
  std::cout << "B;FG;BG\t";
  for (int i = 40; i < 48; i++)
      std::cout << "  " << i << "m\t";
   std::cout << std::endl;
   for (int fg = 30; fg < 38; fg++)
      for (int h = 0; h < 2; h++)
      {
         std::cout << "\E[0m" << h << ";" << fg << "m";
         for (int bg = 40; bg < 48; bg++)
         {
            std::cout << "\t"
                 << "\E[" << h << "m"
                 << "\E[" << fg << "m"
                 << "\E[" << bg << "m"
                 << "  RgB  ";
         }
         std::cout << "\E[0m" << std::endl;
         std::cout << std::endl;
      }

   // Reset the console to no colors.
   std::cout << "\E[0m" << std::endl;

// Colour printing example, from http://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
// ..maybe print board in colour.

#define Color_Red "\33[0:31m\\]" // Color Start
#define Color_end "\33[0m\\]" // To flush out prev settings

  printf("\E[1m\E[37m\E[40m New test \E[0m \n");

  printf("\033[22;34mHello, purple text world!\033[0m\n");
  printf("\x1b[41mHello, red bg world!\x1b[0m\n");
  printf("\033[22;34\x1b[41mHello, red bg world!\x1b[0m\033[0m\n");
//  return 0;
*/


/*
    // Test move gen
    move movelist[100]; // watch out!
    int n = 0;
    //knight_moves(WHITE_PIECE, row_col(0, 1), b, movelist, n);
    gen_moves(b, WHITE_PIECE, movelist, n);
    std::cout << n << " moves generated!\n";
    for (int i = 0; i < n; i++)
    {
      movelist[i].print(b);
    }  

    // Test board evaluation
    int score = eval_material().calc_score(b, WHITE_PIECE);
    std::cout << "Score for this pos for white is: " << score << "\n";
*/


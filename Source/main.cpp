// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include "board.h"
#include "eval.h"
#include "gen_moves.h"
#include "search.h"

void help()
{
  std::cout << "t\tTake back last move\n[enter]\tI'll make the next move\n";
}

void player_move(int& k, board& b, piece_colour& pc, const std::string& move_str)
{
  int r1 = move_str[1] - '1';
  int c1 = move_str[0] - 'a';
  int r2 = move_str[3] - '1';
  int c2 = move_str[2] - 'a';

  move m(row_col(r1, c1), row_col(r2, c2), b);

  // Check legal move
  if (!is_legal(b, pc, m))
  {
    std::cout << "I don't think that's a legal move here!\n";
    return;
  }
  
  b.do_move(m);
  std::cout << k / 2 + 1 << ". " << m << "\n";
  b.print();
      
  k++;
  // Switch player
  pc = (pc == WHITE_PIECE) ? BLACK_PIECE : WHITE_PIECE;
}

void play(int k, evaluator& e, board& b, piece_colour pc)
{
  move m;
  find_best_move(e, b, pc, &m);
  b.do_move(m);
  std::cout << k / 2 + 1 << ". " << m << "\n";
  b.print();
}

int main()
{
  board b;
  b.print();

  evaluator e;
  e.add(new eval_material);
  e.add(new eval_control_centre);

  piece_colour pc = WHITE_PIECE;
  int k = 0;
  while (true)
  {
    std::cout << (pc == WHITE_PIECE ? "White" : "Black") << " to play.\n";
    std::cout << "Enter a move like this 'e2e4', or h for help...\n";
    std::string command;
    std::getline(std::cin, command);

    if (command.empty())
    {
      play(k, e, b, pc);
      k++;
      // Switch player
      pc = (pc == WHITE_PIECE) ? BLACK_PIECE : WHITE_PIECE;
    }
    else if (command.size() == 4)
    {
      player_move(k, b, pc, command);
    }
    else if (command == "h")
    {
      help();
    }
    else if (command == "t")
    {
      if (k > 0)
      {
        b.undo_move();
        k--;
        ////std::cout << k / 2 + 1 << ". " << m << "\n";
        b.print();
        // Flip player
        pc = (pc == WHITE_PIECE) ? BLACK_PIECE : WHITE_PIECE;
      }
      else
      {
        std::cout << "Can't take back!\n";
      }
    }
  }
  return 0;
}


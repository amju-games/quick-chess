// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <string>
#include "square.h"

class board;
class evaluator;

// This class wraps the game and lets user enter commands.
class game
{
public:
  void run();

private:
  void player_move(int& k, board& b, piece_colour& pc, const std::string& move_str);
  void play(int& k, evaluator& e, board& b, piece_colour& pc);

};


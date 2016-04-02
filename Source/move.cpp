#include <iostream>
#include "board.h"
#include "move.h"

void move::print(const board& b)
{
  square f = b.get(from);
  square t = b.get(to);

  if (is_empty(t))
    std::cout << from << " - " << to << "\n";
  else
    std::cout << from << " x " << to << "\n";
}


// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

// To build on Mac:
// In Source/
//  clang++ *.cpp main/main.cpp -I. -std=c++11
//

// On windows command prompt (with MSVC installed), something like:
//  cl *.cpp -o qc.exe -EHsc -DWIN32

#include "game.h"

int main()
{
  game g;
  g.run(); 
}


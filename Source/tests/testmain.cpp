// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

// Unit tests for quick chess 
// To build on Mac:
// First build gtest.a in googletest (only needs doing once):
//   cd tests/googletest/make
//   make gtest.a
// Then back in Source/tests
//   clang++ *.cpp ../*.cpp -I .. -I googletest/include  -std=c++11  googletest/make/gtest.a

#include <gtest/gtest.h>

int main(int argc, char * argv[])
{
  //setup tests
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}



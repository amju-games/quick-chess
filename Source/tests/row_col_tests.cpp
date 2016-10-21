// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>
#include "row_col.h"

TEST(row_col, row_col_bounds)
{
  {
    row_col rc;
    ASSERT_FALSE(rc.is_out_of_bounds());
  }

  {
    row_col rc(7, 7);
    ASSERT_FALSE(rc.is_out_of_bounds());
  }

  {
    row_col rc(8, 0);
    ASSERT_TRUE(rc.is_out_of_bounds());
  }

  {
    row_col rc(0, 8);
    ASSERT_TRUE(rc.is_out_of_bounds());
  }

}


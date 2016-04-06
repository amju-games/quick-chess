#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <ostream>

struct row_col
{
  int row, col;

  row_col(int r = 0, int c = 0) : row(r), col(c) {}
  bool is_out_of_bounds() const { return row > 7 || row < 0 || col > 7 || col < 0; }
};

inline bool operator==(const row_col& rc1, const row_col& rc2)
{
  return rc1.row == rc2.row && rc1.col == rc2.col;
}

inline std::ostream& operator<<(std::ostream& os, const row_col& rc)
{
  return os << char(rc.col + 'a') << rc.row + 1;
}

inline row_col operator+(const row_col& rc1, const row_col& rc2)
{
  return row_col(rc1.row + rc2.row, rc1.col + rc2.col);
}


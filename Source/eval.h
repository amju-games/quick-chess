#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <vector>
#include "board.h"

class eval
{
public:
  eval() : weight(1) {}
  virtual ~eval() {}
  virtual int calc_score(const board& b, piece_colour pc) = 0;

protected:
  int weight;
};

class evaluator
{
public:
  evaluator();
  virtual int calc_score(const board& b, piece_colour pc);

private:
  std::vector<eval*> m_evals;
};

class eval_material : public eval
{
public:
  virtual int calc_score(const board& b, piece_colour pc) override;
};

class eval_control_centre : public evaluator
{
public:
  virtual int calc_score(const board& b, piece_colour pc) override;
};

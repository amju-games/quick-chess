#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <vector>
#include "board.h"

// Base class for position evalutors
class eval
{
public:
  eval() : m_weight(1) {}
  virtual ~eval() {}
  virtual int calc_score(const board& b, piece_colour pc) const = 0;
  int get_weight() const { return m_weight; }

protected:
  int m_weight;
};

// Board evaluator: total score is the weighted sum of individual position
//  evaluators, derived from eval.
class evaluator
{
public:
  int calc_score(const board& b, piece_colour pc) const;
  void add(eval* e);

private:
  std::vector<eval*> m_evals;
};

// Evaluates a board for material. This is the most important consideration.
class eval_material : public eval
{
public:
  eval_material();
  virtual int calc_score(const board& b, piece_colour pc) const override;
};

// Evaluate control of the centre of the board.
class eval_control_centre : public eval
{
public:
  virtual int calc_score(const board& b, piece_colour pc) const override;
};


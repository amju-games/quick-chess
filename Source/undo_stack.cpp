// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include "board.h"
#include "undo_stack.h"

void undo_stack::clear()
{
  while(!m_undo_stack.empty())
  {
    m_undo_stack.pop();
  }
}

// Push undo info for one move onto the stack
void undo_stack::push(const undo& u) 
{ 
  m_undo_stack.push(u);
}
 
// Do the undo info at the top of the stack
void undo_stack::do_top(board& b) const 
{ 
  m_undo_stack.top().do_it(b);
}

// Pop element off the stack
void undo_stack::pop() 
{ 
  m_undo_stack.pop();
}

void undo_sq::do_it(board& b) const
{ 
  b.set(m_pos, m_sq); 
}

std::ostream& operator<<(std::ostream& os, const undo_sq& u)
{
  if (u.m_pos.row == -1)
    return os << "(nothing)";

  return os << u.m_pos << " -> " << (int)u.m_sq;
}

void undo::do_it(board& b) const
{
  for (int i = 0; i < 4; i++)
  {
    if (m_undo_sqs[i].is_valid())
      m_undo_sqs[i].do_it(b);
  }
}

std::ostream& operator<<(std::ostream& os, const undo& u)
{
  for (int i = 0; i < 4; i++)
  {
    os << u.m_undo_sqs[i] << (i < 3 ? ", " : ""); 
  }
  return os;
}


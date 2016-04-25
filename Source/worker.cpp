// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

#include <iostream>
#include "worker.h"

static void* thread_func(worker* w)
{
  std::cout << "Started thread func!\n";

  w->work();
  return nullptr;
}

worker::worker() : m_stopped(false)
{
}

void worker::start()
{
  m_thread = std::thread(thread_func, this);
//  m_thread.detach(); // ?
}

void worker::stop()
{
  // The idea is that subclasses periodically test this variable in
  //  their work() function.
  // This doesn't need to be locked, because it's just set once
  //  and then stays set until this object is destroyed.
  m_stopped = true;
}


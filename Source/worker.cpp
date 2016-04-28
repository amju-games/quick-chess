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
}

void worker::stop()
{
  // The idea is that subclasses periodically test this variable in
  //  their work() function.
  // This doesn't need to be locked, because it's just set once
  //  and then stays set until this object is destroyed.
  m_stopped = true;

  // c++11 threads will TERMINATE the process in dtor if joinable!
  // See Effective Modern C++ Item 37

  // Wait for thread to finish. It may have never been started, in which case
  //  we don't want to join().
  if (m_thread.joinable())
  {
    m_thread.join();
  }
}


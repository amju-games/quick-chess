#pragma once

// -----------------------------------------------------------------------------
// Quick chess - Jason Colman 2016 - just a fun project to keep my hand in.
// -----------------------------------------------------------------------------

// Worker thread type using c++11 threads. This could be used to search in a 
//  separate thread to the UI/main thread.

#include <thread>

// Base class for worker threads.
// Override work() to perform task. Check m_stopped periodically in that function.
class worker
{
public:
  worker();
  virtual ~worker() {}
  virtual void work() = 0;
  virtual void finished() {}
  void start();
  void stop();

protected:
  std::thread m_thread;
  bool m_stopped;
};


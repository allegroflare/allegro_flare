

#include <AllegroFlare/Timer.hpp>

#include <sstream>


Timer::Timer()
   : start_time()
   , end_time()
   , elappsed_time(0.0)
   , running(false)
{}


Timer::~Timer()
{
}


void Timer::start()
{
   if (running) return;

   elappsed_time += end_time - start_time;
   start_time = std::chrono::high_resolution_clock::now();
   running = true;
}


void Timer::stop()
{
   if (!running) return;

   end_time = std::chrono::high_resolution_clock::now();
   elappsed_time += end_time - start_time;
   running = false;
}


int Timer::get_elappsed_time_msec()
{
   std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
   return std::chrono::duration_cast<std::chrono::milliseconds>(elappsed_time + (current_time - start_time)).count();
}



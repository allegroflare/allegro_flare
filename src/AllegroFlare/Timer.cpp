

#include <AllegroFlare/Timer.hpp>

#include <sstream>


namespace AllegroFlare
{
   Timer::Timer()
      : start_time()
      , end_time()
      , elapsed_time(0.0)
      , running(false)
      , stopped(true)
   {}


   Timer::~Timer()
   {
   }


   bool Timer::is_running()
   {
      return running;
   }


   void Timer::reset()
   {
      elapsed_time = std::chrono::duration<double, std::milli>{};
      start_time = std::chrono::high_resolution_clock::time_point{};
      end_time = std::chrono::high_resolution_clock::time_point{};
      running = false;
   }


   void Timer::start()
   {
      if (running) return;
      if (stopped)
      {
         reset();
         stopped = false;
      }

      elapsed_time += end_time - start_time;
      start_time = std::chrono::high_resolution_clock::now();
      running = true;
   }


   void Timer::pause()
   {
      if (!running) return;

      end_time = std::chrono::high_resolution_clock::now();
      elapsed_time += end_time - start_time;
      running = false;
   }


   void Timer::stop()
   {
      if (stopped) return;
      pause();
      stopped = true;
   }


   int Timer::get_elapsed_time_milliseconds()
   {
      if (!running)
      {
         return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::duration<double, std::milli>(elapsed_time)
            ).count();
      }
      else
      {
         std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
         return std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time + (current_time - start_time)).count();
      }
   }

   int Timer::get_elapsed_time_microseconds()
   {
      if (!running)
      {
         return std::chrono::duration_cast<std::chrono::microseconds>(
               std::chrono::duration<double, std::micro>(elapsed_time)
            ).count();
      }
      else
      {
         std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
         return std::chrono::duration_cast<std::chrono::microseconds>(
               elapsed_time + (current_time - start_time)
            ).count();
      }
   }

   int Timer::get_elapsed_time_nanoseconds()
   {
      if (!running)
      {
         return std::chrono::duration_cast<std::chrono::nanoseconds>(
               std::chrono::duration<double, std::nano>(elapsed_time)
            ).count();
      }
      else
      {
         std::chrono::high_resolution_clock::time_point current_time = std::chrono::high_resolution_clock::now();
         return std::chrono::duration_cast<std::chrono::nanoseconds>(
               elapsed_time + (current_time - start_time)
            ).count();
      }
   }
}



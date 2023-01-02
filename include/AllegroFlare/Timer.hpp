#pragma once


#include <chrono>
#include <string>
#include <vector>


namespace AllegroFlare
{
   class Timer
   {
   private:
      std::chrono::high_resolution_clock::time_point start_time;
      std::chrono::high_resolution_clock::time_point end_time;
      std::chrono::duration<double, std::milli> elapsed_time;
      bool running;
      bool stopped;

   public:
      Timer();
      ~Timer();

      bool is_running();

      void reset();
      void start();
      void pause();
      void stop();

      int get_elapsed_time_milliseconds();
      int get_elapsed_time_microseconds();
      int get_elapsed_time_nanoseconds();
   };
}



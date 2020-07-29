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

   public:
      Timer();
      ~Timer();

      bool is_running();

      void start();
      void pause();

      int get_elapsed_time_msec();
      int get_elapsed_time_nanoseconds();
   };
}



#pragma once


#include <chrono>
#include <string>


class Timer
{
private:
   std::chrono::high_resolution_clock::time_point start_time;
   std::chrono::high_resolution_clock::time_point end_time;
   std::chrono::duration<double, std::milli> elappsed_time;
   bool running;

public:
   Timer();
   ~Timer();

   void start();
   void stop();

   int get_elappsed_time_msec();
};



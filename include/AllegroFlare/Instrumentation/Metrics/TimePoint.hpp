#pragma once


#include <chrono>
#include <vector>


namespace AllegroFlare
{
   namespace Instrumentation
   {
      namespace Metrics
      {
         class TimePoint
         {
         private:
            std::vector<std::chrono::steady_clock::time_point> metrics;
            int size;
            int head;
            bool initialized;

         protected:


         public:
            TimePoint();
            ~TimePoint();

            int get_size() const;
            int get_head() const;
            std::vector<std::chrono::steady_clock::time_point> &get_metrics_ref();
            void set_size(int size=64*4);
            void initialize();
            void capture(std::chrono::steady_clock::time_point metric=std::chrono::steady_clock::time_point());
            int head_delta(int delta=0);
            std::vector<std::chrono::steady_clock::time_point> get_last_n_metrics(int count=64);
         };
      }
   }
}




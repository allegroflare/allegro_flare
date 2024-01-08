#pragma once


#include <chrono>
#include <vector>


namespace AllegroFlare
{
   namespace Instrumentation
   {
      class DurationMeasurer
      {
      private:
         std::vector<double> metrics;
         int size;
         int head;
         std::chrono::steady_clock::time_point initial_time_measurement;
         bool is_measuring;
         bool initialized;

      protected:


      public:
         DurationMeasurer();
         ~DurationMeasurer();

         int get_size() const;
         int get_head() const;
         std::vector<double> &get_metrics_ref();
         void set_size(int size=64*4);
         void initialize();
         void start_capture();
         void end_capture();
         int head_delta(int delta=0);
         double average_of_last_n_metrics(int count=64);
         std::vector<double> get_last_n_metrics(int count=64);
         double get_last_metric();
      };
   }
}




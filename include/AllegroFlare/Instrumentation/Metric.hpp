#pragma once


#include <vector>


namespace AllegroFlare
{
   namespace Instrumentation
   {
      class Metric
      {
      private:
         std::vector<double> metrics;
         int size;
         int head;
         bool initialized;

      protected:


      public:
         Metric();
         ~Metric();

         int get_size() const;
         void set_size(int size=64*4);
         void initialize();
         void capture(double metric=0.0);
         int head_delta(int delta=0);
         std::vector<double> get_last_n_metrics(int count=64);
      };
   }
}




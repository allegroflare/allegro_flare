#pragma once


#include <vector>


namespace AllegroFlare
{
   namespace Instrumentation
   {
      namespace Metrics
      {
         class Double
         {
         private:
            std::vector<double> metrics;
            int size;
            int head;
            bool initialized;

         protected:


         public:
            Double();
            ~Double();

            int get_size() const;
            int get_head() const;
            std::vector<double> &get_metrics_ref();
            void set_size(int size=64*4);
            void initialize();
            void capture(double metric=0.0);
            int head_delta(int delta=0);
            double average_of_last_n_metrics(int count=64);
            std::vector<double> get_last_n_metrics(int count=64);
         };
      }
   }
}




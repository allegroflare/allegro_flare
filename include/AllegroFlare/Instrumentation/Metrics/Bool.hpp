#pragma once


#include <vector>


namespace AllegroFlare
{
   namespace Instrumentation
   {
      namespace Metrics
      {
         class Bool
         {
         private:
            std::vector<bool> metrics;
            int size;
            int head;
            bool initialized;

         protected:


         public:
            Bool();
            ~Bool();

            int get_size() const;
            int get_head() const;
            std::vector<bool> &get_metrics_ref();
            void set_size(int size=64*4);
            void initialize();
            void capture(bool metric=false);
            int head_delta(int delta=0);
            std::vector<bool> get_last_n_metrics(int count=64);
         };
      }
   }
}




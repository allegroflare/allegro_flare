#pragma once


#include <utility>
#include <vector>


namespace AllegroFlare
{
   class FlipSync
   {
   private:
      bool currently_capturing_flip_sync;
      std::vector<std::pair<double, double>> flip_metrics;
      int head;
      bool initialized;

   protected:


   public:
      FlipSync();
      ~FlipSync();

      void initialize();
      void start_flip_capture();
      void end_flip_capture();
      int head_delta(int delta=0);
      double get_last_capture_duration();
   };
}




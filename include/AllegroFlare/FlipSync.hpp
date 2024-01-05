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
      int size;
      int head;
      bool initialized;

   protected:


   public:
      FlipSync();
      ~FlipSync();

      int get_size() const;
      void set_size(int size=64*4);
      void initialize();
      void start_flip_capture();
      void end_flip_capture();
      int head_delta(int delta=0);
      std::vector<double> get_last_n_capture_durations(int count=64);
   };
}




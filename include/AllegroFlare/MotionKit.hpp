#pragma once


#include <utility>


namespace AllegroFlare
{
   class MotionKit
   {
   private:

   protected:


   public:
      MotionKit();
      ~MotionKit();

      static float normalize_age(float start_time=0.0f, float end_time=0.0f, float time_now=0.0f);
      static bool strobe(float start_time=0.0f, float time_now=0.0f, float strobes_per_second=10.0f);
      static std::pair<bool, bool> counted_strobe(float start_time=0.0f, float time_now=0.0f, float strobes_per_second=10.0f, int num_strobes=2);
      static bool smooth_strobe(float start_time=0.0f, float time_now=0.0f, float strobes_per_second=10.0f);
      static float age(float start_time=0.0f, float end_time=0.0f);
      static float interpolate(float start_value=0.0f, float end_value=0.0f, float normalized_float=0.0f);
   };
}




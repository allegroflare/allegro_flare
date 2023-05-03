#pragma once




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
      static bool strobe(float start_time=0.0f, float time_now=0.0f, float strobe_frequency=0.2f);
      static float age(float start_time=0.0f, float end_time=0.0f);
      static float interpolate(float start_value=0.0f, float end_value=0.0f, float normalized_float=0.0f);
   };
}




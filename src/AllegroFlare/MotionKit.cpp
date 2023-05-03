

#include <AllegroFlare/MotionKit.hpp>

#include <cmath>


namespace AllegroFlare
{


MotionKit::MotionKit()
{
}


MotionKit::~MotionKit()
{
}


float MotionKit::normalize_age(float start_time, float end_time, float time_now)
{
   float length = (end_time - start_time);
   float time_now_in_range = time_now - start_time;
   if (length == 0.0f) return 0.0f;
   if (time_now_in_range >= length) return 1.0f;
   return time_now_in_range / length;
}

bool MotionKit::strobe(float start_time, float time_now, float strobes_per_second)
{
   float strobe_frequency = 1.0 / strobes_per_second;
   float age = (time_now - start_time);
   return (fmod(age, strobe_frequency) < (strobe_frequency * 0.5));
}

float MotionKit::age(float start_time, float end_time)
{
   return (end_time - start_time);
}

float MotionKit::interpolate(float start_value, float end_value, float normalized_float)
{
   return start_value + (normalized_float * (end_value - start_value));
}


} // namespace AllegroFlare





#include <AllegroFlare/MotionKit.hpp>




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
   return time_now_in_range / length;
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



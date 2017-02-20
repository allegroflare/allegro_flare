



#include <allegro_flare/timeline.h>

#include <algorithm>
#include <sstream>
#include <allegro_flare/interpolators.h>




Timeline::Keyframe::Keyframe(float time, float val, float (*interpolator_func)(float))
   : time(time)
   , val(val)
   , interpolator_func(interpolator_func)
{}




static bool keyframe_sort_func(const Timeline::Keyframe *k1, const Timeline::Keyframe *k2)
{
   return k1->time < k2->time;
}




Timeline::Track::Track(float start_val, std::string label)
   : label(label)
   , start_val(start_val)
{}




void Timeline::Track::add(Timeline::Keyframe *k)
{
   keyframe.push_back(k);
   std::sort(keyframe.begin(), keyframe.end(), keyframe_sort_func);
}




void Timeline::Track::add(float time, float val, float (*interpolator_func)(float)) // shorthand
{
   keyframe.push_back(new Timeline::Keyframe(time, val, interpolator_func));
   std::sort(keyframe.begin(), keyframe.end(), keyframe_sort_func);
}




float Timeline::Track::get_displacement(float t1, float t2)
{
   return get(t2) - get(t1);
}




float Timeline::Track::get(float time)
{
   Timeline::Keyframe *right=NULL;
   float left_time = 0;
   float *left_val = &start_val;

   if (keyframe.empty() || time < 0) return start_val;
   else if (time >= keyframe.back()->time) return keyframe.back()->val;
   else if (time <= keyframe.front()->time)
   {
      right = keyframe.front();
   }
   else
   {
      // would probably be faster in a binary search?
      for (unsigned i=1; i<keyframe.size(); i++)
         if (keyframe[i-1]->time < time && time < keyframe[i]->time)
         {
            left_val = &keyframe[i-1]->val;
            left_time = keyframe[i-1]->time;
            right = keyframe[i];
            break;
         }
   }

   float time_width = right->time - left_time;
   float time_in = time - left_time;
   float time_normal = time_in / time_width;

   float val_delta = right->val - *left_val;

   return right->interpolator_func(time_normal) * val_delta + *left_val;
}




std::string Timeline::Track::get_str()
{
   std::ostringstream ss;
   ss << "timeline: " << label << std::endl;
   for (unsigned i=0; i<keyframe.size(); i++)
      ss << "  frame " << i << ": (" << keyframe[i]->time << ", " << keyframe[i]->val << ", " << keyframe[i]->interpolator_func << ")" << std::endl;

   return ss.str();
}





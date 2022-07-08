

#include <AllegroFlare/Timeline/Track.hpp>
#include <sstream>
#include <algorithm>




static bool keyframe_sort_func(const AllegroFlare::Timeline::Keyframe *k1, const AllegroFlare::Timeline::Keyframe *k2)
{
   return k1->time < k2->time;
}


namespace AllegroFlare
{
namespace Timeline
{



   Track::Track(float start_val, std::string label)
      : label(label)
      , start_val(start_val)
   {}




   void Track::add(AllegroFlare::Timeline::Keyframe *k)
   {
      keyframe.push_back(k);
      std::sort(keyframe.begin(), keyframe.end(), keyframe_sort_func);
   }




   void Track::add(float time, float val, float (*interpolator_func)(float))
   {
      keyframe.push_back(new AllegroFlare::Timeline::Keyframe(time, val, interpolator_func));
      std::sort(keyframe.begin(), keyframe.end(), keyframe_sort_func);
   }




   float Track::get_displacement(float t1, float t2)
   {
      return get(t2) - get(t1);
   }




   float Track::get(float time)
   {
      AllegroFlare::Timeline::Keyframe *right=NULL;
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




   std::string Track::get_str()
   {
      std::ostringstream ss;
      ss << "timeline: " << label << std::endl;
      for (unsigned i=0; i<keyframe.size(); i++)
         ss << "  frame " << i << ": (" << keyframe[i]->time << ", " << keyframe[i]->val << ", " << keyframe[i]->interpolator_func << ")" << std::endl;

      return ss.str();
   }



} // namespace Timeline
} // namespace AllegroFlare



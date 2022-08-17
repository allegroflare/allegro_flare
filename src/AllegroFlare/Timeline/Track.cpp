

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



   Track::Track(std::string label, float start_val, std::vector<AllegroFlare::Timeline::Keyframe *> keyframes)
      : label(label)
      , start_val(start_val)
      , keyframes(keyframes)
   {}



   std::vector<AllegroFlare::Timeline::Keyframe *> Track::get_keyframes()
   {
      return keyframes;
   }



   void Track::set_keyframes(std::vector<AllegroFlare::Timeline::Keyframe *> keyframes)
   {
      this->keyframes = keyframes;
   }



   void Track::add_keyframe(AllegroFlare::Timeline::Keyframe *k)
   {
      keyframes.push_back(k);
      std::sort(keyframes.begin(), keyframes.end(), keyframe_sort_func);
   }




   void Track::add_keyframe(float time, float val, float (*interpolator_func)(float))
   {
      keyframes.push_back(new AllegroFlare::Timeline::Keyframe(time, val, interpolator_func));
      std::sort(keyframes.begin(), keyframes.end(), keyframe_sort_func);
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

      if (keyframes.empty() || time < 0) return start_val;
      else if (time >= keyframes.back()->time) return keyframes.back()->val;
      else if (time <= keyframes.front()->time)
      {
         right = keyframes.front();
      }
      else
      {
         // would probably be faster in a binary search?
         for (unsigned i=1; i<keyframes.size(); i++)
            if (keyframes[i-1]->time < time && time < keyframes[i]->time)
            {
               left_val = &keyframes[i-1]->val;
               left_time = keyframes[i-1]->time;
               right = keyframes[i];
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
      for (unsigned i=0; i<keyframes.size(); i++)
         ss << "  frame " << i << ": (" << keyframes[i]->time << ", " << keyframes[i]->val << ", " << keyframes[i]->interpolator_func << ")" << std::endl;

      return ss.str();
   }



} // namespace Timeline
} // namespace AllegroFlare





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
   void Track::sort_keyframes()
   {
      std::sort(keyframes.begin(), keyframes.end(), keyframe_sort_func);
   }



   Track::Track(std::string label, float start_val, std::vector<AllegroFlare::Timeline::Keyframe *> keyframes)
      : label(label)
      , start_val(start_val)
      , keyframes(keyframes)
   {
      sort_keyframes();
   }



   std::vector<AllegroFlare::Timeline::Keyframe *> Track::get_keyframes()
   {
      return keyframes;
   }



   void Track::set_keyframes(std::vector<AllegroFlare::Timeline::Keyframe *> keyframes)
   {
      this->keyframes = keyframes;
      sort_keyframes();
   }



   void Track::add_keyframe(AllegroFlare::Timeline::Keyframe *k)
   {
      keyframes.push_back(k);
      sort_keyframes();
   }




   void Track::add_keyframe(float time, float val, float (*interpolator_func)(float))
   {
      keyframes.push_back(new AllegroFlare::Timeline::Keyframe(time, val, interpolator_func));
      sort_keyframes();
   }




   float Track::get_displacement(float t1, float t2)
   {
      return get(t2) - get(t1);
   }




   float Track::get(float time)
   {
      AllegroFlare::Timeline::Keyframe *global_right_keyframe = nullptr;

      float left_time = 0;
      float left_val = 0; //&start_val;

      if (keyframes.empty()) return start_val;
      if (keyframes.size() == 1) return keyframes[0]->val;

      if (time <= keyframes.front()->time) return keyframes.front()->val;
      if (time >= keyframes.back()->time) return keyframes.back()->val;

      

      for (unsigned i=1; i<keyframes.size(); i++)
      {
         AllegroFlare::Timeline::Keyframe &left_keyframe = *keyframes[i-1];
         AllegroFlare::Timeline::Keyframe &right_keyframe = *keyframes[i];

         // time is exactly on one of the keyframe times
         if (right_keyframe.time == time) return right_keyframe.val;
         if (left_keyframe.time == time) return left_keyframe.val;

         // time is between keyframes
         if (left_keyframe.time < time && right_keyframe.time > time)
         {
            left_val = left_keyframe.val;
            left_time = left_keyframe.time;
            global_right_keyframe = &right_keyframe;
            break;
         }
      }

      float time_width = global_right_keyframe->time - left_time;

      float time_in = time - left_time;
      float time_normal = time_in / time_width;
      float val_delta = global_right_keyframe->val - left_val;

      return global_right_keyframe->interpolator_func(time_normal) * val_delta + left_val;
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



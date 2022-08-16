#pragma once


#include <vector>
#include <string>
#include <AllegroFlare/Timeline/Keyframe.hpp>


namespace AllegroFlare
{
   namespace Timeline
   {
      class Track
      {
      public: // TODO: make private
         std::string label;
         std::vector<AllegroFlare::Timeline::Keyframe *> keyframe;
         float start_val;

      public:
         Track(float start_val=0, std::string label="");

         void add_keyframe(AllegroFlare::Timeline::Keyframe *k);
         void add_keyframe(float time, float val, float (*interpolator_func)(float)=nullptr);
         float get_displacement(float t1, float t2);
         float get(float time);
         std::string get_str();
      };
   }
}



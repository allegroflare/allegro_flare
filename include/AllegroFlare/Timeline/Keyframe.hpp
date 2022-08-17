#pragma once


#include <string>
#include <AllegroFlare/Interpolators.hpp>


namespace AllegroFlare
{
   namespace Timeline
   {
      class Keyframe
      {
      public:
         float time;
         float val;
         float (*interpolator_func)(float);

         Keyframe(float time=0, float val=0, float (*interpolator_func)(float)=interpolator::linear);
         ~Keyframe();
      };
   }
}




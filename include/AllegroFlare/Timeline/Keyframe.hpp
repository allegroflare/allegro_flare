#pragma once


#include <string>


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

         Keyframe(float time=0, float val=0, float (*interpolator_func)(float)=nullptr); // TODO: default interp to linear
         ~Keyframe();
      };
   }
}




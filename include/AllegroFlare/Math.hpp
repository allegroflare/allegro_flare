#pragma once


#include <string>


namespace AllegroFlare
{
   class Math
   {
   private:

   public:
      Math();
      ~Math();

      static const float PI;
      static const float TAU;
      static const float FULL_ROTATION;

      // Converts a value from degrees to radians.
      static float degrees_to_radians(float deg);

      // Converts a value from radians to degrees.
      static float radians_to_degrees(float rad);
   };
}




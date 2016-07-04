#ifndef __AF_INTERPOLATORS_HEADER
#define __AF_INTERPOLATORS_HEADER




#include <string>




namespace interpolator
{
   typedef float (*interpolator_func_t)(float t);

   float linear(float value);

   float quadraticIn(float t);
   float quadraticOut(float t);
   float quadraticInOut(float t);
   float quadraticOutIn(float t);

   float cubicIn(float t);
   float cubicOut(float t);
   float cubicInOut(float t);

   float quarticIn(float t);
   float quarticOut(float t);
   float quarticInOut(float t);

   float quinticIn(float t);
   float quinticOut(float t);
   float quinticInOut(float t);

   float sineIn(float t);
   float sineOut(float t);
   float sineInOut(float t);

   float exponentialIn(float t);
   float exponentialOut(float t);
   float exponentialInOut(float t);

   float circularIn(float t);
   float circularOut(float t);
   float circularInOut(float t);

   float elasticIn(float t);

   float backIn(float t);
   float backOut(float t);
   float backInOut(float t);

   float bounceOut(float t);
   float bounceIn(float t);
   float bounceInOut(float t);

   float fastIn(float t);
   float fastOut(float t);
   float fastInOut(float t);
   float slowIn(float t);
   float slowOut(float t);
   float slowInOut(float t);

   float doubleFastIn(float t);
   float doubleFastOut(float t);
   float doubleSlowIn(float t);
   float doubleSlowOut(float t);
   float doubleSlowInOut(float t);

   float trippleFastIn(float t);
   float trippleFastOut(float t);
   float trippleSlowIn(float t);
   float trippleSlowOut(float t);
   float trippleSlowInOut(float t);

   float quadrupleFastIn(float t);
   float quadrupleFastOut(float t);
   float quadrupleSlowIn(float t);
   float quadrupleSlowOut(float t);
   float quadrupleSlowInOut(float t);

   float bloompIn(float value); // TODO: fix this broken function

   interpolator_func_t get_interpolator_by_name(std::string name);
   std::string get_interpolator_func_name_as_str(interpolator_func_t func); // TODO: complete this function
}




#endif

#ifndef __AF_INTERPOLATORS_HEADER
#define __AF_INTERPOLATORS_HEADER




#include <string>




namespace interpolator
{
   typedef float (*interpolator_func_t)(float t);

   float linear(float value);

   float quadratic_in(float t);
   float quadratic_out(float t);
   float quadratic_in_out(float t);
   float quadratic_out_in(float t);

   float cubic_in(float t);
   float cubic_out(float t);
   float cubic_in_out(float t);

   float quartic_in(float t);
   float quartic_out(float t);
   float quartic_in_out(float t);

   float quintic_in(float t);
   float quintic_out(float t);
   float quintic_in_out(float t);

   float sine_in(float t);
   float sine_out(float t);
   float sine_in_out(float t);

   float exponential_in(float t);
   float exponential_out(float t);
   float exponential_in_out(float t);

   float circular_in(float t);
   float circular_out(float t);
   float circular_in_out(float t);

   float elastic_in(float t);

   float back_in(float t);
   float back_out(float t);
   float back_in_out(float t);

   float bounce_out(float t);
   float bounce_in(float t);
   float bounce_in_out(float t);

   float fast_in(float t);
   float fast_out(float t);
   float fast_in_out(float t);
   float slow_in(float t);
   float slow_out(float t);
   float slow_in_out(float t);

   float double_fast_in(float t);
   float double_fast_out(float t);
   float double_slow_in(float t);
   float double_slow_out(float t);
   float double_slow_in_out(float t);

   float tripple_fast_in(float t);
   float tripple_fast_out(float t);
   float tripple_slow_in(float t);
   float tripple_slow_out(float t);
   float tripple_slow_in_out(float t);

   float quadruple_fast_in(float t);
   float quadruple_fast_out(float t);
   float quadruple_slow_in(float t);
   float quadruple_slow_out(float t);
   float quadruple_slow_in_out(float t);

   float bloomp_in(float value); // TODO: fix this broken function

   interpolator_func_t get_interpolator_by_name(std::string name);
   std::string get_interpolator_func_name_as_str(interpolator_func_t func); // TODO: complete this function
}




#endif



#include <AllegroFlare/Interpolators.hpp>


#include <math.h>
#include <string>




namespace AllegroFlare
{
#define INTERP_PI 3.1415926536f




   bool ___in_range(const float &num, const float &min, const float &max)
   {
      if (num < min) return false;
      if (num > max) return false;
      return true;
   }




   float interpolator::linear(float value)
   {
      return value;
   }




   ///////////// Quadratic Easing: t^2 ///////////////////




   float interpolator::quadratic_in(float t)
   {
      return t*t;
   }




   float interpolator::quadratic_out(float t)
   {
      return -t*(t-2);
   }




   float interpolator::quadratic_in_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      if ((t/=d/2) < 1) return c/2*t*t + b;
      --t;
      return -c/2 * ((t)*(t-2) - 1) + b;
   }




   float interpolator::quadratic_out_in(float t)
   {
      if (t < 0.5f) return quadratic_out(t*2) * 0.5f;
      else if (t > 0.5f) return quadratic_in((t-0.5f)*2) * 0.5f + 0.5f;
      else return t; // t == 0.5
   }




   ///////////// Cubic Easing: t^3 ///////////////////////




   float interpolator::cubic_in(float t)
   {
      float b = 0;
      float c = 1;
      //	float d = 1;
      return c*(t)*t*t + b;
   }




   float interpolator::cubic_out(float t)
   {
      t = t-1;
      return t*t*t + 1;
   }




   float interpolator::cubic_in_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      t /= (d/2);
      if ((t) < 1) return c/2*t*t*t + b;
      t -= 2;
      return c/2*(t*t*t + 2) + b;
   }




   ///////////// Quadratic Easing: t^4 /////////////////////




   float interpolator::quartic_in(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      t /= d;
      return c*t*t*t*t + b;
   }




   float interpolator::quartic_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      t = t/d-1;
      return -c * (t*t*t*t - 1) + b;
   }




   float interpolator::quartic_in_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
      t -= 2;
      return -c/2 * (t*t*t*t - 2) + b;
   }




   ///////////// Quintic Easing: t^5 ////////////////////




   float interpolator::quintic_in(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      t /= d;
      return c*t*t*t*t*t + b;
   }




   float interpolator::quintic_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      t = t/d - 1;
      return c*(t*t*t*t*t + 1) + b;
   }




   float interpolator::quintic_in_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      t /= d/2;
      if ((t) < 1) return c/2*t*t*t*t*t + b;
      t -= 2;
      return c/2*(t*t*t*t*t + 2) + b;
   }




   ///////////// Sinusoidal Easing: sin(t) ///////////////




   float interpolator::sine_in(float t)
   {
      float b = 0.0f;
      float c = 1.0f;
      float d = 1.0f;
      return -c * cos(t/d * (INTERP_PI/2.0f)) + c + b;
   }




   float interpolator::sine_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      return c * sin(t/d * (INTERP_PI/2.0f)) + b;
   }




   float interpolator::sine_in_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      return -c/2 * (cos(INTERP_PI*t/d) - 1) + b;
   }




   ///////////// Exponential Easing: 2^t /////////////////




   float interpolator::exponential_in(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      return (t==0) ? b : c * (float)pow(2, 10 * (t/d - 1)) + b;
   }




   float interpolator::exponential_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      return (t==d) ? b+c : c * (float)(-pow(2, -10 * t/d) + 1) + b;
   }




   float interpolator::exponential_in_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      if (t==0) return b;
      if (t==d) return b+c;
      if ((t/=d/2) < 1) return c/2 * (float)pow(2, 10 * (t - 1)) + b;
      return c/2 * (float)(-pow(2, -10 * --t) + 2) + b;
   }




   /////////// Circular Easing: sqrt(1-t^2) //////////////




   float interpolator::circular_in(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      t /= d;
      return -c * (sqrt(1 - (t)*t) - 1) + b;
   }




   float interpolator::circular_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      t = t/d - 1;
      return c * sqrt(1 - (t)*t) + b;
   }




   float interpolator::circular_in_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;
      if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
      t -= 2;
      return c/2 * (sqrt(1 - (t)*t) + 1) + b;
   }




   /////////// Elastic Easing: Exponentially Decaying Sine Wave  //////////////




   float interpolator::elastic_in(float t)
   {
      float amplitude = 1.0f; //<- not sure how modifying these variables will change things
      float period = 0.3f; //<- not sure how modifying these variables will change things

      if (t==0) return 0;
      if (t==1) return 1;

      float s = 0; //<-locally used variable

      if (!period) period = 0.3f;
      if (amplitude < 1) { amplitude = 1; s = period/4.0f; }
      else s = period/(2*INTERP_PI) * asin (1/amplitude);
      t -= 1;
      return -(amplitude * (float)pow(2, 10 * (t)) * sin((t - s) * (2.0f * INTERP_PI) / period));
   }




   /////////// Back Easing: Overshooting Cubic Easing: (s+1)*t^3 - s*t^2  //////////////




   // an OVERSHOOT value of 1.70158 produces an overshoot of 10%
#define OVERSHOOT 1.70158f

   float interpolator::back_in(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;


      float s = OVERSHOOT;
      t /= d;
      return c*(t)*t*((s+1)*t - s) + b;
   }




   float interpolator::back_out(float t)
   {
      float b = 0;
      float c = 1;
      float d = 1;

      float s = OVERSHOOT;
      t = t/d - 1;
      return c*((t)*t*((s+1)*t + s) + 1) + b;
   }




   float interpolator::back_in_out(float t)
   {
      float s = OVERSHOOT;
      if ((t) < 1) { t /= 0.5f; s*=(1.525f); return 0.5f*(t*t*(((s)+1)*t - s)); }
      t -= 2;
      s *= (1.525f);
      return 0.5f*((t)*t*(((s)+1)*t + s) + 2);
   }




   /////////// Bounce Easing: Exponentially Decaying Parabolic Bounce  //////////////




   float interpolator::bounce_out(float t)
   {
      if (t < (1.0f/2.75f)) return (7.5625f*t*t);
      else if (t < (2.0f/2.75f))
      {
         t-=(1.5f/2.75f);
         return (7.5625f*(t)*t + 0.75f);
      }
      else if (t < (2.5f/2.75f))
      {
         t-=(2.25f/2.75f);
         return (7.5625f*(t)*t + 0.9375f);
      }
      else
      {
         t-=(2.625f/2.75f);
         return (7.5625f*(t)*t + 0.984375f);
      }
   }




   float interpolator::bounce_in(float t)
   {
      t = 1.0f - t;
      if (t < (1.0f/2.75f)) return 1.0f - (7.5625f*t*t);
      else if (t < (2.0f/2.75f))
      {
         t-=(1.5f/2.75f);
         return 1.0f - (7.5625f*(t)*t + 0.75f);
      }
      else if (t < (2.5f/2.75f))
      {
         t-=(2.25f/2.75f);
         return 1.0f - (7.5625f*(t)*t + 0.9375f);
      }
      else
      {
         t-=(2.625f/2.75f);
         return 1.0f - (7.5625f*(t)*t + 0.984375f);
      }
   }




   float interpolator::bounce_in_out(float t)
   {
      if (t < 0.5f) return bounce_in(t*2.0f) * 0.5f;
      return bounce_out(t*2.0f-1.0f) * 0.5f + 0.5f;
   }




   /////////// User-Friendly Names //////////////




   float interpolator::fast_in(float t) { return quadratic_out(t); }
   float interpolator::fast_out(float t) { return quadratic_in(t); }
   float interpolator::fast_in_out(float t) { return quadratic_out_in(t); }
   float interpolator::slow_in(float t) { return quadratic_in(t); }
   float interpolator::slow_out(float t) { return quadratic_out(t); }
   float interpolator::slow_in_out(float t) { return quadratic_in_out(t); }

   float interpolator::double_fast_in(float t) { return cubic_out(t); }
   float interpolator::double_fast_out(float t) { return cubic_in(t); }
   float interpolator::double_slow_in(float t) { return cubic_in(t); }
   float interpolator::double_slow_out(float t) { return cubic_out(t); }
   float interpolator::double_slow_in_out(float t) { return cubic_in_out(t); }

   float interpolator::tripple_fast_in(float t) { return quartic_out(t); }
   float interpolator::tripple_fast_out(float t) { return quartic_in(t); }
   float interpolator::tripple_slow_in(float t) { return quartic_in(t); }
   float interpolator::tripple_slow_out(float t) { return quartic_out(t); }
   float interpolator::tripple_slow_in_out(float t) { return quartic_in_out(t); }

   float interpolator::quadruple_fast_in(float t) { return quintic_out(t); }
   float interpolator::quadruple_fast_out(float t) { return quintic_in(t); }
   float interpolator::quadruple_slow_in(float t) { return quintic_in(t); }
   float interpolator::quadruple_slow_out(float t) { return quintic_out(t); }
   float interpolator::quadruple_slow_in_out(float t) { return quintic_in_out(t); }




   // TODO: fix this thing

   float interpolator::bloomp_in(float value)
   {
#define fast_curve_interpolator(xxx, yyy, zzz) (fast_in((zzz-xxx)/(yyy-xxx))*(yyy-xxx) + xxx)
#define slow_curve_interpolator(xxx, yyy, zzz) (slow_in((zzz-xxx)/(yyy-xxx))*(yyy-xxx) + xxx)

      float bounce_peak = 0.2f;
      //float &value = value;

      if (value < 0.3f) return slow_curve_interpolator(0.0f, 0.3f, value);
      else if (___in_range(value, 0.3f, 0.45f))
      {
         float inner_value = fast_curve_interpolator(0.3f, 0.45f, value);
         return 1.0f + inner_value * bounce_peak; // bounce_peak is the total extra amount in the bounce
      }
      else if (___in_range(value, 0.45f, 0.6f))
      {
         float inner_value = fast_curve_interpolator(0.6f, 0.45f, value);
         return 1.0f + inner_value * bounce_peak; // bounce_peak is the total extra amount in the bounce
      }
      else if (___in_range(value, 0.6f, 0.75f))
      {
         float inner_value = fast_curve_interpolator(0.6f, 0.75f, value);
         return 1.0f - inner_value * bounce_peak * 0.4f; // bounce_peak is the total extra amount in the bounce
      }
      else if (value >= 0.75f)
      {
         float inner_value = slow_in_out(value)*0.25f + 0.75f; //slow_inout_curve_interpolator(1.0f, 0.75f, value);
         return 1.0f - inner_value * bounce_peak * 0.4f; // bounce_peak is the total extra amount in the bounce
      }
      return value;

#undef fast_curve_interpolator
#undef slow_curve_interpolator
   }




   interpolator::interpolator_func_t interpolator::get_interpolator_by_name(std::string name)
   {
      // incomplete
      if (name == "linear") return linear;

      else if (name == "fast_in") return fast_in;
      else if (name == "fast_out") return fast_out;
      else if (name == "fast_in_out") return fast_in_out;
      else if (name == "slow_in") return slow_in;
      else if (name == "slow_out") return slow_out;
      else if (name == "slow_in_out") return slow_in_out;

      else if (name == "double_fast_in") return double_fast_in;
      else if (name == "double_fast_out") return double_fast_out;
      else if (name == "double_slow_in") return double_slow_in;
      else if (name == "double_slow_out") return double_slow_out;
      else if (name == "double_slow_in_out") return double_slow_in_out;

      else if (name == "tripple_fast_in") return tripple_fast_in;
      else if (name == "tripple_fast_out") return tripple_fast_out;
      else if (name == "tripple_slow_in") return tripple_slow_in;
      else if (name == "tripple_slow_out") return tripple_slow_out;
      else if (name == "tripple_slow_in_out") return tripple_slow_in_out;

      else if (name == "quadruple_fast_in") return quadruple_fast_in;
      else if (name == "quadruple_fast_out") return quadruple_fast_out;
      else if (name == "quadruple_slow_in") return quadruple_slow_in;
      else if (name == "quadruple_slow_out") return quadruple_slow_out;
      else if (name == "quadruple_slow_in_out") return quadruple_slow_in_out;

      return NULL;
   }




   std::string interpolator::get_interpolator_func_name_as_str(interpolator::interpolator_func_t func)
   {
      // incomplete
      if (func == linear) return "linear";

      else if (func == fast_in) return "fast_in";
      else if (func == fast_out) return "fast_out";
      else if (func == fast_in_out) return "fast_in_out";
      else if (func == slow_in) return "slow_in";
      else if (func == slow_out) return "slow_out";
      else if (func == slow_in_out) return "slow_in_out";

      return "undef";
   }




#undef INTERP_PI
}




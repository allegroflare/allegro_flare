



#include <math.h>
#include <string>

#include <allegro_flare/interpolators.h>




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




///////////// LIBRARY EASING FUNCTIONS //////////////
// the equations below come from http://robertpenner.com/easing/




///////////// QUADRATIC EASING: t^2 ///////////////////




// quadratic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be in frames or seconds/milliseconds
//A_INLINE float quadraticIn(float t)

float interpolator::quadraticIn(float t)
{
   return t*t;
}




// quadratic easing out - decelerating to zero velocity

float interpolator::quadraticOut(float t)
{
   return -t*(t-2);
}




// quadratic easing in/out - acceleration until halfway, then deceleration

float interpolator::quadraticInOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   if ((t/=d/2) < 1) return c/2*t*t + b;
   --t;
   return -c/2 * ((t)*(t-2) - 1) + b;
}




// quadratic easing in/out - deceleration until halfway, then acceleration

float interpolator::quadraticOutIn(float t)
{
   if (t < 0.5f) return quadraticOut(t*2) * 0.5f;
   else if (t > 0.5f) return quadraticIn((t-0.5f)*2) * 0.5f + 0.5f;
   else return t; // t == 0.5
}




///////////// CUBIC EASING: t^3 ///////////////////////

// cubic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be frames or seconds/milliseconds

float interpolator::cubicIn(float t)
{
   float b = 0;
   float c = 1;
   //	float d = 1;
   return c*(t)*t*t + b;
}




// cubic easing out - decelerating to zero velocity

float interpolator::cubicOut(float t)
{
   t = t-1;
   return t*t*t + 1;
}




// cubic easing in/out - acceleration until halfway, then deceleration

float interpolator::cubicInOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   t /= (d/2);
   if ((t) < 1) return c/2*t*t*t + b;
   t -= 2;
   return c/2*(t*t*t + 2) + b;
}




///////////// QUARTIC EASING: t^4 /////////////////////

// quartic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be frames or seconds/milliseconds

float interpolator::quarticIn(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   t /= d;
   return c*t*t*t*t + b;
}




// quartic easing out - decelerating to zero velocity

float interpolator::quarticOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   t = t/d-1;
   return -c * (t*t*t*t - 1) + b;
}




// quartic easing in/out - acceleration until halfway, then deceleration

float interpolator::quarticInOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   if ((t/=d/2) < 1) return c/2*t*t*t*t + b;
   t -= 2;
   return -c/2 * (t*t*t*t - 2) + b;
}




///////////// QUINTIC EASING: t^5  ////////////////////

// quintic easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in value, d: duration
// t and d can be frames or seconds/milliseconds

float interpolator::quinticIn(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   t /= d;
   return c*t*t*t*t*t + b;
}




// quintic easing out - decelerating to zero velocity

float interpolator::quinticOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   t = t/d - 1;
   return c*(t*t*t*t*t + 1) + b;
}




// quintic easing in/out - acceleration until halfway, then deceleration

float interpolator::quinticInOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   t /= d/2;
   if ((t) < 1) return c/2*t*t*t*t*t + b;
   t -= 2;
   return c/2*(t*t*t*t*t + 2) + b;
}




///////////// SINUSOIDAL EASING: sin(t) ///////////////




// sinusoidal easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration

float interpolator::sineIn(float t)
{
   float b = 0.0f;
   float c = 1.0f;
   float d = 1.0f;
   return -c * cos(t/d * (INTERP_PI/2.0f)) + c + b;
}




// sinusoidal easing out - decelerating to zero velocity

float interpolator::sineOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   return c * sin(t/d * (INTERP_PI/2.0f)) + b;
}




// sinusoidal easing in/out - accelerating until halfway, then decelerating

float interpolator::sineInOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   return -c/2 * (cos(INTERP_PI*t/d) - 1) + b;
}




///////////// EXPONENTIAL EASING: 2^t /////////////////




// exponential easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration

float interpolator::exponentialIn(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   return (t==0) ? b : c * (float)pow(2, 10 * (t/d - 1)) + b;
}




// exponential easing out - decelerating to zero velocity

float interpolator::exponentialOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   return (t==d) ? b+c : c * (float)(-pow(2, -10 * t/d) + 1) + b;
}




// exponential easing in/out - accelerating until halfway, then decelerating

float interpolator::exponentialInOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   if (t==0) return b;
   if (t==d) return b+c;
   if ((t/=d/2) < 1) return c/2 * (float)pow(2, 10 * (t - 1)) + b;
   return c/2 * (float)(-pow(2, -10 * --t) + 2) + b;
}




/////////// CIRCULAR EASING: sqrt(1-t^2) //////////////




// circular easing in - accelerating from zero velocity
// t: current time, b: beginning value, c: change in position, d: duration

float interpolator::circularIn(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   t /= d;
   return -c * (sqrt(1 - (t)*t) - 1) + b;
}




// circular easing out - decelerating to zero velocity

float interpolator::circularOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   t = t/d - 1;
   return c * sqrt(1 - (t)*t) + b;
}




// circular easing in/out - acceleration until halfway, then deceleration

float interpolator::circularInOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;
   if ((t/=d/2) < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
   t -= 2;
   return c/2 * (sqrt(1 - (t)*t) + 1) + b;
}




/////////// ELASTIC EASING: exponentially decaying sine wave  //////////////




// t: current time, b: beginning value, c: change in value, d: duration, a: amplitude (optional), p: period (optional)
// t and d can be in frames or seconds/milliseconds

float interpolator::elasticIn(float t)
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




/////////// BACK EASING: overshooting cubic easing: (s+1)*t^3 - s*t^2  //////////////




// back easing in - backtracking slightly, then reversing direction and moving to target
// t: current time, b: beginning value, c: change in value, d: duration, s: overshoot amount (optional)
// t and d can be in frames or seconds/milliseconds
// s controls the amount of overshoot: higher s means greater overshoot
// s has a default value of 1.70158, which produces an overshoot of 10 percent
// s==0 produces cubic easing with no overshoot

// an OVERSHOOT value of 1.70158 produces an overshoot of 10%
#define OVERSHOOT 1.70158f

float interpolator::backIn(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;


   float s = OVERSHOOT;
   t /= d;
   return c*(t)*t*((s+1)*t - s) + b;
}




// back easing out - moving towards target, overshooting it slightly, then reversing and coming back to target

float interpolator::backOut(float t)
{
   float b = 0;
   float c = 1;
   float d = 1;

   float s = OVERSHOOT;
   t = t/d - 1;
   return c*((t)*t*((s+1)*t + s) + 1) + b;
}




// back easing in/out - backtracking slightly, then reversing direction and moving to target,
// then overshooting target, reversing, and finally coming back to target

float interpolator::backInOut(float t)
{
   float s = OVERSHOOT;
   if ((t) < 1) { t /= 0.5f; s*=(1.525f); return 0.5f*(t*t*(((s)+1)*t - s)); }
   t -= 2;
   s *= (1.525f);
   return 0.5f*((t)*t*(((s)+1)*t + s) + 2);
}




/////////// BOUNCE EASING: exponentially decaying parabolic bounce  //////////////




// t: current time, b: beginning value, c: change in position, d: duration
// bounce easing out

float interpolator::bounceOut(float t)
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




// bounce easing in

float interpolator::bounceIn(float t)
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




// bounce easing in/out

float interpolator::bounceInOut(float t)
{
   if (t < 0.5f) return bounceIn(t*2.0f) * 0.5f;
   return bounceOut(t*2.0f-1.0f) * 0.5f + 0.5f;
}




float interpolator::fastIn(float t) { return quadraticOut(t); }
float interpolator::fastOut(float t) { return quadraticIn(t); }
float interpolator::fastInOut(float t) { return quadraticOutIn(t); }
float interpolator::slowIn(float t) { return quadraticIn(t); }
float interpolator::slowOut(float t) { return quadraticOut(t); }
float interpolator::slowInOut(float t) { return quadraticInOut(t); }

float interpolator::doubleFastIn(float t) { return cubicOut(t); }
float interpolator::doubleFastOut(float t) { return cubicIn(t); }
float interpolator::doubleSlowIn(float t) { return cubicIn(t); }
float interpolator::doubleSlowOut(float t) { return cubicOut(t); }
float interpolator::doubleSlowInOut(float t) { return cubicInOut(t); }

float interpolator::trippleFastIn(float t) { return quarticOut(t); }
float interpolator::trippleFastOut(float t) { return quarticIn(t); }
float interpolator::trippleSlowIn(float t) { return quarticIn(t); }
float interpolator::trippleSlowOut(float t) { return quarticOut(t); }
float interpolator::trippleSlowInOut(float t) { return quarticInOut(t); }

float interpolator::quadrupleFastIn(float t) { return quinticOut(t); }
float interpolator::quadrupleFastOut(float t) { return quinticIn(t); }
float interpolator::quadrupleSlowIn(float t) { return quinticIn(t); }
float interpolator::quadrupleSlowOut(float t) { return quinticOut(t); }
float interpolator::quadrupleSlowInOut(float t) { return quinticInOut(t); }




// TODO: fix this thing

float interpolator::bloompIn(float value)
{
#define fast_curve_interpolator(xxx, yyy, zzz) (fastIn((zzz-xxx)/(yyy-xxx))*(yyy-xxx) + xxx)
#define slow_curve_interpolator(xxx, yyy, zzz) (slowIn((zzz-xxx)/(yyy-xxx))*(yyy-xxx) + xxx)

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
      float inner_value = slowInOut(value)*0.25f + 0.75f; //slow_inout_curve_interpolator(1.0f, 0.75f, value);
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

   else if (name == "fastIn") return fastIn;
   else if (name == "fastOut") return fastOut;
   else if (name == "fastInOut") return fastInOut;
   else if (name == "slowIn") return slowIn;
   else if (name == "slowOut") return slowOut;
   else if (name == "slowInOut") return slowInOut;

   else if (name == "doubleFastIn") return doubleFastIn;
   else if (name == "doubleFastOut") return doubleFastOut;
   else if (name == "doubleSlowIn") return doubleSlowIn;
   else if (name == "doubleSlowOut") return doubleSlowOut;
   else if (name == "doubleSlowInOut") return doubleSlowInOut;

   else if (name == "trippleFastIn") return trippleFastIn;
   else if (name == "trippleFastOut") return trippleFastOut;
   else if (name == "trippleSlowIn") return trippleSlowIn;
   else if (name == "trippleSlowOut") return trippleSlowOut;
   else if (name == "trippleSlowInOut") return trippleSlowInOut;

   else if (name == "quadrupleFastIn") return quadrupleFastIn;
   else if (name == "quadrupleFastOut") return quadrupleFastOut;
   else if (name == "quadrupleSlowIn") return quadrupleSlowIn;
   else if (name == "quadrupleSlowOut") return quadrupleSlowOut;
   else if (name == "quadrupleSlowInOut") return quadrupleSlowInOut;

   return NULL;
}




std::string interpolator::get_interpolator_func_name_as_str(interpolator::interpolator_func_t func)
{
   // incomplete
   if (func == linear) return "linear";

   else if (func == fastIn) return "fastIn";
   else if (func == fastOut) return "fastOut";
   else if (func == fastInOut) return "fastInOut";
   else if (func == slowIn) return "slowIn";
   else if (func == slowOut) return "slowOut";
   else if (func == slowInOut) return "slowInOut";

   return "undef";
}




#undef INTERP_PI





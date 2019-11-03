#pragma once


#include <vector>
#include <AllegroFlare/Interpolators.hpp>


namespace AllegroFlare
{
   class Motion
   {
   public:
      class Node // might find a better name
      {
      public:
         float *val;
         float start_time;
         float end_time;
         float start_val;
         float end_val;
         float (*interpolator_func)(float);
         void (*callback_func)(void *);
         void *callback_data;
         bool active;

         Node();
         Node(float *val, float start_time, float end_time, float start_val, float end_val,
               float (*interpolator_func)(float), void (*callback_func)(void *data), void *callback_data);
         bool update(float time_now);
         void set(float *val, float start_time, float end_time, float start_val, float end_val,
               float (*interpolator_func)(float), void (*callback_func)(void *data), void *callback_data);
         void clear();
      };

   private:
      int last_index;
      unsigned num_reserved;
      int get_new_index();
      std::vector<Motion::Node *> control;

   public:
      Motion(unsigned num_reserved=200);
      bool update(float time_now);

      bool is_being_animated(float *val);
      bool clear_animations_on(float *val);
      bool clear_animations_on(std::vector<float *> vals);
      int get_num_active_animations();
      void clear_all();

      // simple motion
      void animate(float *val, float start_val, float end_val, float start_time, float end_time, float (*interpolator_func)(float)=interpolator::double_fast_in, void (*callback_func)(void *)=nullptr, void *callback_data=nullptr);
      void move(float *val, float displacement, float duration=0.4, float (*interpolator_func)(float)=interpolator::fast_in, void (*callback_func)(void *)=nullptr, void *callback_data=nullptr);
      void move_to(float *val, float dest_val, float duration=0.4, float (*interpolator_func)(float)=interpolator::fast_in, void (*callback_func)(void *)=nullptr, void *callback_data=nullptr);

      // same as above, but clears any existing animations on *val beforehand.
      void canimate(float *val, float start_val, float end_val, float start_time, float end_time, float (*interpolator_func)(float)=interpolator::double_fast_in, void (*callback_func)(void *)=nullptr, void *callback_data=nullptr);
      void cmove(float *val, float displacement, float duration=0.4, float (*interpolator_func)(float)=interpolator::fast_in, void (*callback_func)(void *)=nullptr, void *callback_data=nullptr);
      void cmove_to(float *val, float dest_val, float duration=0.4, float (*interpolator_func)(float)=interpolator::fast_in, void (*callback_func)(void *)=nullptr, void *callback_data=nullptr);
   };
}



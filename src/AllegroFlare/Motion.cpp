

#include <AllegroFlare/Motion.hpp>

#include <allegro5/allegro.h> // for al_get_time()


namespace AllegroFlare
{
   Motion::Node::Node()
      : val(NULL)
      , start_time(0)
      , end_time(0)
      , start_val(0)
      , end_val(0)
      , interpolator_func(NULL)
      , callback_func(NULL)
      , callback_data(NULL)
      , active(false)
   { }


   Motion::Node::Node(float *val, float start_time, float end_time, float start_val, float end_val,
         float (*interpolator_func)(float), void (*callback_func)(void *data), void *callback_data)
      : val(val)
      , start_time(start_time)
      , end_time(end_time)
      , start_val(start_val)
      , end_val(end_val)
      , interpolator_func(interpolator_func)
      , callback_func(callback_func)
      , callback_data(callback_data)
      , active(true)
   { }


   bool Motion::Node::update(float time_now)
   {
      if (!active) return active;
      if (time_now < start_time) return active;
      else if (time_now >= end_time)
      {
         *val = end_val;
         active = false;
         if (callback_func) callback_func(callback_data);
      }
      else
      {
         float local_normal = (time_now - start_time) / (end_time - start_time);
         *val = (end_val - start_val) * interpolator_func(local_normal) + start_val;
      }
      return active;
   }


   void Motion::Node::set(float *val, float start_time, float end_time, float start_val, float end_val,
         float (*interpolator_func)(float), void (*callback_func)(void *), void *callback_data)
   {
      this->active = true;
      this->val = val;
      this->start_time = start_time;
      this->end_time = end_time;
      this->start_val = start_val;
      this->end_val = end_val;
      this->interpolator_func = interpolator_func;
      this->callback_func = callback_func;
      this->callback_data = callback_data;
   }


   void Motion::Node::clear()
   {
      val = NULL;
      start_time = 0;
      end_time = 0;
      start_val = 0;
      end_val = 0;
      callback_func = NULL;
      interpolator_func = NULL;
      active = false;
   }


   Motion::Motion(unsigned num_reserved)
      : last_index(0)
        , num_reserved(num_reserved)
   {
      for (unsigned i=0; i<num_reserved; i++)
         control.push_back(new Motion::Node());
   }


   int Motion::get_new_index()
   {
      // this is kinda ghetto
      last_index++;
      last_index = last_index % num_reserved;
      return last_index;
   }


   void Motion::animate(float *val, float start_val, float end_val, float start_time, float end_time, float (*interpolator_func)(float), void (*callback_func)(void *), void *callback_data)
   {
      int new_index = get_new_index();
      control[new_index]->clear();
      control[new_index]->set(val, start_time, end_time, start_val, end_val, interpolator_func, callback_func, callback_data);
   }


   void Motion::move(float *val, float displacement, float duration, float (*interpolator_func)(float), void (*callback_func)(void *), void *callback_data)
   {
      double time_now = al_get_time();
      int new_index = get_new_index();
      control[new_index]->clear();
      control[new_index]->set(val, time_now, time_now+duration, *val, *val+displacement, interpolator_func, callback_func, callback_data);
   }


   void Motion::move_to(float *val, float end_val, float duration, float (*interpolator_func)(float), void (*callback_func)(void *), void *callback_data)
   {
      double time_now = al_get_time();
      int new_index = get_new_index();
      control[new_index]->clear();
      control[new_index]->set(val, time_now, time_now+duration, *val, end_val, interpolator_func, callback_func, callback_data);
   }


   void Motion::canimate(float *val, float start_val, float end_val, float start_time, float end_time, float (*interpolator_func)(float), void (*callback_func)(void *), void *callback_data)
   {
      int new_index = get_new_index();
      clear_animations_on(val);
      control[new_index]->clear();
      control[new_index]->set(val, start_time, end_time, start_val, end_val, interpolator_func, callback_func, callback_data);
   }


   void Motion::cmove(float *val, float displacement, float duration, float (*interpolator_func)(float), void (*callback_func)(void *), void *callback_data)
   {
      double time_now = al_get_time();
      int new_index = get_new_index();
      clear_animations_on(val);
      control[new_index]->clear();
      control[new_index]->set(val, time_now, time_now+duration, *val, *val+displacement, interpolator_func, callback_func, callback_data);
   }


   void Motion::cmove_to(float *val, float end_val, float duration, float (*interpolator_func)(float), void (*callback_func)(void *), void *callback_data)
   {
      double time_now = al_get_time();
      int new_index = get_new_index();
      clear_animations_on(val);
      control[new_index]->clear();
      control[new_index]->set(val, time_now, time_now+duration, *val, end_val, interpolator_func, callback_func, callback_data);
   }


   bool Motion::clear_animations_on(float *val)
   {
      bool found = false;
      for (unsigned i=0; i<num_reserved; i++)
         if (control[i]->val == val)
         {
            control[i]->clear();
            found = true;
         }
      return found;
   }


   bool Motion::clear_animations_on(std::vector<float *> vals)
   {
      bool found = false;
      for (unsigned c=0; c<control.size(); c++)
         for (unsigned v=0; v<vals.size(); v++)
            if (vals[v] == control[c]->val)
            {
               control[c]->clear();
               found=true;
            }
      return found;
   }


   void Motion::clear_all()
   {
      for (unsigned c=0; c<control.size(); c++)
         control[c]->clear();
   }


   bool Motion::update(float time_now)
   {
      bool whatever = false; // does it need a name?
      for (unsigned i=0; i<control.size(); i++)
      {
         if (!control[i]->update(time_now)) control[i]->clear();
         else whatever = true;
      }
      return whatever;
   }


   bool Motion::is_being_animated(float *val)
   {
      for (unsigned i=0; i<control.size(); i++)
         if (control[i]->val == val) return true;
      return false;
   }


   int Motion::get_num_active_animations()
   {
      int count = 0;
      for (unsigned i=0; i<control.size(); i++)
         if (control[i]->active) count++;
      return count;
   }
}



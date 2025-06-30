#pragma once


#include <cstdint>
#include <functional>


namespace AllegroFlare
{
   class AtomicTimeStepper
   {
   private:
      double time_step_resolution_denom;
      double time_step_resolution;
      double total_accumulated_time;
      uint64_t total_accumulated_steps;
      std::function<void(double, double, void*)> on_step_func;
      void* on_step_func_user_data;

   protected:


   public:
      AtomicTimeStepper();
      ~AtomicTimeStepper();

      void set_on_step_func(std::function<void(double, double, void*)> on_step_func);
      void set_on_step_func_user_data(void* on_step_func_user_data);
      double get_time_step_resolution_denom() const;
      double get_time_step_resolution() const;
      double get_total_accumulated_time() const;
      uint64_t get_total_accumulated_steps() const;
      std::function<void(double, double, void*)> get_on_step_func() const;
      void* get_on_step_func_user_data() const;
      void step_one();
      void step_n_times(int num_times_to_step=1);
   };
}




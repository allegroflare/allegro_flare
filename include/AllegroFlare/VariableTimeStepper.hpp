#pragma once


#include <AllegroFlare/AtomicTimeStepper.hpp>
#include <functional>
#include <tuple>


namespace AllegroFlare
{
   class VariableTimeStepper
   {
   private:
      AllegroFlare::AtomicTimeStepper atomic_time_stepper;
      int max_allowed_steps;

   protected:


   public:
      VariableTimeStepper();
      ~VariableTimeStepper();

      int get_max_allowed_steps() const;
      double get_total_accumulated_time();
      void set_atomic_on_step_func(std::function<void(double, double, void*)> on_step_func={});
      void set_atomic_on_step_func_user_data(void* on_step_func_user_data=nullptr);
      void set_max_allowed_steps(int max_allowed_steps=10);
      std::tuple<double, int, int> step_ahead_to(double time_to_step_to=1.0/60.0);
   };
}




#pragma once


#include <AllegroFlare/Timer.hpp>
#include <AllegroFlare/VariableTimeStepper.hpp>
#include <functional>


namespace AllegroFlare
{
   class GameWorldTimer
   {
   private:
      AllegroFlare::VariableTimeStepper variable_time_stepper;
      double last_time_step__time_remaining_to_next_step;
      int last_time_step__num_steps_taken;
      int last_time_step__excess_steps_not_taken;
      double last_time_step__total_accumulated_time;
      double last_time_step__total_accumulated_time_target;
      AllegroFlare::Timer timer;

   protected:


   public:
      GameWorldTimer();
      ~GameWorldTimer();

      double get_last_time_step__time_remaining_to_next_step() const;
      int get_last_time_step__num_steps_taken() const;
      int get_last_time_step__excess_steps_not_taken() const;
      double get_last_time_step__total_accumulated_time() const;
      double get_last_time_step__total_accumulated_time_target() const;
      void set_atomic_on_step_func(std::function<void(double, double, void*)> on_step_func={});
      void set_atomic_on_step_func_user_data(void* on_step_func_user_data=nullptr);
      void start();
      void stop();
      void pause();
      void unpause();
      bool is_running();
      void update();
   };
}




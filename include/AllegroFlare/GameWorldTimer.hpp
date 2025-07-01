#pragma once


#include <AllegroFlare/Timer.hpp>
#include <AllegroFlare/VariableTimeStepper.hpp>


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

      void start();
      void stop();
      void pause();
      bool is_running();
      void update();
   };
}




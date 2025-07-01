

#include <AllegroFlare/VariableTimeStepper.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


VariableTimeStepper::VariableTimeStepper()
   : atomic_time_stepper({})
   , max_allowed_steps(10)
{
}


VariableTimeStepper::~VariableTimeStepper()
{
}


int VariableTimeStepper::get_max_allowed_steps() const
{
   return max_allowed_steps;
}


double VariableTimeStepper::get_total_accumulated_time()
{
   return atomic_time_stepper.get_total_accumulated_time();
}

void VariableTimeStepper::set_atomic_on_step_func(std::function<void(double, double, void*)> on_step_func)
{
   atomic_time_stepper.set_on_step_func(on_step_func);
   return;
}

void VariableTimeStepper::set_atomic_on_step_func_user_data(void* on_step_func_user_data)
{
   atomic_time_stepper.set_on_step_func_user_data(on_step_func_user_data);
   return;
}

void VariableTimeStepper::set_max_allowed_steps(int max_allowed_steps)
{
   if (!(max_allowed_steps > 0))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::VariableTimeStepper::set_max_allowed_steps]: error: guard \"max_allowed_steps > 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::VariableTimeStepper::set_max_allowed_steps]: error: guard \"max_allowed_steps > 0\" not met");
   }
   this->max_allowed_steps = max_allowed_steps;
   return;
}

std::tuple<double, int, int> VariableTimeStepper::step_ahead_to(double time_to_step_to)
{
   const double current_time = atomic_time_stepper.get_total_accumulated_time();

   if (time_to_step_to <= current_time)
   {
       // Target time is not in the future. Return status.
       return { time_to_step_to - current_time, 0, 0 };
   }

   // Calculate the number of steps required
   const double duration_to_step = time_to_step_to - current_time;
   const double time_step_res = atomic_time_stepper.get_time_step_resolution();
   int num_steps_to_take = static_cast<int>(std::floor(duration_to_step / time_step_res));
   int excess_steps_not_taken = 0;

   // Cap the number of steps to perform to prevent the "spiral of death".
   if (num_steps_to_take > max_allowed_steps)
   {
       excess_steps_not_taken = num_steps_to_take - max_allowed_steps;
       num_steps_to_take = max_allowed_steps;
   }

   if (num_steps_to_take > 0)
   {
       atomic_time_stepper.step_n_times(num_steps_to_take);
   }

   // Calculate final remaining time and return the complete result.
   const double new_current_time = atomic_time_stepper.get_total_accumulated_time();
   const double remaining_time = time_to_step_to - new_current_time;

   return { remaining_time, num_steps_to_take, excess_steps_not_taken };
}


} // namespace AllegroFlare



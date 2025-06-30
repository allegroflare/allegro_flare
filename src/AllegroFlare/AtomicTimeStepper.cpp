

#include <AllegroFlare/AtomicTimeStepper.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


AtomicTimeStepper::AtomicTimeStepper()
   : time_step_resolution_denom(256.0)
   , time_step_resolution(1.0 / time_step_resolution_denom)
   , total_accumulated_time(0.0)
   , total_accumulated_steps(0)
   , on_step_func({})
   , on_step_func_user_data(nullptr)
{
}


AtomicTimeStepper::~AtomicTimeStepper()
{
}


void AtomicTimeStepper::set_on_step_func(std::function<void(double, double, void*)> on_step_func)
{
   this->on_step_func = on_step_func;
}


void AtomicTimeStepper::set_on_step_func_user_data(void* on_step_func_user_data)
{
   this->on_step_func_user_data = on_step_func_user_data;
}


double AtomicTimeStepper::get_time_step_resolution_denom() const
{
   return time_step_resolution_denom;
}


double AtomicTimeStepper::get_time_step_resolution() const
{
   return time_step_resolution;
}


double AtomicTimeStepper::get_total_accumulated_time() const
{
   return total_accumulated_time;
}


uint64_t AtomicTimeStepper::get_total_accumulated_steps() const
{
   return total_accumulated_steps;
}


std::function<void(double, double, void*)> AtomicTimeStepper::get_on_step_func() const
{
   return on_step_func;
}


void* AtomicTimeStepper::get_on_step_func_user_data() const
{
   return on_step_func_user_data;
}


void AtomicTimeStepper::step_one()
{
   total_accumulated_time += time_step_resolution;
   total_accumulated_steps++;
   if (on_step_func) on_step_func(time_step_resolution, total_accumulated_time, on_step_func_user_data);
   return;
}

void AtomicTimeStepper::step_n_times(int num_times_to_step)
{
   if (!((num_times_to_step >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::AtomicTimeStepper::step_n_times]: error: guard \"(num_times_to_step >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::AtomicTimeStepper::step_n_times]: error: guard \"(num_times_to_step >= 0)\" not met");
   }
   for (int i=0; i<num_times_to_step; i++)
   {
      step_one();
   }
   return;
}


} // namespace AllegroFlare



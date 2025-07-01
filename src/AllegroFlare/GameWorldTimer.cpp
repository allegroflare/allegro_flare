

#include <AllegroFlare/GameWorldTimer.hpp>




namespace AllegroFlare
{


GameWorldTimer::GameWorldTimer()
   : variable_time_stepper({})
   , last_time_step__time_remaining_to_next_step(0)
   , last_time_step__num_steps_taken(0)
   , last_time_step__excess_steps_not_taken(0)
   , last_time_step__total_accumulated_time(0)
   , last_time_step__total_accumulated_time_target(0)
   , timer({})
{
}


GameWorldTimer::~GameWorldTimer()
{
}


void GameWorldTimer::start()
{
   timer.start();
   return;
}

void GameWorldTimer::stop()
{
   timer.stop();
   return;
}

void GameWorldTimer::pause()
{
   timer.pause();
   return;
}

bool GameWorldTimer::is_running()
{
   return timer.is_running();
}

void GameWorldTimer::update()
{
   if (!timer.is_running()) return;

   double elapsed_seconds = static_cast<double>(timer.get_elapsed_time_microseconds()) / 1000000.0;

   std::tie(
      last_time_step__time_remaining_to_next_step,
      last_time_step__num_steps_taken,
      last_time_step__excess_steps_not_taken
   ) = variable_time_stepper.step_ahead_to(elapsed_seconds);

   last_time_step__total_accumulated_time_target = elapsed_seconds;
   last_time_step__total_accumulated_time = variable_time_stepper.get_total_accumulated_time();

   return;
}


} // namespace AllegroFlare



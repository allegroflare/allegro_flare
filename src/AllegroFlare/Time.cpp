

#include <AllegroFlare/Time.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Time::Time(float started_at)
   : started_at(started_at)
   , playhead(0.0f)
   , rate(0.0f)
   , last_rate_changed_at(0.0f)
{
}


Time::~Time()
{
}


void Time::set_started_at(float started_at)
{
   this->started_at = started_at;
}


float Time::get_started_at() const
{
   return started_at;
}


float Time::absolute_now()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Time::absolute_now]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Time::absolute_now: error: guard \"al_is_system_installed()\" not met");
   }
   return al_get_time();
}

float Time::now()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Time::now]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Time::now: error: guard \"al_is_system_installed()\" not met");
   }
   float time_now = al_get_time();
   float rate_window_age = time_now - last_rate_changed_at;
   playhead += (rate_window_age * rate);
   return playhead;
}

void Time::jump_ahead_sec(float distance)
{
   if (!(distance >= 0.0))
   {
      std::stringstream error_message;
      error_message << "[Time::jump_ahead_sec]: error: guard \"distance >= 0.0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Time::jump_ahead_sec: error: guard \"distance >= 0.0\" not met");
   }
   // TODO: Consider and account for possible overflows
   playhead += distance;
}

void Time::set_rate(float rate)
{
   if (!(rate >= 0.0001))
   {
      std::stringstream error_message;
      error_message << "[Time::set_rate]: error: guard \"rate >= 0.0001\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Time::set_rate: error: guard \"rate >= 0.0001\" not met");
   }
   last_rate_changed_at = absolute_now();
   this->rate = rate;
   return;
}


} // namespace AllegroFlare



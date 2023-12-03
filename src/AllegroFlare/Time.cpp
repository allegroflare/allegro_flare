

#include <AllegroFlare/Time.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Time::Time(double started_at)
   : started_at(started_at)
   , playhead(0.0)
   , rate(1.0)
   , last_rate_changed_at(0.0)
{
}


Time::~Time()
{
}


void Time::set_started_at(double started_at)
{
   this->started_at = started_at;
}


double Time::get_started_at() const
{
   return started_at;
}


double Time::get_rate() const
{
   return rate;
}


double Time::universal_absolute_now()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Time::universal_absolute_now]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Time::universal_absolute_now: error: guard \"al_is_system_installed()\" not met");
   }
   return al_get_time();
}

double Time::now(double time_now)
{
   double rate_window_age = time_now - last_rate_changed_at;
   std::cout << "rate_window_age: " << rate_window_age << std::endl;
   playhead += (rate_window_age * rate);
   return playhead;
}

void Time::jump_ahead_sec(double distance)
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

void Time::set_rate(double rate, double time_now)
{
   if (!(rate >= 0.0001))
   {
      std::stringstream error_message;
      error_message << "[Time::set_rate]: error: guard \"rate >= 0.0001\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Time::set_rate: error: guard \"rate >= 0.0001\" not met");
   }
   last_rate_changed_at = time_now;
   this->rate = rate;
   return;
}

double Time::calculate_age(double time_now, double time_begin)
{
   return time_now - time_begin;
}


} // namespace AllegroFlare



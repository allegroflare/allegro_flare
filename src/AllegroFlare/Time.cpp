

#include <AllegroFlare/Time.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Time::Time()
   : absolute_now(0.0)
   , playhead(0.0)
   , rate(1.0)
   , paused(false)
   , last_rate_changed_at(0.0)
{
}


Time::~Time()
{
}


double Time::get_absolute_now() const
{
   return absolute_now;
}


double Time::get_playhead() const
{
   return playhead;
}


double Time::get_rate() const
{
   return rate;
}


bool Time::get_paused() const
{
   return paused;
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

void Time::set_absolute_now(double absolute_now)
{
   if (!((absolute_now >= this->absolute_now)))
   {
      std::stringstream error_message;
      error_message << "[Time::set_absolute_now]: error: guard \"(absolute_now >= this->absolute_now)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Time::set_absolute_now: error: guard \"(absolute_now >= this->absolute_now)\" not met");
   }
   // NOTE: Time can not flow in reverse in this model. An absolute_now can only be assigned if it is equal or past
   // the current absolute now.
   double previous_absolute_now = this->absolute_now;
   this->absolute_now = absolute_now;

   if (!paused)
   {
      double rate_window_age = absolute_now - previous_absolute_now;
      playhead += rate_window_age * rate;
   }

   return;
}

void Time::pause()
{
   if (paused) return;
   paused = true;
   return;
}

void Time::unpause()
{
   if (!paused) return;
   paused = false;
   return;
}

double Time::now()
{
   //update_now();
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

void Time::set_rate(double rate)
{
   if (!(rate >= 0.0001))
   {
      std::stringstream error_message;
      error_message << "[Time::set_rate]: error: guard \"rate >= 0.0001\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Time::set_rate: error: guard \"rate >= 0.0001\" not met");
   }
   //last_rate_changed_at = absolute_now;
   this->rate = rate;
   return;
}

double Time::calculate_age(double time_now, double time_begin)
{
   return time_now - time_begin;
}


} // namespace AllegroFlare



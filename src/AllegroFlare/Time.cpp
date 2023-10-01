

#include <AllegroFlare/Time.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Time::Time(float started_at)
   : started_at(started_at)
   , offset(0.0f)
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
   return absolute_now() + offset;
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
   offset += distance;
}


} // namespace AllegroFlare



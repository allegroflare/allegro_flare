

#include <AllegroFlare/Time.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Time::Time(float started_at)
   : started_at(started_at)
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


float Time::now()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Time::now]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error(error_message.str());
   }
   return al_get_time();
}


} // namespace AllegroFlare



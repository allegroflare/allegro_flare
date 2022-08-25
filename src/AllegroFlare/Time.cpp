

#include <AllegroFlare/Time.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


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
         error_message << "Time" << "::" << "now" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   return al_get_time();
}
} // namespace AllegroFlare



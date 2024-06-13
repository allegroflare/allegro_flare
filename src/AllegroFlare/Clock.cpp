

#include <AllegroFlare/Clock.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


Clock::Clock()
{
}


Clock::~Clock()
{
}


float Clock::real_world_time_since(float time_of_event)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Clock::real_world_time_since]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Clock::real_world_time_since]: error: guard \"al_is_system_installed()\" not met");
   }
   return al_get_time() - time_of_event;
}


} // namespace AllegroFlare



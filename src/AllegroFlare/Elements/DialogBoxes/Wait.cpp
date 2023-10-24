

#include <AllegroFlare/Elements/DialogBoxes/Wait.hpp>

#include <allegro5/allegro.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace DialogBoxes
{


Wait::Wait(float duration, float started_at)
   : AllegroFlare::Elements::DialogBoxes::Base(AllegroFlare::Elements::DialogBoxes::Wait::TYPE)
   , duration(duration)
   , started_at(started_at)
{
}


Wait::~Wait()
{
}


void Wait::set_duration(float duration)
{
   this->duration = duration;
}


float Wait::get_duration() const
{
   return duration;
}


float Wait::get_started_at() const
{
   return started_at;
}


bool Wait::ready_to_auto_advance()
{
   // When the Wait dialog is finished, it's ready to auto advance
   return get_finished();
}

void Wait::update()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Wait::update]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Wait::update: error: guard \"al_is_system_installed()\" not met");
   }
   // TODO: Test this update
   // TODO: Use AllegroFlare::Time and speed up the advancing rate for a faster test
   if (get_finished()) return;

   float time_now = al_get_time();
   if (time_now - started_at >= duration)
   {
      set_finished(true);
   }
   return;
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare



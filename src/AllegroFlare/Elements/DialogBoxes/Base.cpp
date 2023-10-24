

#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>

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


Base::Base(std::string type)
   : type(type)
   , created_at(0)
   , finished(false)
{
}


Base::~Base()
{
}


void Base::set_created_at(float created_at)
{
   this->created_at = created_at;
}


void Base::set_finished(bool finished)
{
   this->finished = finished;
}


std::string Base::get_type() const
{
   return type;
}


float Base::get_created_at() const
{
   return created_at;
}


bool Base::get_finished() const
{
   return finished;
}


void Base::start()
{
   // TODO: Implement this in the derived DialogBoxes, might consider renaming "crated_at" to "started_at"
   //       and setting it here
   return;
}

void Base::update()
{
   // TODO: Consider if this should be pure_virtual
   return;
}

void Base::advance()
{
   // TODO: Consider if this should be pure_virtual
   return;
}

bool Base::ready_to_auto_advance()
{
   // TODO: Consider if this should be pure_virtual
   return false;
}

bool Base::move_cursor_position_up()
{
   return false;
}

bool Base::move_cursor_position_down()
{
   return false;
}

float Base::infer_age(float time_now)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Base::infer_age]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Base::infer_age: error: guard \"al_is_system_installed()\" not met");
   }
   return time_now - get_created_at();
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace DialogBoxes
} // namespace Elements
} // namespace AllegroFlare



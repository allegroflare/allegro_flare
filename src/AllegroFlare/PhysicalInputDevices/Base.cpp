

#include <AllegroFlare/PhysicalInputDevices/Base.hpp>

#include <allegro5/allegro.h>


namespace AllegroFlare
{
namespace PhysicalInputDevices
{


Base::Base(std::string type, std::string name, bool connected)
   : type(type)
   , name(name)
   , connected(connected)
   , connected_at(0.0f)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


std::string Base::get_name() const
{
   return name;
}


bool Base::get_connected() const
{
   return connected;
}


float Base::get_connected_at() const
{
   return connected_at;
}


void Base::set_connected(bool connected)
{
   // Make no change if it's the same status
   if (this->connected == connected) return;

   // Update the connected_at time if the device has become connected
   if (connected) connected_at = al_get_time();
   else connected_at = 0.0f;

   this->connected = connected;
   return;
}

bool Base::is_keyboard()
{
   return false;
}

bool Base::is_joystick()
{
   return false;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace PhysicalInputDevices
} // namespace AllegroFlare



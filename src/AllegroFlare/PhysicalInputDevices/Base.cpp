

#include <AllegroFlare/PhysicalInputDevices/Base.hpp>




namespace AllegroFlare
{
namespace PhysicalInputDevices
{


Base::Base(std::string type, std::string name, bool connected)
   : type(type)
   , name(name)
   , connected(connected)
{
}


Base::~Base()
{
}


void Base::set_connected(bool connected)
{
   this->connected = connected;
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



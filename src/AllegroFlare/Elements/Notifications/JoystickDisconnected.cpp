

#include <AllegroFlare/Elements/Notifications/JoystickDisconnected.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace Notifications
{


JoystickDisconnected::JoystickDisconnected(std::string joystick_name)
   : AllegroFlare::Elements::Notifications::Base("JoystickDisconnected")
   , joystick_name(joystick_name)
{
}


JoystickDisconnected::~JoystickDisconnected()
{
}


void JoystickDisconnected::set_joystick_name(std::string joystick_name)
{
   this->joystick_name = joystick_name;
}


std::string JoystickDisconnected::get_joystick_name() const
{
   return joystick_name;
}




} // namespace Notifications
} // namespace Elements
} // namespace AllegroFlare



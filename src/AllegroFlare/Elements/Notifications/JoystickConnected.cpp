

#include <AllegroFlare/Elements/Notifications/JoystickConnected.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace Notifications
{


JoystickConnected::JoystickConnected(std::string joystick_name)
   : AllegroFlare::Elements::Notifications::Base("JoystickConnected")
   , joystick_name(joystick_name)
{
}


JoystickConnected::~JoystickConnected()
{
}


void JoystickConnected::set_joystick_name(std::string joystick_name)
{
   this->joystick_name = joystick_name;
}


std::string JoystickConnected::get_joystick_name() const
{
   return joystick_name;
}




} // namespace Notifications
} // namespace Elements
} // namespace AllegroFlare



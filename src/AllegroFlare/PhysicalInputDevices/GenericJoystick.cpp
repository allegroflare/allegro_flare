

#include <AllegroFlare/PhysicalInputDevices/GenericJoystick.hpp>




namespace AllegroFlare
{
namespace PhysicalInputDevices
{


GenericJoystick::GenericJoystick()
   : AllegroFlare::PhysicalInputDevices::Base(AllegroFlare::PhysicalInputDevices::GenericJoystick::TYPE, "Generic Joystick")
   , al_joystick(nullptr)
{
}


GenericJoystick::~GenericJoystick()
{
}


void GenericJoystick::set_al_joystick(ALLEGRO_JOYSTICK* al_joystick)
{
   this->al_joystick = al_joystick;
}


ALLEGRO_JOYSTICK* GenericJoystick::get_al_joystick() const
{
   return al_joystick;
}


bool GenericJoystick::is_keyboard()
{
   return true;
}


} // namespace PhysicalInputDevices
} // namespace AllegroFlare



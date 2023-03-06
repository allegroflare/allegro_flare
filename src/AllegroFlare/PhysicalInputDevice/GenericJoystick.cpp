

#include <AllegroFlare/PhysicalInputDevice/GenericJoystick.hpp>




namespace AllegroFlare
{
namespace PhysicalInputDevice
{


GenericJoystick::GenericJoystick()
   : AllegroFlare::PhysicalInputDevice::Base(AllegroFlare::PhysicalInputDevice::GenericJoystick::TYPE, "Generic Joystick")
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


} // namespace PhysicalInputDevice
} // namespace AllegroFlare





#include <AllegroFlare/PhysicalInputDevice/GenericJoystick.hpp>




namespace AllegroFlare
{
namespace PhysicalInputDevice
{


GenericJoystick::GenericJoystick()
   : AllegroFlare::PhysicalInputDevice::Base(AllegroFlare::PhysicalInputDevice::GenericJoystick::TYPE, "Generic Joystick")
   , al_joystick(nullptr)
   , connected(false)
{
}


GenericJoystick::~GenericJoystick()
{
}


void GenericJoystick::set_al_joystick(ALLEGRO_JOYSTICK* al_joystick)
{
   this->al_joystick = al_joystick;
}


void GenericJoystick::set_connected(bool connected)
{
   this->connected = connected;
}


ALLEGRO_JOYSTICK* GenericJoystick::get_al_joystick() const
{
   return al_joystick;
}


bool GenericJoystick::get_connected() const
{
   return connected;
}




} // namespace PhysicalInputDevice
} // namespace AllegroFlare



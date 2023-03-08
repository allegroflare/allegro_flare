

#include <AllegroFlare/PhysicalInputDevices/Joysticks/Base.hpp>




namespace AllegroFlare
{
namespace PhysicalInputDevices
{
namespace Joysticks
{


Base::Base()
   : AllegroFlare::PhysicalInputDevices::Base(AllegroFlare::PhysicalInputDevices::Joysticks::Base::TYPE, "Generic Joystick")
   , al_joystick(nullptr)
{
}


Base::~Base()
{
}


void Base::set_al_joystick(ALLEGRO_JOYSTICK* al_joystick)
{
   this->al_joystick = al_joystick;
}


ALLEGRO_JOYSTICK* Base::get_al_joystick() const
{
   return al_joystick;
}


bool Base::is_joystick()
{
   return true;
}

bool Base::is_using_al_joystick(ALLEGRO_JOYSTICK* possibly_same_al_joystick)
{
   return (possibly_same_al_joystick == al_joystick);
}


} // namespace Joysticks
} // namespace PhysicalInputDevices
} // namespace AllegroFlare



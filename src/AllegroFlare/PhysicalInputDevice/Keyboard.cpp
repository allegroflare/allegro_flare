

#include <AllegroFlare/PhysicalInputDevice/Keyboard.hpp>




namespace AllegroFlare
{
namespace PhysicalInputDevice
{


Keyboard::Keyboard()
   : AllegroFlare::PhysicalInputDevice::Base(AllegroFlare::PhysicalInputDevice::Keyboard::TYPE, "Keyboard")
{
}


Keyboard::~Keyboard()
{
}


bool Keyboard::is_keyboard()
{
   return true;
}


} // namespace PhysicalInputDevice
} // namespace AllegroFlare



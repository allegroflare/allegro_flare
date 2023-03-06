

#include <AllegroFlare/PhysicalInputDevices/Keyboard.hpp>




namespace AllegroFlare
{
namespace PhysicalInputDevices
{


Keyboard::Keyboard()
   : AllegroFlare::PhysicalInputDevices::Base(AllegroFlare::PhysicalInputDevices::Keyboard::TYPE, "Keyboard")
{
}


Keyboard::~Keyboard()
{
}


bool Keyboard::is_keyboard()
{
   return true;
}


} // namespace PhysicalInputDevices
} // namespace AllegroFlare



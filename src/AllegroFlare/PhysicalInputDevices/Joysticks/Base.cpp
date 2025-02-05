

#include <AllegroFlare/PhysicalInputDevices/Joysticks/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace PhysicalInputDevices
{
namespace Joysticks
{


Base::Base()
   : AllegroFlare::PhysicalInputDevices::Base(AllegroFlare::PhysicalInputDevices::Joysticks::Base::TYPE, "Generic Joystick")
   , al_joystick(nullptr)
   , name("")
   , buttons({})
   , has_been_setup(false)
{
}


Base::~Base()
{
}


ALLEGRO_JOYSTICK* Base::get_al_joystick() const
{
   return al_joystick;
}


std::string Base::get_name() const
{
   return name;
}


std::map<uint32_t, std::string> Base::get_buttons() const
{
   return buttons;
}


void Base::set_al_joystick(ALLEGRO_JOYSTICK* al_joystick)
{
   if (!((!has_been_setup)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::PhysicalInputDevices::Joysticks::Base::set_al_joystick]: error: guard \"(!has_been_setup)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::PhysicalInputDevices::Joysticks::Base::set_al_joystick]: error: guard \"(!has_been_setup)\" not met");
   }
   this->al_joystick = al_joystick;
   return;
}

std::string Base::get_name()
{
   if (!(has_been_setup))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::PhysicalInputDevices::Joysticks::Base::get_name]: error: guard \"has_been_setup\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::PhysicalInputDevices::Joysticks::Base::get_name]: error: guard \"has_been_setup\" not met");
   }
   return name;
}

std::map<uint32_t, std::string> Base::get_buttons()
{
   if (!(has_been_setup))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::PhysicalInputDevices::Joysticks::Base::get_buttons]: error: guard \"has_been_setup\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::PhysicalInputDevices::Joysticks::Base::get_buttons]: error: guard \"has_been_setup\" not met");
   }
   return buttons;
}

bool Base::setup()
{
   if (!(al_joystick))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::PhysicalInputDevices::Joysticks::Base::setup]: error: guard \"al_joystick\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::PhysicalInputDevices::Joysticks::Base::setup]: error: guard \"al_joystick\" not met");
   }
   // Grab the joystick name
   name = al_get_joystick_name(al_joystick);

   // Grab the buttons and their names
   int num_buttons = al_get_joystick_num_buttons(al_joystick);
   for (int i=0; i<num_buttons; i++)
   {
      buttons[i] = al_get_joystick_button_name(al_joystick, i);
   }

   // TODO: consider the following data
   //al_get_joystick_active
   //al_get_joystick_name
   //al_get_joystick_stick_name
   //al_get_joystick_axis_name
   //al_get_joystick_button_name
   //al_get_joystick_stick_flags
   //al_get_joystick_num_sticks
   //al_get_joystick_num_axes
   //al_get_joystick_num_buttons
   //al_get_joystick_state

   has_been_setup = true;
   return true;
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



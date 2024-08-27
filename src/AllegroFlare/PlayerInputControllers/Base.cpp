

#include <AllegroFlare/PlayerInputControllers/Base.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace PlayerInputControllers
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


void Base::update_time_step(double time_now, double delta_time)
{
   // NOTE: This method should likely be renamed, it's equivelent to an update on a time step. It's processed
   // along with the update in the TileFPS/Screen update method, but before physics are applied on entities
   return;
}

void Base::on_activate()
{
   // Override this in the derived class
   // NOTE: Will be called when the controls are connected to be currently in use
   return;
}

void Base::on_deactivate()
{
   // Override this in the derived class
   // NOTE: Will be called when the controls are disconnected from being currently used
   return;
}

void Base::gameplay_suspend_func()
{
   // Override this in the derived class
   // NOTE: Called when the gameplay is suspended, for example for a pause, dialog, opening of a menu screen, etc
   return;
}

void Base::gameplay_resume_func()
{
   // Override this in the derived class
   // NOTE: Called when the gameplay is unsuspended, for example from a pause, closing dialog, closing of a menu
   // screen.
   return;
}

void Base::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   // Override this in the derived class
   return;
}

void Base::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   // Override this in the derived class
   return;
}

void Base::key_down_func(ALLEGRO_EVENT* ev)
{
   // Override this in the derived class
   return;
}

void Base::key_up_func(ALLEGRO_EVENT* ev)
{
   // Override this in the derived class
   return;
}

void Base::key_char_func(ALLEGRO_EVENT* ev)
{
   // Override this in the derived class
   return;
}

void Base::joy_axis_func(ALLEGRO_EVENT* ev)
{
   // Override this in the derived class
   return;
}

void Base::mouse_down_func(ALLEGRO_EVENT* ev)
{
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::PlayerInputControllers::Base::mouse_down_func]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::PlayerInputControllers::Base::mouse_down_func]: error: guard \"ev\" not met");
   }
   // Override this in the derived class
   return;
}

void Base::mouse_axes_func(ALLEGRO_EVENT* ev)
{
   // Override this in the derived class
   return;
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace PlayerInputControllers
} // namespace AllegroFlare



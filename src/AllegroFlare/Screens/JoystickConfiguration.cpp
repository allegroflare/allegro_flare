

#include <AllegroFlare/Screens/JoystickConfiguration.hpp>

#include <AllegroFlare/VirtualController.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


JoystickConfiguration::JoystickConfiguration(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, std::size_t surface_width, std::size_t surface_height)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::JoystickConfiguration::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , surface_width(surface_width)
   , surface_height(surface_height)
   , joystick_configuration_element()
   , initialized(false)
{
}


JoystickConfiguration::~JoystickConfiguration()
{
}


void JoystickConfiguration::set_surface_width(std::size_t surface_width)
{
   this->surface_width = surface_width;
}


void JoystickConfiguration::set_surface_height(std::size_t surface_height)
{
   this->surface_height = surface_height;
}


std::size_t JoystickConfiguration::get_surface_width() const
{
   return surface_width;
}


std::size_t JoystickConfiguration::get_surface_height() const
{
   return surface_height;
}


AllegroFlare::Elements::JoystickConfigurationList &JoystickConfiguration::get_joystick_configuration_element_ref()
{
   return joystick_configuration_element;
}


void JoystickConfiguration::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void JoystickConfiguration::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void JoystickConfiguration::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   joystick_configuration_element.set_font_bin(font_bin);
   this->font_bin = font_bin;
   return;
}

void JoystickConfiguration::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::initialize: error: guard \"font_bin\" not met");
   }
   joystick_configuration_element.initialize();
   initialized = true;
   return;
}

void JoystickConfiguration::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::on_activate: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void JoystickConfiguration::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::on_deactivate: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void JoystickConfiguration::update()
{
   joystick_configuration_element.update();
   return;
}

void JoystickConfiguration::render()
{
   joystick_configuration_element.render();
   return;
}

void JoystickConfiguration::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::primary_timer_func: error: guard \"initialized\" not met");
   }
   update();
   render();
   return;
}

void JoystickConfiguration::virtual_control_button_up_func(int player_num, int button_num, bool repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::virtual_control_button_up_func: error: guard \"initialized\" not met");
   }
   // TODO: consider if this function needs implementing
   return;
}

void JoystickConfiguration::virtual_control_button_down_func(int player_num, int button_num, bool repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   // TODO: Have this function account for state of the joystick_configuration_element
   switch(button_num)
   {
      case AllegroFlare::VirtualController::BUTTON_UP:
         joystick_configuration_element.move_cursor_up();
      break;

      case AllegroFlare::VirtualController::BUTTON_DOWN:
         joystick_configuration_element.move_cursor_down();
      break;
   }
   return;
}

void JoystickConfiguration::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[JoystickConfiguration::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("JoystickConfiguration::virtual_control_axis_change_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}


} // namespace Screens
} // namespace AllegroFlare



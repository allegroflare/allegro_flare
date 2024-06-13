

#include <AllegroFlare/Screens/InputDeviceConfiguration.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


InputDeviceConfiguration::InputDeviceConfiguration(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, std::size_t surface_width, std::size_t surface_height, AllegroFlare::InputDevicesList* input_devices_list)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::InputDeviceConfiguration::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , surface_width(surface_width)
   , surface_height(surface_height)
   , on_exit_callback_func()
   , on_exit_callback_func_user_data(nullptr)
   , input_devices_list(input_devices_list)
   , input_devices_list_element()
   , input_device_configuration_element()
   , initialized(false)
{
}


InputDeviceConfiguration::~InputDeviceConfiguration()
{
}


void InputDeviceConfiguration::set_surface_width(std::size_t surface_width)
{
   this->surface_width = surface_width;
}


void InputDeviceConfiguration::set_surface_height(std::size_t surface_height)
{
   this->surface_height = surface_height;
}


void InputDeviceConfiguration::set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::InputDeviceConfiguration*, void*)> on_exit_callback_func)
{
   this->on_exit_callback_func = on_exit_callback_func;
}


void InputDeviceConfiguration::set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data)
{
   this->on_exit_callback_func_user_data = on_exit_callback_func_user_data;
}


std::size_t InputDeviceConfiguration::get_surface_width() const
{
   return surface_width;
}


std::size_t InputDeviceConfiguration::get_surface_height() const
{
   return surface_height;
}


std::function<void(AllegroFlare::Screens::InputDeviceConfiguration*, void*)> InputDeviceConfiguration::get_on_exit_callback_func() const
{
   return on_exit_callback_func;
}


void* InputDeviceConfiguration::get_on_exit_callback_func_user_data() const
{
   return on_exit_callback_func_user_data;
}


AllegroFlare::Elements::InputDevicesList &InputDeviceConfiguration::get_input_devices_list_element_ref()
{
   return input_devices_list_element;
}


AllegroFlare::Elements::InputDeviceConfigurationList &InputDeviceConfiguration::get_input_device_configuration_element_ref()
{
   return input_device_configuration_element;
}


void InputDeviceConfiguration::compile_assertions()
{
   static_assert(sizeof(TYPE) > 0); // That's fun :)
   return;
}

void InputDeviceConfiguration::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::set_event_emitter]: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void InputDeviceConfiguration::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::set_bitmap_bin]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void InputDeviceConfiguration::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   input_device_configuration_element.set_font_bin(font_bin);
   input_devices_list_element.set_font_bin(font_bin);
   this->font_bin = font_bin;
   return;
}

void InputDeviceConfiguration::set_input_devices_list(AllegroFlare::InputDevicesList* input_devices_list)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::set_input_devices_list]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::set_input_devices_list]: error: guard \"(!initialized)\" not met");
   }
   this->input_devices_list = input_devices_list;
   return;
}

void InputDeviceConfiguration::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::initialize]: error: guard \"font_bin\" not met");
   }
   input_device_configuration_element.initialize();
   input_devices_list_element.initialize();

   initialized = true;
   return;
}

void InputDeviceConfiguration::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::on_activate]: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void InputDeviceConfiguration::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::on_deactivate]: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void InputDeviceConfiguration::update()
{
   input_device_configuration_element.update();
   return;
}

void InputDeviceConfiguration::render()
{
   input_device_configuration_element.render();
   return;
}

void InputDeviceConfiguration::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::primary_timer_func]: error: guard \"initialized\" not met");
   }
   update();
   render();
   return;
}

void InputDeviceConfiguration::call_on_exit_callback()
{
   // TODO: Test this callback
   if (on_exit_callback_func) on_exit_callback_func(this, on_exit_callback_func_user_data);
   return;
}

void InputDeviceConfiguration::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::virtual_control_button_up_func]: error: guard \"initialized\" not met");
   }
   // TODO: consider if this function needs implementing
   return;
}

void InputDeviceConfiguration::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   // TODO: Have this function account for state of the input_device_configuration_element
   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP:
         input_device_configuration_element.move_cursor_up();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN:
         input_device_configuration_element.move_cursor_down();
      break;

      default:
         call_on_exit_callback(); // TODO: Set conditions when then is permitted and/or blocked (for example, when
                                  // in the middle of remapping a device
      break;
   }
   return;
}

void InputDeviceConfiguration::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::InputDeviceConfiguration::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::InputDeviceConfiguration::virtual_control_axis_change_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}


} // namespace Screens
} // namespace AllegroFlare



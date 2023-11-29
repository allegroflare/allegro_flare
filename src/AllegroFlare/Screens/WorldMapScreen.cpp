

#include <AllegroFlare/Screens/WorldMapScreen.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


WorldMapScreen::WorldMapScreen(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::WorldMapScreen::TYPE)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , map_viewer({})
   , on_exit_callback_func()
   , on_exit_callback_func_user_data(nullptr)
   , on_activate_callback_func()
   , on_activate_callback_func_user_data(nullptr)
   , initialized(false)
{
}


WorldMapScreen::~WorldMapScreen()
{
}


void WorldMapScreen::set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::WorldMapScreen*, void*)> on_exit_callback_func)
{
   this->on_exit_callback_func = on_exit_callback_func;
}


void WorldMapScreen::set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data)
{
   this->on_exit_callback_func_user_data = on_exit_callback_func_user_data;
}


void WorldMapScreen::set_on_activate_callback_func(std::function<void(AllegroFlare::Screens::WorldMapScreen*, void*)> on_activate_callback_func)
{
   this->on_activate_callback_func = on_activate_callback_func;
}


void WorldMapScreen::set_on_activate_callback_func_user_data(void* on_activate_callback_func_user_data)
{
   this->on_activate_callback_func_user_data = on_activate_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::WorldMapScreen*, void*)> WorldMapScreen::get_on_exit_callback_func() const
{
   return on_exit_callback_func;
}


void* WorldMapScreen::get_on_exit_callback_func_user_data() const
{
   return on_exit_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::WorldMapScreen*, void*)> WorldMapScreen::get_on_activate_callback_func() const
{
   return on_activate_callback_func;
}


void* WorldMapScreen::get_on_activate_callback_func_user_data() const
{
   return on_activate_callback_func_user_data;
}


void WorldMapScreen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   map_viewer.set_bitmap_bin(bitmap_bin);
   return;
}

void WorldMapScreen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   map_viewer.set_font_bin(font_bin);
   return;
}

void WorldMapScreen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::initialize: error: guard \"font_bin\" not met");
   }
   initialized = true;

   map_viewer.set_bitmap_bin(bitmap_bin);
   map_viewer.set_font_bin(font_bin);
   map_viewer.initialize();
   //crime_summary.set_map(&map);

   return;
}

void WorldMapScreen::set_map(AllegroFlare::WorldMaps::Maps::Basic* map)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::set_map]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::set_map: error: guard \"bitmap_bin\" not met");
   }
   map_viewer.set_map(map);
   return;
}

void WorldMapScreen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::on_activate: error: guard \"initialized\" not met");
   }
   map_viewer.on_switch_in();
   //emit_event_to_update_input_hints_bar(); // Requires event_emitter
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void WorldMapScreen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::on_deactivate: error: guard \"initialized\" not met");
   }
   map_viewer.on_switch_out();
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void WorldMapScreen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::primary_timer_func: error: guard \"initialized\" not met");
   }
   map_viewer.update();
   map_viewer.render();
   return;
}

void WorldMapScreen::activate_at_cursor()
{
   if (on_activate_callback_func) on_activate_callback_func(this, on_activate_callback_func_user_data);
   return;
}

void WorldMapScreen::activate_exit_screen()
{
   if (on_exit_callback_func) on_exit_callback_func(this, on_exit_callback_func_user_data);
   return;
}

void WorldMapScreen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::virtual_control_button_up_func: error: guard \"initialized\" not met");
   }
   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP:
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN:
         map_viewer.unset_cursor_moving_vertical();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT:
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT:
         map_viewer.unset_cursor_moving_horizontal();
      break;
   }
   return;
}

void WorldMapScreen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   //if (mode != MODE_USING_VIRTUAL_CONTROLS) return;

   // TODO: validate VirtualControllers::GenericController type

   switch(virtual_controller_button_num)
   {
      case AllegroFlare::VirtualControllers::GenericController::BUTTON_UP:
         map_viewer.set_cursor_moving_up();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN:
         map_viewer.set_cursor_moving_down();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT:
         map_viewer.set_cursor_moving_left();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT:
         map_viewer.set_cursor_moving_right();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT_BUMPER:
         map_viewer.step_zoom_in();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT_BUMPER:
         map_viewer.step_zoom_out();
      break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_A: {
         activate_at_cursor();
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_B: {
         map_viewer.move_cursor_to_origin_or_primary_point_of_interest();
      } break;

      case AllegroFlare::VirtualControllers::GenericController::BUTTON_X:
         activate_exit_screen();
      break;
   }

   return;
}

void WorldMapScreen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WorldMapScreen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WorldMapScreen::virtual_control_axis_change_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}


} // namespace Screens
} // namespace AllegroFlare



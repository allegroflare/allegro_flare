

#include <AllegroFlare/Screens/WorldMapScreen.hpp>

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
   , initialized(false)
{
}


WorldMapScreen::~WorldMapScreen()
{
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
   //emit_event_to_update_input_hints_bar();
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
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void WorldMapScreen::update()
{
   return;
}

void WorldMapScreen::render()
{
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
   update();
   render();
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
   // TODO: this function
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
   // TODO: this function
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





#include <AllegroFlare/Screens/LevelSelectScreen.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


LevelSelectScreen::LevelSelectScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::LevelSelectScreen::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , level_select_element()
   , initialized(false)
{
}


LevelSelectScreen::~LevelSelectScreen()
{
}


AllegroFlare::Elements::LevelSelect &LevelSelectScreen::get_level_select_element_ref()
{
   return level_select_element;
}


void LevelSelectScreen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void LevelSelectScreen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void LevelSelectScreen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void LevelSelectScreen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::set_model_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::set_model_bin: error: guard \"(!initialized)\" not met");
   }
   this->model_bin = model_bin;
   return;
}

void LevelSelectScreen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::initialize: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::initialize: error: guard \"model_bin\" not met");
   }
   initialized = true;

   level_select_element.set_event_emitter(event_emitter);
   level_select_element.set_font_bin(font_bin);

   return;
}

void LevelSelectScreen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::on_activate: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void LevelSelectScreen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::on_deactivate: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void LevelSelectScreen::update()
{
   return;
}

void LevelSelectScreen::render()
{
   level_select_element.render();
   return;
}

void LevelSelectScreen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::primary_timer_func: error: guard \"initialized\" not met");
   }
   update();
   render();
   return;
}

void LevelSelectScreen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::virtual_control_button_up_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void LevelSelectScreen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   //if (!processing_user_input()) return;

   //if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_UP) move_cursor_up();
   //if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_DOWN) move_cursor_down();
   //if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_A
      //|| virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_MENU
      //)
   //{
      //select_menu_option();
   //}

   return;
}

void LevelSelectScreen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::virtual_control_axis_change_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}


} // namespace Screens
} // namespace AllegroFlare



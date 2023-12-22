

#include <AllegroFlare/Screens/LevelSelectScreen.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


LevelSelectScreen::LevelSelectScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::LevelSelectScreen::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , level_select_element()
   , on_menu_choice_callback_func()
   , on_menu_choice_callback_func_user_data(nullptr)
   , initialized(false)
{
}


LevelSelectScreen::~LevelSelectScreen()
{
}


void LevelSelectScreen::set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Screens::LevelSelectScreen*, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void LevelSelectScreen::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


std::function<void(AllegroFlare::Screens::LevelSelectScreen*, void*)> LevelSelectScreen::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* LevelSelectScreen::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
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

void LevelSelectScreen::set_levels_list(std::vector<std::pair<std::string, std::string>> levels_list)
{
   level_select_element.set_levels_list(levels_list);
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
   initialized = true;

   level_select_element.set_event_emitter(event_emitter);
   level_select_element.set_font_bin(font_bin);
   level_select_element.set_on_menu_choice_callback_func([this](AllegroFlare::Elements::LevelSelect*, void*){
      if (on_menu_choice_callback_func)
         on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
   });

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
   // TODO: emit_event_to_update_input_hints_bar();
   // TODO: emit_show_and_size_input_hints_bar_event();

   // TODO: Test the calling and error message response here in this "submit_on_activate_if_empty" block
   bool submit_on_activate_if_empty = true;
   if (submit_on_activate_if_empty && level_select_element.list_is_empty())
   {
      if (!on_menu_choice_callback_func)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Screens::LevelSelectScreen",
            "\"submit_on_activate_if_empty\" is set to true, thus expecting an \"on_menu_choice_callback_func\" "
               " to be present but it is not."
         );
      }

      // TODO: Add boolean option to supress this message
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Screens::LevelSelectScreen",
         "\"submit_on_activate_if_empty\" is true, so now calling \"on_menu_choice_callback_func\"."
      );

      on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
   }
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
   // TODO: emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void LevelSelectScreen::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::update: error: guard \"initialized\" not met");
   }
   return;
}

void LevelSelectScreen::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::render: error: guard \"initialized\" not met");
   }
   level_select_element.render();
   return;
}

void LevelSelectScreen::activate_selected_menu_option()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::activate_selected_menu_option]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::activate_selected_menu_option: error: guard \"initialized\" not met");
   }
   level_select_element.activate_selected_menu_option();
   return;
}

std::string LevelSelectScreen::infer_current_menu_option_value()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[LevelSelectScreen::infer_current_menu_option_value]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("LevelSelectScreen::infer_current_menu_option_value: error: guard \"initialized\" not met");
   }
   return level_select_element.infer_current_menu_option_value();
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
   // TODO: Confirm usage of VirtualControllers::GenericController

   switch(virtual_controller_button_num)
   {
      case VirtualControllers::GenericController::BUTTON_UP: {
         level_select_element.move_cursor_up();
      } break;

      case VirtualControllers::GenericController::BUTTON_DOWN: {
         level_select_element.move_cursor_down();
      } break;

      case VirtualControllers::GenericController::BUTTON_LEFT: {
         level_select_element.move_cursor_left();
      } break;

      case VirtualControllers::GenericController::BUTTON_RIGHT: {
         level_select_element.move_cursor_right();
      } break;

      case VirtualControllers::GenericController::BUTTON_MENU:
      case VirtualControllers::GenericController::BUTTON_A: {
         activate_selected_menu_option();
      } break;
   }

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



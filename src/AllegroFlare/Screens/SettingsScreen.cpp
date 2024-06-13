

#include <AllegroFlare/Screens/SettingsScreen.hpp>

#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


SettingsScreen::SettingsScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin)
   : AllegroFlare::Screens::Base(AllegroFlare::Screens::SettingsScreen::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , on_exit_callback_func()
   , on_exit_callback_func_user_data(nullptr)
   , surface_width(1920)
   , surface_height(1080)
   , initialized(false)
{
}


SettingsScreen::~SettingsScreen()
{
}


void SettingsScreen::set_on_exit_callback_func(std::function<void(AllegroFlare::Screens::SettingsScreen*, void*)> on_exit_callback_func)
{
   this->on_exit_callback_func = on_exit_callback_func;
}


void SettingsScreen::set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data)
{
   this->on_exit_callback_func_user_data = on_exit_callback_func_user_data;
}


void SettingsScreen::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


std::function<void(AllegroFlare::Screens::SettingsScreen*, void*)> SettingsScreen::get_on_exit_callback_func() const
{
   return on_exit_callback_func;
}


void* SettingsScreen::get_on_exit_callback_func_user_data() const
{
   return on_exit_callback_func_user_data;
}


int SettingsScreen::get_surface_width() const
{
   return surface_width;
}


int SettingsScreen::get_surface_height() const
{
   return surface_height;
}


void SettingsScreen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::set_event_emitter]: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void SettingsScreen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::set_bitmap_bin]: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void SettingsScreen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::set_font_bin]: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void SettingsScreen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::set_model_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::set_model_bin]: error: guard \"(!initialized)\" not met");
   }
   this->model_bin = model_bin;
   return;
   return;
}

void SettingsScreen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::initialize]: error: guard \"model_bin\" not met");
   }
   initialized = true;
   return;
}

void SettingsScreen::exit_screen()
{
   if (!on_exit_callback_func)
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Screens::SettingsScreen::exit_screen",
         "Expecting an \"on_exit_callback_func\" to be present, but it is not."
      );
   }

   on_exit_callback_func(this, on_exit_callback_func_user_data);

   return;
}

void SettingsScreen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::on_activate]: error: guard \"initialized\" not met");
   }
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void SettingsScreen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::on_deactivate]: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void SettingsScreen::update()
{
   return;
}

void SettingsScreen::render()
{
   ALLEGRO_FONT *heading_font = obtain_heading_font();
   ALLEGRO_FONT *text_font = obtain_text_font();
   int text_font_line_height = al_get_font_line_height(text_font);

   // Draw the heading
   al_draw_text(
      heading_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      surface_width/2,
      surface_height/2-100,
      ALLEGRO_ALIGN_CENTER,
      "Settings"
   );

   // Draw the placeholder text
   al_draw_text(
      text_font,
      ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5},
      surface_width/2,
      surface_height/2,
      ALLEGRO_ALIGN_CENTER,
      "There are no settings to configure."
   );
   al_draw_text(
      text_font,
      ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5},
      surface_width/2,
      surface_height/2+text_font_line_height,
      ALLEGRO_ALIGN_CENTER,
      "Press any key to continue"
   );
   return;
}

void SettingsScreen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::primary_timer_func]: error: guard \"initialized\" not met");
   }
   update();
   render();
   return;
}

void SettingsScreen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::virtual_control_button_up_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void SettingsScreen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   exit_screen();
   return;
}

void SettingsScreen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::virtual_control_axis_change_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

ALLEGRO_FONT* SettingsScreen::obtain_heading_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::obtain_heading_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::obtain_heading_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -52");
}

ALLEGRO_FONT* SettingsScreen::obtain_text_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Screens::SettingsScreen::obtain_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Screens::SettingsScreen::obtain_text_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -32");
}


} // namespace Screens
} // namespace AllegroFlare



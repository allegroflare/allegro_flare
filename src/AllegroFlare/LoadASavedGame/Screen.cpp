

#include <AllegroFlare/LoadASavedGame/Screen.hpp>

#include <AllegroFlare/LoadASavedGame/SaveSlotRenderer.hpp>
#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace LoadASavedGame
{


Screen::Screen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin)
   : AllegroFlare::Screens::Base(AllegroFlare::LoadASavedGame::Screen::TYPE)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , save_slots({})
   , cursor_position(0)
   , on_menu_choice_callback_func({})
   , on_menu_choice_callback_func_user_data(nullptr)
   , on_exit_callback_func({})
   , on_exit_callback_func_user_data(nullptr)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_on_menu_choice_callback_func(std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void Screen::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


void Screen::set_on_exit_callback_func(std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> on_exit_callback_func)
{
   this->on_exit_callback_func = on_exit_callback_func;
}


void Screen::set_on_exit_callback_func_user_data(void* on_exit_callback_func_user_data)
{
   this->on_exit_callback_func_user_data = on_exit_callback_func_user_data;
}


std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> Screen::get_save_slots() const
{
   return save_slots;
}


std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> Screen::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* Screen::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
}


std::function<void(AllegroFlare::LoadASavedGame::Screen*, void*)> Screen::get_on_exit_callback_func() const
{
   return on_exit_callback_func;
}


void* Screen::get_on_exit_callback_func_user_data() const
{
   return on_exit_callback_func_user_data;
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_font_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_font_bin: error: guard \"(!initialized)\" not met");
   }
   this->font_bin = font_bin;
   return;
}

void Screen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_model_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_model_bin: error: guard \"(!initialized)\" not met");
   }
   this->model_bin = model_bin;
   return;
}

void Screen::set_save_slots(std::vector<AllegroFlare::LoadASavedGame::SaveSlots::Base*> save_slots)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_save_slots]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_save_slots: error: guard \"(!initialized)\" not met");
   }
   this->save_slots = save_slots;
   cursor_position = 0;
   return;
}

void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"model_bin\" not met");
   }
   initialized = true;
   return;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_activate: error: guard \"initialized\" not met");
   }
   cursor_position = 0;
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_deactivate: error: guard \"initialized\" not met");
   }
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::move_cursor_up()
{
   if (save_slots.empty()) return;
   cursor_position--;
   if (cursor_position < 0) cursor_position += save_slots.size();
   return;
}

void Screen::move_cursor_down()
{
   if (save_slots.empty()) return;
   cursor_position++;
   if (cursor_position > save_slots.size()) cursor_position -= save_slots.size();
   return;
}

void Screen::exit_screen()
{
   // TODO: Test this method
   if (on_exit_callback_func)
   {
      on_exit_callback_func(this, on_exit_callback_func_user_data);
   }
   else
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::LoadASavedGame::Screen::exit_screen",
         "Expecting an \"on_exit_callback_func\" to be present, but it is not."
      );
   }

   return;
}

void Screen::activate_current_focused_menu_option()
{
   // TODO: Test this method
   if (on_menu_choice_callback_func)
   {
      on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
   }
   else
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::LoadASavedGame::Screen::activate_current_focused_menu_option",
         "Expecting an \"on_menu_choice_callback_func\" to be present, but it is not."
      );
   }
   return;
}

void Screen::select_current_focused_menu_option()
{
   // For now, do a direct call to activate the option
   select_current_focused_menu_option();
   return;
}

void Screen::update()
{
   return;
}

void Screen::render()
{
   render_title();
   render_save_slots();
   return;
}

void Screen::render_title()
{
   ALLEGRO_FONT *font = obtain_heading_font();
   float line_height = al_get_font_line_height(font);
   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, 1920/2, 260-line_height, ALLEGRO_ALIGN_CENTER, "Load a Saved Game");
   return;
}

void Screen::render_save_slots()
{
   float y_cursor = 400;
   float y_distance = 1080/6;
   int i=0;
   for (auto &save_slot : save_slots)
   {
      float x = 1920/2;
      float y = y_cursor + y_distance*i;
      // HERE: Continue on this
      AllegroFlare::LoadASavedGame::SaveSlotRenderer renderer;
      renderer.set_font_bin(font_bin);
      renderer.render(
         save_slot,
         x,
         y
      );
      i++;

      // If this is currently focused under the cursor, draw the cursor (for now)
      // TODO: Replace this with a more active cursor
      bool this_save_slot_is_focused = (i == cursor_position);
      if (this_save_slot_is_focused)
      {
         float slot_width = renderer.get_slot_width();
         float slot_h_width = slot_width/2;
         float slot_height = renderer.get_slot_height();
         float slot_h_height = slot_height/2;
         al_draw_rectangle(
            x-slot_h_width,
            y-slot_h_height,
            x+slot_h_width,
            y+slot_h_height,
            ALLEGRO_COLOR{1, 1, 1, 1},
            6.0
         );
      }
   }
   return;
}

void Screen::primary_timer_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::primary_timer_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::primary_timer_func: error: guard \"initialized\" not met");
   }
   update();
   render();
   return;
}

void Screen::key_char_func(ALLEGRO_EVENT* event)
{
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_char_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_char_func: error: guard \"event\" not met");
   }
   switch(event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
         move_cursor_up();
      break;

      case ALLEGRO_KEY_DOWN:
         move_cursor_down();
      break;

      case ALLEGRO_KEY_Q:
         exit_screen();
      break;

      case ALLEGRO_KEY_ENTER:
         select_current_focused_menu_option();
      break;
   }
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_axis_change_func: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

ALLEGRO_FONT* Screen::obtain_heading_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::obtain_heading_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::obtain_heading_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -46");
}

ALLEGRO_FONT* Screen::obtain_text_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::obtain_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::obtain_text_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -32");
}


} // namespace LoadASavedGame
} // namespace AllegroFlare



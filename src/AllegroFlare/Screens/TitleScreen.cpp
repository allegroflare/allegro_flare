

#include <AllegroFlare/Screens/TitleScreen.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Screens
{


TitleScreen::TitleScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, std::string title_text)
   : AllegroFlare::Screens::Base()
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , title_text(title_text)
   , menu_options({})
   , cursor_position(0)
   , initialized(false)
{
}


TitleScreen::~TitleScreen()
{
}


void TitleScreen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void TitleScreen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


std::string TitleScreen::get_title_text()
{
   return title_text;
}


bool TitleScreen::get_initialized()
{
   return initialized;
}


void TitleScreen::initialize()
{
   menu_options = { { "Start new game", "start_new_game" }, { "Exit", "exit_game" } };
   cursor_position = 0;
   initialized = true;
   return;
}

void TitleScreen::move_cursor_up()
{
   cursor_position++;
   if (cursor_position >= menu_options.size()) cursor_position = cursor_position % menu_options.size();
   return;
}

void TitleScreen::move_cursor_down()
{
   cursor_position--;
   if (cursor_position < 0) cursor_position += menu_options.size();
   return;
}

void TitleScreen::select_menu_option()
{
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "TitleScreen" << "::" << "select_menu_option" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string current_menu_option_value = infer_current_menu_option_value();

   // TODO: clarify this mapping so that it can be injected into the menu
   if (current_menu_option_value == "start_new_game") event_emitter->emit_event(ALLEGRO_FLARE_EVENT_START_NEW_GAME);
   else if (current_menu_option_value == "exit_game") event_emitter->emit_event(ALLEGRO_FLARE_EVENT_EXIT_GAME);
   else
   {
      std::string current_menu_option_label = infer_current_menu_option_label();
      std::stringstream ss;
      ss << "[AllegroFlare::Screens::TitleScreen::select_menu_option()] error: There is no consequential action "
            "assigned for the menu option value \"" << current_menu_option_value <<  "\".  Note this is "
            "the value for the menu item labeled \"" << current_menu_option_label << "\".";
      throw std::runtime_error(ss.str());
   }

   return;
}

void TitleScreen::primary_timer_func()
{
   render();
   return;
}

void TitleScreen::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "TitleScreen" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "TitleScreen" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(get_initialized()))
      {
         std::stringstream error_message;
         error_message << "TitleScreen" << "::" << "render" << ": error: " << "guard \"get_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   draw_title_text();
   draw_menu();
   return;
}

void TitleScreen::draw_title_text()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *title_font = obtain_title_font();
   int surface_width = 1920;
   int surface_height = 1080;
   al_draw_text(
      title_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      surface_width / 2,
      surface_height / 3,
      ALLEGRO_ALIGN_CENTER,
      get_title_text().c_str()
   );
   return;
}

void TitleScreen::draw_menu()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *menu_font = obtain_menu_font();
   int surface_width = 1920;
   int surface_height = 1080;
   float menu_item_vertical_spacing = (int)(al_get_font_line_height(menu_font) * 1.25f);
   int menu_item_num = 0;

   for (auto &menu_option : menu_options)
   {
      bool showing_cursor_on_this_option = false;
      if (menu_item_num == cursor_position) showing_cursor_on_this_option = true;

      std::string menu_item_text = std::get<0>(menu_option);
      al_draw_text(
         menu_font,
         ALLEGRO_COLOR{1, 1, 1, 1},
         surface_width / 2,
         surface_height / 2 + menu_item_vertical_spacing * menu_item_num,
         ALLEGRO_ALIGN_CENTER,
         menu_item_text.c_str()
      );

      if (showing_cursor_on_this_option)
      {
         float menu_item_text_width = al_get_text_width(menu_font, menu_item_text.c_str());
         al_draw_text(
            menu_font,
            ALLEGRO_COLOR{1, 1, 1, 1},
            surface_width / 2 - (menu_item_text_width * 0.5),
            surface_height / 2 + menu_item_vertical_spacing * menu_item_num,
            ALLEGRO_ALIGN_RIGHT,
            ">  "
         );
      }

      menu_item_num++;
   }
   return;
}

std::string TitleScreen::infer_current_menu_option_value()
{
   if (menu_options.empty()) return "";
   if (cursor_position < 0 || cursor_position >= menu_options.size())
   {
      throw std::runtime_error("[AllegroFlare/Screens/TitleScreen]: error: cursor_position is not in "
                               "a valid position to get the current menu choice's value.");
   }
   std::string current_menu_option_value = std::get<1>(menu_options[cursor_position]);
   return current_menu_option_value;
}

std::string TitleScreen::infer_current_menu_option_label()
{
   if (menu_options.empty()) return "";
   if (cursor_position < 0 || cursor_position >= menu_options.size())
   {
      throw std::runtime_error("[AllegroFlare/Screens/TitleScreen]: error: cursor_position is not in "
                               "a valid position to get the current menu choice's label.");
   }
   std::string current_menu_option_value = std::get<1>(menu_options[cursor_position]);
   return current_menu_option_value;
}

ALLEGRO_FONT* TitleScreen::obtain_title_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "TitleScreen" << "::" << "obtain_title_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -90");
}

ALLEGRO_FONT* TitleScreen::obtain_menu_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "TitleScreen" << "::" << "obtain_menu_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -56");
}

void TitleScreen::key_char_func(ALLEGRO_EVENT* event)
{
   switch(event->keyboard.keycode)
   {
      case ALLEGRO_KEY_UP:
        move_cursor_up();
      break;

      case ALLEGRO_KEY_DOWN:
        move_cursor_down();
      break;

      case ALLEGRO_KEY_ENTER:
        select_menu_option();
      break;
   }
   return;
}
} // namespace Screens
} // namespace AllegroFlare



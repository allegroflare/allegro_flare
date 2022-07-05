

#include <AllegroFlare/Screens/GameOverScreen.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/VirtualControls.hpp>


namespace AllegroFlare
{
namespace Screens
{


GameOverScreen::GameOverScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Screens::Base("GameOverScreen")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , menu_options({})
   , cursor_position(0)
   , initialized(false)
{
}


GameOverScreen::~GameOverScreen()
{
}


void GameOverScreen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void GameOverScreen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


bool GameOverScreen::get_initialized()
{
   return initialized;
}


void GameOverScreen::initialize()
{
   menu_options = { { "Try again", "try_again" }, { "Go to Title Screen", "start_title_screen" } };
   cursor_position = 0;
   initialized = true;
   return;
}

void GameOverScreen::move_cursor_up()
{
   cursor_position++;
   if (cursor_position >= menu_options.size()) cursor_position = cursor_position % menu_options.size();
   return;
}

void GameOverScreen::move_cursor_down()
{
   cursor_position--;
   if (cursor_position < 0) cursor_position += menu_options.size();
   return;
}

void GameOverScreen::select_menu_option()
{
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "GameOverScreen" << "::" << "select_menu_option" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::string current_menu_option_value = infer_current_menu_option_value();
   event_emitter->emit_game_event(current_menu_option_value);
   return;
}

void GameOverScreen::primary_timer_func()
{
   render();
   return;
}

void GameOverScreen::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "GameOverScreen" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "GameOverScreen" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(get_initialized()))
      {
         std::stringstream error_message;
         error_message << "GameOverScreen" << "::" << "render" << ": error: " << "guard \"get_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   draw_primary_text();
   draw_menu();
   return;
}

void GameOverScreen::draw_primary_text()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *title_font = obtain_title_font();
   float font_line_height = al_get_font_line_height(title_font);
   int surface_width = 1920;
   int surface_height = 1080;
   al_draw_text(
      title_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      surface_width / 2,
      surface_height / 2 - font_line_height*2,
      ALLEGRO_ALIGN_CENTER,
      "G     A     M     E         O     V     E     R"
   );
   return;
}

void GameOverScreen::draw_menu()
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

std::string GameOverScreen::infer_current_menu_option_value()
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

std::string GameOverScreen::infer_current_menu_option_label()
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

ALLEGRO_FONT* GameOverScreen::obtain_title_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "GameOverScreen" << "::" << "obtain_title_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -56");
}

ALLEGRO_FONT* GameOverScreen::obtain_menu_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "GameOverScreen" << "::" << "obtain_menu_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -48");
}

void GameOverScreen::virtual_control_button_down_func(int player_num, int button_num, bool is_repeat)
{
   if (button_num == VirtualControls::get_BUTTON_UP()) move_cursor_up();
   if (button_num == VirtualControls::get_BUTTON_DOWN()) move_cursor_down();
   if (button_num == VirtualControls::get_BUTTON_A()) select_menu_option();
}
} // namespace Screens
} // namespace AllegroFlare



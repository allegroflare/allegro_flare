

#include <AllegroFlare/Screens/GameWonScreen.hpp>

#include <AllegroFlare/VirtualControls.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


GameWonScreen::GameWonScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, std::string game_event_name_to_emit_on_submission)
   : AllegroFlare::Screens::Base("GameWonScreen")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , game_event_name_to_emit_on_submission(game_event_name_to_emit_on_submission)
{
}


GameWonScreen::~GameWonScreen()
{
}


void GameWonScreen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void GameWonScreen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void GameWonScreen::set_game_event_name_to_emit_on_submission(std::string game_event_name_to_emit_on_submission)
{
   this->game_event_name_to_emit_on_submission = game_event_name_to_emit_on_submission;
}


std::string GameWonScreen::get_game_event_name_to_emit_on_submission() const
{
   return game_event_name_to_emit_on_submission;
}


void GameWonScreen::primary_timer_func()
{
   render();
   return;
}

void GameWonScreen::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[GameWonScreen::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameWonScreen::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[GameWonScreen::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameWonScreen::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   draw_primary_text();
   draw_instruction_text();
   return;
}

void GameWonScreen::draw_primary_text()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *title_font = obtain_title_font();
   float font_line_height = al_get_font_line_height(title_font);
   int surface_width = 1920;
   int surface_height = 1080;
   al_draw_multiline_text(
      title_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      surface_width / 2,
      surface_height / 2 - font_line_height,
      surface_width,
      font_line_height,
      ALLEGRO_ALIGN_CENTER,
      "Y   O   U      W   I   N"
   );
   return;
}

void GameWonScreen::draw_instruction_text()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *title_font = obtain_instruction_font();
   float font_line_height = al_get_font_line_height(title_font);
   int surface_width = 1920;
   int surface_height = 1080;
   al_draw_multiline_text(
      title_font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      surface_width / 2,
      surface_height / 2 + font_line_height*2,
      surface_width,
      font_line_height,
      ALLEGRO_ALIGN_CENTER,
      "Press any button"
   );
   return;
}

ALLEGRO_FONT* GameWonScreen::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[GameWonScreen::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameWonScreen::obtain_title_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("DroidSans.ttf -80");
}

ALLEGRO_FONT* GameWonScreen::obtain_instruction_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[GameWonScreen::obtain_instruction_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameWonScreen::obtain_instruction_font: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("DroidSans.ttf -48");
}

void GameWonScreen::virtual_control_button_down_func(int player_num, int button_num, bool is_repeat)
{
   event_emitter->emit_game_event(game_event_name_to_emit_on_submission);
   //if (button_num == VirtualControls::BUTTON_UP) move_cursor_up();
   //if (button_num == VirtualControls::BUTTON_DOWN) move_cursor_down();
   //if (button_num == VirtualControls::BUTTON_A) select_menu_option();
}


} // namespace Screens
} // namespace AllegroFlare



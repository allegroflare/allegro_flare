

#include <AllegroFlare/Screens/GameWonScreen.hpp>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/EventNames.hpp>
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


GameWonScreen::GameWonScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Screens::Base()
   , event_emitter(event_emitter)
   , font_bin(font_bin)
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
         error_message << "GameWonScreen" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "GameWonScreen" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
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
      "Press any key"
   );
   return;
}

void GameWonScreen::return_to_title_screen()
{
   if (!(event_emitter))
      {
         std::stringstream error_message;
         error_message << "GameWonScreen" << "::" << "return_to_title_screen" << ": error: " << "guard \"event_emitter\" not met";
         throw std::runtime_error(error_message.str());
      }
   event_emitter->emit_event(ALLEGRO_FLARE_EVENT_START_TITLE_SCREEN);
   return;
}

ALLEGRO_FONT* GameWonScreen::obtain_title_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "GameWonScreen" << "::" << "obtain_title_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -80");
}

ALLEGRO_FONT* GameWonScreen::obtain_instruction_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "GameWonScreen" << "::" << "obtain_instruction_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return font_bin->auto_get("DroidSans.ttf -48");
}

void GameWonScreen::key_char_func(ALLEGRO_EVENT* event)
{
   // on any keypress:
   return_to_title_screen();
   return;
}
} // namespace Screens
} // namespace AllegroFlare



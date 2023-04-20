

#include <AllegroFlare/Screens/GameWonScreen.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


std::string GameWonScreen::DEFAULT_TITLE_TEXT = "Y   O   U      W   I   N";


std::string GameWonScreen::DEFAULT_INSTRUCTION_TEXT = "Press any button";


GameWonScreen::GameWonScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, std::string title_text, AllegroFlare::Elements::Backgrounds::Base* background, std::string title_font_name, int title_font_size, std::string instruction_text, std::string instruction_font_name, int instruction_font_size, std::string game_event_name_to_emit_on_submission)
   : AllegroFlare::Screens::Base("GameWonScreen")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , title_text(title_text)
   , background(background)
   , title_font_name(title_font_name)
   , title_font_size(title_font_size)
   , instruction_text(instruction_text)
   , instruction_font_name(instruction_font_name)
   , instruction_font_size(instruction_font_size)
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


void GameWonScreen::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void GameWonScreen::set_background(AllegroFlare::Elements::Backgrounds::Base* background)
{
   this->background = background;
}


void GameWonScreen::set_title_font_name(std::string title_font_name)
{
   this->title_font_name = title_font_name;
}


void GameWonScreen::set_title_font_size(int title_font_size)
{
   this->title_font_size = title_font_size;
}


void GameWonScreen::set_instruction_text(std::string instruction_text)
{
   this->instruction_text = instruction_text;
}


void GameWonScreen::set_instruction_font_name(std::string instruction_font_name)
{
   this->instruction_font_name = instruction_font_name;
}


void GameWonScreen::set_instruction_font_size(int instruction_font_size)
{
   this->instruction_font_size = instruction_font_size;
}


void GameWonScreen::set_game_event_name_to_emit_on_submission(std::string game_event_name_to_emit_on_submission)
{
   this->game_event_name_to_emit_on_submission = game_event_name_to_emit_on_submission;
}


AllegroFlare::Elements::Backgrounds::Base* GameWonScreen::get_background() const
{
   return background;
}


std::string GameWonScreen::get_title_font_name() const
{
   return title_font_name;
}


int GameWonScreen::get_title_font_size() const
{
   return title_font_size;
}


std::string GameWonScreen::get_instruction_font_name() const
{
   return instruction_font_name;
}


int GameWonScreen::get_instruction_font_size() const
{
   return instruction_font_size;
}


std::string GameWonScreen::get_game_event_name_to_emit_on_submission() const
{
   return game_event_name_to_emit_on_submission;
}


void GameWonScreen::on_activate()
{
   if (background) background->activate();
   return;
}

void GameWonScreen::on_deactivate()
{
   if (background) background->deactivate();
   return;
}

void GameWonScreen::primary_timer_func()
{
   if (background) background->update();
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
   if (background) background->render();
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
      title_text.c_str()
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
      instruction_text.c_str()
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
   std::stringstream title_font_identifier;
   title_font_identifier << title_font_name << " " << title_font_size;
   return font_bin->auto_get(title_font_identifier.str());
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
   std::stringstream instruction_font_identifier;
   instruction_font_identifier << instruction_font_name << " " << instruction_font_size;
   return font_bin->auto_get(instruction_font_identifier.str());
}

void GameWonScreen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   event_emitter->emit_game_event(game_event_name_to_emit_on_submission);
}


} // namespace Screens
} // namespace AllegroFlare



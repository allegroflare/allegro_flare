

#include <AllegroFlare/Screens/GameOverScreen.hpp>

#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


std::string GameOverScreen::DEFAULT_TITLE_TEXT = "G   A   M   E      O   V   E   R";


std::vector<std::pair<std::string, std::string>> GameOverScreen::DEFAULT_MENU_OPTIONS = { { "Try again", "try_again" }, { "Go to Title Screen", "start_title_screen" } };


GameOverScreen::GameOverScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, std::string title_text, AllegroFlare::Elements::Backgrounds::Base* background, std::string title_font_name, int title_font_size, std::string menu_font_name, int menu_font_size)
   : AllegroFlare::Screens::Base("GameOverScreen")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , title_text(title_text)
   , menu_options(DEFAULT_MENU_OPTIONS)
   , background(background)
   , cursor_position(0)
   , title_font_name(title_font_name)
   , title_font_size(title_font_size)
   , menu_font_name(menu_font_name)
   , menu_font_size(menu_font_size)
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


void GameOverScreen::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void GameOverScreen::set_background(AllegroFlare::Elements::Backgrounds::Base* background)
{
   this->background = background;
}


void GameOverScreen::set_title_font_name(std::string title_font_name)
{
   this->title_font_name = title_font_name;
}


void GameOverScreen::set_title_font_size(int title_font_size)
{
   this->title_font_size = title_font_size;
}


void GameOverScreen::set_menu_font_name(std::string menu_font_name)
{
   this->menu_font_name = menu_font_name;
}


void GameOverScreen::set_menu_font_size(int menu_font_size)
{
   this->menu_font_size = menu_font_size;
}


AllegroFlare::Elements::Backgrounds::Base* GameOverScreen::get_background() const
{
   return background;
}


std::string GameOverScreen::get_title_font_name() const
{
   return title_font_name;
}


int GameOverScreen::get_title_font_size() const
{
   return title_font_size;
}


std::string GameOverScreen::get_menu_font_name() const
{
   return menu_font_name;
}


int GameOverScreen::get_menu_font_size() const
{
   return menu_font_size;
}


bool GameOverScreen::get_initialized() const
{
   return initialized;
}


void GameOverScreen::set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options)
{
   if (!((!menu_options.empty())))
   {
      std::stringstream error_message;
      error_message << "[GameOverScreen::set_menu_options]: error: guard \"(!menu_options.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameOverScreen::set_menu_options: error: guard \"(!menu_options.empty())\" not met");
   }
   // TODO: add tests for this feature
   // TODO: Validate menu options (unique labels, non-empty datas)
   this->menu_options = menu_options;
   cursor_position = 0;
   return;
}

void GameOverScreen::initialize()
{
   menu_options = { { "Try again", "try_again" }, { "Go to Title Screen", "start_title_screen" } };
   cursor_position = 0;
   initialized = true;
   return;
}

void GameOverScreen::on_activate()
{
   if (background) background->activate();
   return;
}

void GameOverScreen::on_deactivate()
{
   if (background) background->activate();
   return;
}

void GameOverScreen::move_cursor_up()
{
   cursor_position--;
   if (cursor_position < 0) cursor_position += menu_options.size();
   return;
}

void GameOverScreen::move_cursor_down()
{
   cursor_position++;
   if (cursor_position >= menu_options.size()) cursor_position = cursor_position % menu_options.size();
   return;
}

void GameOverScreen::select_menu_option()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[GameOverScreen::select_menu_option]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameOverScreen::select_menu_option: error: guard \"event_emitter\" not met");
   }
   std::string current_menu_option_value = infer_current_menu_option_value();
   event_emitter->emit_game_event(current_menu_option_value);
   return;
}

void GameOverScreen::primary_timer_func()
{
   if (background) background->update();
   render();
   return;
}

void GameOverScreen::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[GameOverScreen::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameOverScreen::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[GameOverScreen::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameOverScreen::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[GameOverScreen::render]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameOverScreen::render: error: guard \"get_initialized()\" not met");
   }
   if (background) background->render();
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
      surface_height / 2 - font_line_height,
      ALLEGRO_ALIGN_CENTER,
      title_text.c_str()
   );
   return;
}

void GameOverScreen::draw_menu()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *menu_font = obtain_menu_font();
   float font_line_height = al_get_font_line_height(menu_font);
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
         surface_height / 2 + menu_item_vertical_spacing * menu_item_num + font_line_height * 2,
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
            surface_height / 2 + menu_item_vertical_spacing * menu_item_num + font_line_height * 2,
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
      error_message << "[GameOverScreen::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameOverScreen::obtain_title_font: error: guard \"font_bin\" not met");
   }
   std::stringstream title_font_identifier;
   title_font_identifier << title_font_name << " " << title_font_size;
   return font_bin->auto_get(title_font_identifier.str());
}

ALLEGRO_FONT* GameOverScreen::obtain_menu_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[GameOverScreen::obtain_menu_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("GameOverScreen::obtain_menu_font: error: guard \"font_bin\" not met");
   }
   std::stringstream menu_font_identifier;
   menu_font_identifier << menu_font_name << " " << menu_font_size;
   return font_bin->auto_get(menu_font_identifier.str());
}

void GameOverScreen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_UP) move_cursor_up();
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_DOWN) move_cursor_down();
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_A
      || virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_MENU
      )
   {
      select_menu_option();
   }
}


} // namespace Screens
} // namespace AllegroFlare





#include <AllegroFlare/Screens/TitleScreen.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/VirtualControls.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


TitleScreen::TitleScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, std::string title_text, std::string copyright_text, std::string background_bitmap_name, std::string title_bitmap_name, std::string font_name, ALLEGRO_COLOR title_text_color, ALLEGRO_COLOR menu_text_color, ALLEGRO_COLOR menu_selector_color, ALLEGRO_COLOR menu_selected_text_color, ALLEGRO_COLOR copyright_text_color, int title_font_size, int menu_font_size, int copyright_font_size)
   : AllegroFlare::Screens::Base("TitleScreen")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , title_text(title_text)
   , copyright_text(copyright_text)
   , background_bitmap_name(background_bitmap_name)
   , title_bitmap_name(title_bitmap_name)
   , font_name(font_name)
   , title_text_color(title_text_color)
   , menu_text_color(menu_text_color)
   , menu_selector_color(menu_selector_color)
   , menu_selected_text_color(menu_selected_text_color)
   , copyright_text_color(copyright_text_color)
   , title_font_size(title_font_size)
   , menu_font_size(menu_font_size)
   , copyright_font_size(copyright_font_size)
   , menu_options(build_default_menu_options())
   , menu_position_x(1920 / 2)
   , menu_position_y(1080 / 2)
   , cursor_position(0)
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


void TitleScreen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void TitleScreen::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void TitleScreen::set_copyright_text(std::string copyright_text)
{
   this->copyright_text = copyright_text;
}


void TitleScreen::set_background_bitmap_name(std::string background_bitmap_name)
{
   this->background_bitmap_name = background_bitmap_name;
}


void TitleScreen::set_title_bitmap_name(std::string title_bitmap_name)
{
   this->title_bitmap_name = title_bitmap_name;
}


void TitleScreen::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void TitleScreen::set_title_text_color(ALLEGRO_COLOR title_text_color)
{
   this->title_text_color = title_text_color;
}


void TitleScreen::set_menu_text_color(ALLEGRO_COLOR menu_text_color)
{
   this->menu_text_color = menu_text_color;
}


void TitleScreen::set_menu_selector_color(ALLEGRO_COLOR menu_selector_color)
{
   this->menu_selector_color = menu_selector_color;
}


void TitleScreen::set_menu_selected_text_color(ALLEGRO_COLOR menu_selected_text_color)
{
   this->menu_selected_text_color = menu_selected_text_color;
}


void TitleScreen::set_copyright_text_color(ALLEGRO_COLOR copyright_text_color)
{
   this->copyright_text_color = copyright_text_color;
}


void TitleScreen::set_title_font_size(int title_font_size)
{
   this->title_font_size = title_font_size;
}


void TitleScreen::set_menu_font_size(int menu_font_size)
{
   this->menu_font_size = menu_font_size;
}


void TitleScreen::set_copyright_font_size(int copyright_font_size)
{
   this->copyright_font_size = copyright_font_size;
}


void TitleScreen::set_menu_position_x(float menu_position_x)
{
   this->menu_position_x = menu_position_x;
}


void TitleScreen::set_menu_position_y(float menu_position_y)
{
   this->menu_position_y = menu_position_y;
}


std::string TitleScreen::get_title_text() const
{
   return title_text;
}


std::string TitleScreen::get_copyright_text() const
{
   return copyright_text;
}


std::string TitleScreen::get_background_bitmap_name() const
{
   return background_bitmap_name;
}


std::string TitleScreen::get_title_bitmap_name() const
{
   return title_bitmap_name;
}


std::string TitleScreen::get_font_name() const
{
   return font_name;
}


ALLEGRO_COLOR TitleScreen::get_title_text_color() const
{
   return title_text_color;
}


ALLEGRO_COLOR TitleScreen::get_menu_text_color() const
{
   return menu_text_color;
}


ALLEGRO_COLOR TitleScreen::get_menu_selector_color() const
{
   return menu_selector_color;
}


ALLEGRO_COLOR TitleScreen::get_menu_selected_text_color() const
{
   return menu_selected_text_color;
}


ALLEGRO_COLOR TitleScreen::get_copyright_text_color() const
{
   return copyright_text_color;
}


int TitleScreen::get_title_font_size() const
{
   return title_font_size;
}


int TitleScreen::get_menu_font_size() const
{
   return menu_font_size;
}


int TitleScreen::get_copyright_font_size() const
{
   return copyright_font_size;
}


std::vector<std::pair<std::string, std::string>> TitleScreen::get_menu_options() const
{
   return menu_options;
}


float TitleScreen::get_menu_position_x() const
{
   return menu_position_x;
}


float TitleScreen::get_menu_position_y() const
{
   return menu_position_y;
}


int TitleScreen::get_cursor_position() const
{
   return cursor_position;
}


void TitleScreen::on_activate()
{
   cursor_position = 0;
   return;
}

void TitleScreen::set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options)
{
   this->menu_options = menu_options;
   cursor_position = 0;
   return;
}

void TitleScreen::move_cursor_up()
{
   if (menu_is_empty()) return;

   cursor_position--;
   if (cursor_position < 0) cursor_position += menu_options.size();
   return;
}

void TitleScreen::move_cursor_down()
{
   if (menu_is_empty()) return;

   cursor_position++;
   if (cursor_position >= menu_options.size()) cursor_position = cursor_position % menu_options.size();
   return;
}

void TitleScreen::activate_menu_option(std::string menu_option_name)
{
   event_emitter->emit_game_event(menu_option_name);

   //if (menu_option_name == "start_new_game")
   //{
      //event_emitter->emit_event(ALLEGRO_FLARE_EVENT_START_NEW_GAME);
      ////event_emitter->emit_game_event(ALLEGRO_FLARE_EVENT_START_NEW_GAME);
   //}
   //else if (menu_option_name == "exit_game")
   //{
      //event_emitter->emit_event(ALLEGRO_FLARE_EVENT_EXIT_GAME);
      ////event_emitter->emit_game_event(menu_option_name);
   //}
   //else
   //{
      //std::stringstream ss;
      //ss << "[AllegroFlare::Screens::TitleScreen::activate_menu_option()] error: There is no consequential action "
            //"assigned for the menu option value \"" << menu_option_name <<  "\".  Note this is "
            //"the value for the menu item labeled \"" << menu_option_name << "\".";
      //throw std::runtime_error(ss.str());
   //}
   //return;
}

void TitleScreen::select_menu_option()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::select_menu_option]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::select_menu_option: error: guard \"event_emitter\" not met");
   }
   if (menu_is_empty())
   {
      std::cout <<
         "[AllegroFlare::Screens::TitleScreen::select_menu_option()] error: can not select a menu item, "
         "the menu is empty."
         << std::endl;
      return;
   }

   std::string current_menu_option_value = infer_current_menu_option_value();

   activate_menu_option(current_menu_option_value);

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
      error_message << "[TitleScreen::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   //al_set_render_state(ALLEGRO_DEPTH_FUNCTION, ALLEGRO_RENDER_LESS);
   //al_set_render_state(ALLEGRO_DEPTH_FUNCTION, ALLEGRO_RENDER_LESS_EQUAL);

   draw_background();
   draw_title();
   draw_copyright_text();
   draw_menu();
   return;
}

void TitleScreen::draw_background()
{
   if (background_bitmap_name.empty()) return;
   ALLEGRO_BITMAP *background = obtain_background_bitmap();
   if (!background) return;

   al_draw_scaled_bitmap(background,
      0, 0, al_get_bitmap_width(background), al_get_bitmap_height(background),
      0, 0, 1920, 1080, 0);

   return;
}

void TitleScreen::draw_title()
{
   if (!title_bitmap_name.empty())
   {
      ALLEGRO_BITMAP *title_bitmap = obtain_title_bitmap();
      if (title_bitmap)
      {
         AllegroFlare::Placement2D place;
         place.position.x = 1920 / 2;
         place.position.y = 1080 / 3;
         place.size.x = al_get_bitmap_width(title_bitmap);
         place.size.y = al_get_bitmap_height(title_bitmap);
         place.start_transform();
         al_draw_bitmap(title_bitmap, 0, 0, 0);
         place.restore_transform();
      }
   }
   else if (!title_text.empty())
   {
      // TODO: review guards on this function
      ALLEGRO_FONT *title_font = obtain_title_font();
      int surface_width = 1920;
      int surface_height = 1080;
      al_draw_text(
         title_font,
         title_text_color, //ALLEGRO_COLOR{1, 1, 1, 1},
         surface_width / 2,
         surface_height / 3,
         ALLEGRO_ALIGN_CENTER,
         get_title_text().c_str()
      );
   }
   return;
}

void TitleScreen::draw_copyright_text()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *copyright_font = obtain_copyright_font();
   int surface_width = 1920;
   int surface_height = 1080;
   float line_height = al_get_font_line_height(copyright_font);

   int number_of_lines = 1;
   for (int i = 0; i < copyright_text.size(); i++) if (copyright_text[i] == '\n') number_of_lines++;

   al_draw_multiline_text(
      copyright_font,
      copyright_text_color,
      surface_width/2,
      surface_height - 80 - (int)(number_of_lines * line_height / 2),
      surface_width,
      line_height,
      ALLEGRO_ALIGN_CENTER,
      get_copyright_text().c_str()
   );
   return;
}

void TitleScreen::draw_menu()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::draw_menu]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::draw_menu: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: review guards on this function
   ALLEGRO_FONT *menu_font = obtain_menu_font();
   int surface_width = 1920;
   int surface_height = 1080;
   float h_font_line_height = (int)(al_get_font_line_height(menu_font) * 0.5f);
   float menu_item_vertical_spacing = (int)(al_get_font_line_height(menu_font) * 1.25f);
   float h_menu_item_vertical_spacing = (int)(al_get_font_line_height(menu_font) * 1.25f);
   int menu_item_num = 0;

   // get longest menu option text length
   int longest_menu_option_text_width = 0;
   for (auto &menu_option : menu_options)
   {
      std::string menu_item_text = std::get<0>(menu_option);
      int this_menu_item_text_width = al_get_text_width(menu_font, menu_item_text.c_str());
      if (this_menu_item_text_width > longest_menu_option_text_width)
         longest_menu_option_text_width = this_menu_item_text_width;
   }

   // render each menu item
   for (auto &menu_option : menu_options)
   {
      bool showing_cursor_on_this_option = false;
      if (menu_item_num == cursor_position) showing_cursor_on_this_option = true;
      std::string menu_item_text = std::get<0>(menu_option);

      ALLEGRO_COLOR this_menu_text_color = showing_cursor_on_this_option
         ? menu_selected_text_color : menu_text_color;

      float x = menu_position_x;
      float y = menu_position_y + menu_item_vertical_spacing * menu_item_num;

      if (showing_cursor_on_this_option)
      {
         float box_width = longest_menu_option_text_width + 148;
         float box_height = al_get_font_line_height(menu_font) + 6;
         float h_box_width = box_width * 0.5;
         float h_box_height = box_height * 0.5;
         al_draw_filled_rectangle(x-h_box_width, y-h_box_height, x+h_box_width, y+h_box_height, menu_selector_color);
      }

      al_draw_text(
         menu_font,
         this_menu_text_color,
         (int)x,
         (int)(y-h_font_line_height),
         ALLEGRO_ALIGN_CENTER,
         menu_item_text.c_str()
      );

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
      error_message << "[TitleScreen::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::obtain_title_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << title_font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* TitleScreen::obtain_menu_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::obtain_menu_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::obtain_menu_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << menu_font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* TitleScreen::obtain_copyright_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::obtain_copyright_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::obtain_copyright_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << copyright_font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_BITMAP* TitleScreen::obtain_background_bitmap()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::obtain_background_bitmap]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::obtain_background_bitmap: error: guard \"bitmap_bin\" not met");
   }
   return bitmap_bin->auto_get(background_bitmap_name);
}

ALLEGRO_BITMAP* TitleScreen::obtain_title_bitmap()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::obtain_title_bitmap]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::obtain_title_bitmap: error: guard \"bitmap_bin\" not met");
   }
   return bitmap_bin->auto_get(title_bitmap_name);
}

void TitleScreen::virtual_control_button_down_func(int player_num, int button_num, bool is_repeat)
{
   if (button_num == VirtualControls::BUTTON_UP) move_cursor_up();
   if (button_num == VirtualControls::BUTTON_DOWN) move_cursor_down();
   if (button_num == VirtualControls::BUTTON_A
      || button_num == VirtualControls::BUTTON_START
      )
   {
      select_menu_option();
   }
}

bool TitleScreen::menu_is_empty()
{
   return menu_options.empty();
}

bool TitleScreen::menu_has_items()
{
   return !menu_is_empty();
}

std::vector<std::pair<std::string, std::string>> TitleScreen::build_default_menu_options()
{
   std::vector<std::pair<std::string, std::string>> result;
   result = { { "Start new game", "start_new_game" }, { "Credits", "show_credits" }, { "Exit", "exit_game" } };
   return result;
}


} // namespace Screens
} // namespace AllegroFlare





#include <AllegroFlare/Screens/PauseScreen.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


PauseScreen::PauseScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, std::string title_text, std::string footer_text, std::string title_bitmap_name, std::string font_name, ALLEGRO_COLOR title_text_color, ALLEGRO_COLOR menu_text_color, ALLEGRO_COLOR menu_selector_color, ALLEGRO_COLOR footer_text_color, int title_font_size, int menu_font_size, int footer_font_size, bool show_footer_text)
   : AllegroFlare::Screens::Base("PauseScreen")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , title_text(title_text)
   , footer_text(footer_text)
   , on_menu_choice_callback_func()
   , on_menu_choice_callback_func_user_data(nullptr)
   , title_bitmap_name(title_bitmap_name)
   , font_name(font_name)
   , title_text_color(title_text_color)
   , menu_text_color(menu_text_color)
   , menu_selector_color(menu_selector_color)
   , footer_text_color(footer_text_color)
   , title_font_size(title_font_size)
   , menu_font_size(menu_font_size)
   , footer_font_size(footer_font_size)
   , show_footer_text(show_footer_text)
   , menu_options(build_default_menu_options())
   , cursor_position(0)
   , title_menu_gutter(80)
{
}


PauseScreen::~PauseScreen()
{
}


void PauseScreen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void PauseScreen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void PauseScreen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void PauseScreen::set_title_text(std::string title_text)
{
   this->title_text = title_text;
}


void PauseScreen::set_footer_text(std::string footer_text)
{
   this->footer_text = footer_text;
}


void PauseScreen::set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Screens::PauseScreen*, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void PauseScreen::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


void PauseScreen::set_title_bitmap_name(std::string title_bitmap_name)
{
   this->title_bitmap_name = title_bitmap_name;
}


void PauseScreen::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void PauseScreen::set_title_text_color(ALLEGRO_COLOR title_text_color)
{
   this->title_text_color = title_text_color;
}


void PauseScreen::set_menu_text_color(ALLEGRO_COLOR menu_text_color)
{
   this->menu_text_color = menu_text_color;
}


void PauseScreen::set_menu_selector_color(ALLEGRO_COLOR menu_selector_color)
{
   this->menu_selector_color = menu_selector_color;
}


void PauseScreen::set_footer_text_color(ALLEGRO_COLOR footer_text_color)
{
   this->footer_text_color = footer_text_color;
}


void PauseScreen::set_title_font_size(int title_font_size)
{
   this->title_font_size = title_font_size;
}


void PauseScreen::set_menu_font_size(int menu_font_size)
{
   this->menu_font_size = menu_font_size;
}


void PauseScreen::set_footer_font_size(int footer_font_size)
{
   this->footer_font_size = footer_font_size;
}


void PauseScreen::set_show_footer_text(bool show_footer_text)
{
   this->show_footer_text = show_footer_text;
}


void PauseScreen::set_title_menu_gutter(float title_menu_gutter)
{
   this->title_menu_gutter = title_menu_gutter;
}


std::string PauseScreen::get_title_text() const
{
   return title_text;
}


std::string PauseScreen::get_footer_text() const
{
   return footer_text;
}


std::function<void(AllegroFlare::Screens::PauseScreen*, void*)> PauseScreen::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* PauseScreen::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
}


std::string PauseScreen::get_title_bitmap_name() const
{
   return title_bitmap_name;
}


std::string PauseScreen::get_font_name() const
{
   return font_name;
}


ALLEGRO_COLOR PauseScreen::get_title_text_color() const
{
   return title_text_color;
}


ALLEGRO_COLOR PauseScreen::get_menu_text_color() const
{
   return menu_text_color;
}


ALLEGRO_COLOR PauseScreen::get_menu_selector_color() const
{
   return menu_selector_color;
}


ALLEGRO_COLOR PauseScreen::get_footer_text_color() const
{
   return footer_text_color;
}


int PauseScreen::get_title_font_size() const
{
   return title_font_size;
}


int PauseScreen::get_menu_font_size() const
{
   return menu_font_size;
}


int PauseScreen::get_footer_font_size() const
{
   return footer_font_size;
}


bool PauseScreen::get_show_footer_text() const
{
   return show_footer_text;
}


std::vector<std::pair<std::string, std::string>> PauseScreen::get_menu_options() const
{
   return menu_options;
}


int PauseScreen::get_cursor_position() const
{
   return cursor_position;
}


float PauseScreen::get_title_menu_gutter() const
{
   return title_menu_gutter;
}


void PauseScreen::on_activate()
{
   cursor_position = 0;
   return;
}

void PauseScreen::on_deactivate()
{
   return;
}

void PauseScreen::set_menu_options(std::vector<std::pair<std::string, std::string>> menu_options)
{
   this->menu_options = menu_options;
   cursor_position = 0;
   return;
}

void PauseScreen::move_cursor_up()
{
   if (menu_is_empty()) return;

   cursor_position--;
   if (cursor_position < 0) cursor_position += menu_options.size();
   return;
}

void PauseScreen::move_cursor_down()
{
   if (menu_is_empty()) return;

   cursor_position++;
   if (cursor_position >= menu_options.size()) cursor_position = cursor_position % menu_options.size();
   return;
}

void PauseScreen::activate_menu_option(std::string menu_option_name)
{
   event_emitter->emit_game_event(menu_option_name);
   // TODO: Test this callback
   if (on_menu_choice_callback_func) on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
}

void PauseScreen::select_menu_option()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[PauseScreen::select_menu_option]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PauseScreen::select_menu_option: error: guard \"event_emitter\" not met");
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

void PauseScreen::primary_timer_func()
{
   render();
   return;
}

void PauseScreen::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[PauseScreen::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PauseScreen::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PauseScreen::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PauseScreen::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   draw_title();
   if (show_footer_text) draw_footer_text();
   draw_menu();
   return;
}

void PauseScreen::draw_title()
{
   int surface_width = 1920;
   int surface_height = 1080;

   float title_x = surface_width/2;
   float title_y = surface_height/2 - title_menu_gutter/2;

   if (!title_bitmap_name.empty())
   {
      ALLEGRO_BITMAP *title_bitmap = obtain_title_bitmap();
      if (title_bitmap)
      {
         AllegroFlare::Placement2D place;
         place.position.x = title_x;
         place.position.y = title_y;
         place.size.x = al_get_bitmap_width(title_bitmap);
         place.size.y = al_get_bitmap_height(title_bitmap);
         place.align.y = 1.0f;

         place.start_transform();
         al_draw_bitmap(title_bitmap, 0, 0, 0);
         place.restore_transform();
      }
   }
   else if (!title_text.empty())
   {
      // TODO: review guards on this function
      ALLEGRO_FONT *title_font = obtain_title_font();
      al_draw_text(
         title_font,
         title_text_color, //ALLEGRO_COLOR{1, 1, 1, 1},
         title_x,
         title_y - al_get_font_line_height(title_font), // / 2,
         ALLEGRO_ALIGN_CENTER,
         get_title_text().c_str()
      );
   }
   return;
}

void PauseScreen::draw_footer_text()
{
   // TODO: review guards on this function
   ALLEGRO_FONT *footer_font = obtain_footer_font();
   int surface_width = 1920;
   int surface_height = 1080;
   al_draw_text(
      footer_font,
      footer_text_color, //ALLEGRO_COLOR{1, 1, 1, 1},
      surface_width / 2,
      surface_height - 100,
      ALLEGRO_ALIGN_CENTER,
      get_footer_text().c_str()
   );
   return;
}

void PauseScreen::draw_menu()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[PauseScreen::draw_menu]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PauseScreen::draw_menu: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: review guards on this function
   ALLEGRO_FONT *menu_font = obtain_menu_font();
   int surface_width = 1920;
   int surface_height = 1080;
   float h_font_line_height = (int)(al_get_font_line_height(menu_font) * 0.5f);
   float menu_item_vertical_spacing = (int)(al_get_font_line_height(menu_font) * 1.25f);
   float h_menu_item_vertical_spacing = (int)(al_get_font_line_height(menu_font) * 1.25f);
   int menu_item_num = 0;

   float menu_x = surface_width/2;
   float menu_y = surface_height/2 + title_menu_gutter / 2; //surface_height/6;

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
         ? ALLEGRO_COLOR{0, 0, 0, 1.0} : menu_text_color;

      float x = menu_x;
      float y = menu_y + menu_item_vertical_spacing * menu_item_num;

      if (showing_cursor_on_this_option)
      {
         float box_width = longest_menu_option_text_width + 48;
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

std::string PauseScreen::infer_current_menu_option_value()
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

std::string PauseScreen::infer_current_menu_option_label()
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

ALLEGRO_FONT* PauseScreen::obtain_title_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[PauseScreen::obtain_title_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PauseScreen::obtain_title_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << title_font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* PauseScreen::obtain_menu_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[PauseScreen::obtain_menu_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PauseScreen::obtain_menu_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << menu_font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* PauseScreen::obtain_footer_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[PauseScreen::obtain_footer_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PauseScreen::obtain_footer_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << footer_font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_BITMAP* PauseScreen::obtain_title_bitmap()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[PauseScreen::obtain_title_bitmap]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("PauseScreen::obtain_title_bitmap: error: guard \"bitmap_bin\" not met");
   }
   return bitmap_bin->auto_get(title_bitmap_name);
}

void PauseScreen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
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

bool PauseScreen::menu_is_empty()
{
   return menu_options.empty();
}

bool PauseScreen::menu_has_items()
{
   return !menu_is_empty();
}

std::vector<std::pair<std::string, std::string>> PauseScreen::build_default_menu_options()
{
   std::vector<std::pair<std::string, std::string>> result;
   result = { { "Resume", "unpause_game" }, { "Exit to title screen", "go_to_title_screen" }, { "Quit", "exit_game" } };
   return result;
}


} // namespace Screens
} // namespace AllegroFlare





#include <AllegroFlare/Screens/TitleScreen.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/VirtualControls.hpp>
#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Screens
{


TitleScreen::TitleScreen(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, std::string title_text, std::string copyright_text, std::string background_bitmap_name, std::string title_bitmap_name, std::string title_font_name, std::string menu_font_name, std::string copyright_font_name, ALLEGRO_COLOR title_text_color, ALLEGRO_COLOR menu_text_color, ALLEGRO_COLOR menu_selector_color, ALLEGRO_COLOR menu_selected_text_color, ALLEGRO_COLOR copyright_text_color, int title_font_size, int menu_font_size, int copyright_font_size)
   : AllegroFlare::Screens::Base("TitleScreen")
   , event_emitter(event_emitter)
   , font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , title_text(title_text)
   , copyright_text(copyright_text)
   , background_bitmap_name(background_bitmap_name)
   , title_bitmap_name(title_bitmap_name)
   , title_font_name(title_font_name)
   , menu_font_name(menu_font_name)
   , copyright_font_name(copyright_font_name)
   , title_text_color(title_text_color)
   , menu_text_color(menu_text_color)
   , menu_selector_color(menu_selector_color)
   , menu_selected_text_color(menu_selected_text_color)
   , copyright_text_color(copyright_text_color)
   , title_font_size(title_font_size)
   , menu_font_size(menu_font_size)
   , copyright_font_size(copyright_font_size)
   , menu_options(build_default_menu_options())
   , title_position_x(1920 / 2)
   , title_position_y((1080 / 24 * 9))
   , menu_position_x(1920 / 2)
   , menu_position_y(1080 / 12 * 7)
   , cursor_position(0)
   , menu_move_sound_effect_identifier("menu_move")
   , menu_move_sound_effect_enabled(true)
   , menu_select_option_sound_effect_identifier("menu_select")
   , menu_select_option_sound_effect_enabled(true)
   , menu_option_selection_activation_delay(1.0f)
   , reveal_duration(2.0f)
   , reveal_started_at(0.0f)
   , showing_menu(false)
   , showing_copyright(false)
   , state(STATE_UNDEF)
   , state_is_busy(false)
   , state_changed_at(0.0f)
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


void TitleScreen::set_title_font_name(std::string title_font_name)
{
   this->title_font_name = title_font_name;
}


void TitleScreen::set_menu_font_name(std::string menu_font_name)
{
   this->menu_font_name = menu_font_name;
}


void TitleScreen::set_copyright_font_name(std::string copyright_font_name)
{
   this->copyright_font_name = copyright_font_name;
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


void TitleScreen::set_title_position_x(float title_position_x)
{
   this->title_position_x = title_position_x;
}


void TitleScreen::set_title_position_y(float title_position_y)
{
   this->title_position_y = title_position_y;
}


void TitleScreen::set_menu_position_x(float menu_position_x)
{
   this->menu_position_x = menu_position_x;
}


void TitleScreen::set_menu_position_y(float menu_position_y)
{
   this->menu_position_y = menu_position_y;
}


void TitleScreen::set_menu_move_sound_effect_identifier(std::string menu_move_sound_effect_identifier)
{
   this->menu_move_sound_effect_identifier = menu_move_sound_effect_identifier;
}


void TitleScreen::set_menu_move_sound_effect_enabled(bool menu_move_sound_effect_enabled)
{
   this->menu_move_sound_effect_enabled = menu_move_sound_effect_enabled;
}


void TitleScreen::set_menu_select_option_sound_effect_identifier(std::string menu_select_option_sound_effect_identifier)
{
   this->menu_select_option_sound_effect_identifier = menu_select_option_sound_effect_identifier;
}


void TitleScreen::set_menu_select_option_sound_effect_enabled(bool menu_select_option_sound_effect_enabled)
{
   this->menu_select_option_sound_effect_enabled = menu_select_option_sound_effect_enabled;
}


void TitleScreen::set_menu_option_selection_activation_delay(float menu_option_selection_activation_delay)
{
   this->menu_option_selection_activation_delay = menu_option_selection_activation_delay;
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


std::string TitleScreen::get_title_font_name() const
{
   return title_font_name;
}


std::string TitleScreen::get_menu_font_name() const
{
   return menu_font_name;
}


std::string TitleScreen::get_copyright_font_name() const
{
   return copyright_font_name;
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


float TitleScreen::get_title_position_x() const
{
   return title_position_x;
}


float TitleScreen::get_title_position_y() const
{
   return title_position_y;
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


std::string TitleScreen::get_menu_move_sound_effect_identifier() const
{
   return menu_move_sound_effect_identifier;
}


bool TitleScreen::get_menu_move_sound_effect_enabled() const
{
   return menu_move_sound_effect_enabled;
}


std::string TitleScreen::get_menu_select_option_sound_effect_identifier() const
{
   return menu_select_option_sound_effect_identifier;
}


bool TitleScreen::get_menu_select_option_sound_effect_enabled() const
{
   return menu_select_option_sound_effect_enabled;
}


float TitleScreen::get_menu_option_selection_activation_delay() const
{
   return menu_option_selection_activation_delay;
}


void TitleScreen::TODO()
{
   // There is some confusing naming between "selected", "chosen", etc.  Selected seems to signify
   // either "highlighted" or "chosen" depending on the casses.
   return;
}

void TitleScreen::set_font_name(std::string font_name)
{
   title_font_name = font_name;
   menu_font_name = font_name;
   copyright_font_name = font_name;
   return;
}

void TitleScreen::set_state(uint32_t state, bool override_if_busy)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::set_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::set_state: error: guard \"is_valid_state(state)\" not met");
   }
   if (this->state == state) return;
   if (!override_if_busy && state_is_busy) return;
   uint32_t previous_state = this->state;

   switch (state)
   {
      case STATE_REVEALING:
         cursor_position = 0;
         showing_menu = false;
         showing_copyright = false;
      break;

      case STATE_AWAITING_USER_INPUT:
         show_menu();
      break;

      case STATE_CHOSE_MENU_OPTION:
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   this->state = state;
   state_changed_at = al_get_time();

   return;
}

void TitleScreen::update_state(float time_now)
{
   if (!(is_valid_state(state)))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::update_state]: error: guard \"is_valid_state(state)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::update_state: error: guard \"is_valid_state(state)\" not met");
   }
   float state_age = infer_age(state_changed_at, time_now);

   switch (state)
   {
      case STATE_REVEALING: {
         float reveal_age = infer_reveal_age();
         if (state_age > reveal_duration)
         {
            set_state(STATE_AWAITING_USER_INPUT);
         }
      } break;

      case STATE_AWAITING_USER_INPUT:
      break;

      case STATE_CHOSE_MENU_OPTION:
         if (state_age > menu_option_selection_activation_delay)
         {
            std::string current_menu_option_value = infer_current_menu_option_value();
            activate_menu_option(current_menu_option_value);
         }
      break;

      default:
         throw std::runtime_error("weird error");
      break;
   }

   return;
}

bool TitleScreen::is_valid_state(uint32_t state)
{
   std::set<uint32_t> valid_states =
   {
      STATE_REVEALING,
      STATE_AWAITING_USER_INPUT,
      STATE_CHOSE_MENU_OPTION,
   };
   return (valid_states.count(state) > 0);
}

float TitleScreen::infer_age(float time_of_event, float time_now)
{
   return std::max(0.0f, time_now - time_of_event);
}

float TitleScreen::infer_reveal_age(float time_now)
{
   return std::max(0.0f, infer_age(reveal_started_at, time_now));
}

float TitleScreen::infer_reveal_age_n(float time_now)
{
   if (!((reveal_duration != 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[TitleScreen::infer_reveal_age_n]: error: guard \"(reveal_duration != 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TitleScreen::infer_reveal_age_n: error: guard \"(reveal_duration != 0.0f)\" not met");
   }
   return std::max(0.0f, std::min(1.0f, infer_reveal_age(time_now) / reveal_duration));
}

void TitleScreen::show_menu()
{
   showing_menu = true;
   showing_copyright = true;
   return;
}

void TitleScreen::on_activate()
{
   set_state(STATE_REVEALING);
   return;
}

void TitleScreen::skip_to_title()
{
   set_state(STATE_AWAITING_USER_INPUT);
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
   if (!STATE_AWAITING_USER_INPUT) return;

   if (menu_move_sound_effect_enabled) play_menu_move_sound_effect();

   cursor_position--;
   if (cursor_position < 0) cursor_position += menu_options.size();

   return;
}

void TitleScreen::move_cursor_down()
{
   if (!STATE_AWAITING_USER_INPUT) return;

   if (menu_move_sound_effect_enabled) play_menu_move_sound_effect();

   cursor_position++;
   if (cursor_position >= menu_options.size()) cursor_position = cursor_position % menu_options.size();

   return;
}

void TitleScreen::activate_menu_option(std::string menu_option_name)
{
   event_emitter->emit_game_event(menu_option_name);
   return;
}

void TitleScreen::select_menu_option()
{
   if (!STATE_AWAITING_USER_INPUT) return;

   if (menu_is_empty())
   {
      std::cout <<
         "[AllegroFlare::Screens::TitleScreen::select_menu_option()] error: can not select a menu item, "
         "the menu is empty."
         << std::endl;
      return;
   }

   set_state(STATE_CHOSE_MENU_OPTION);

   if (menu_select_option_sound_effect_enabled) play_menu_select_option_sound_effect();

   return;
}

void TitleScreen::primary_timer_func()
{
   update_state();
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
   draw_background();
   draw_title();
   if (showing_copyright) draw_copyright_text();
   if (showing_menu) draw_menu();
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
      float reveal_opacity = infer_reveal_age_n();
      ALLEGRO_COLOR tint = ALLEGRO_COLOR{reveal_opacity, reveal_opacity, reveal_opacity, reveal_opacity};
      if (title_bitmap)
      {
         AllegroFlare::Placement2D place;
         place.position.x = title_position_x;
         place.position.y = title_position_y;
         place.size.x = al_get_bitmap_width(title_bitmap);
         place.size.y = al_get_bitmap_height(title_bitmap);
         place.start_transform();
         al_draw_tinted_bitmap(title_bitmap, tint, 0, 0, 0);
         place.restore_transform();
      }
   }
   else if (!title_text.empty())
   {
      // TODO: review guards on this function
      ALLEGRO_FONT *title_font = obtain_title_font();
      float reveal_opacity = infer_reveal_age_n();
      ALLEGRO_COLOR revealed_color = ALLEGRO_COLOR{
         reveal_opacity * title_text_color.r,
         reveal_opacity * title_text_color.g,
         reveal_opacity * title_text_color.b,
         reveal_opacity * title_text_color.a
      };
      //int surface_width = 1920;
      //int surface_height = 1080;
      al_draw_text(
         title_font,
         revealed_color,
         title_position_x,
         title_position_y,
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
         //al_draw_filled_rectangle(x-h_box_width, y-h_box_height, x+h_box_width, y+h_box_height, menu_selector_color);
         al_draw_rectangle(x-h_box_width, y-h_box_height, x+h_box_width, y+h_box_height, menu_selector_color, 2.0);
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

void TitleScreen::play_menu_move_sound_effect()
{
   event_emitter->emit_play_sound_effect_event(menu_move_sound_effect_identifier);
   return;
}

void TitleScreen::play_menu_select_option_sound_effect()
{
   event_emitter->emit_play_sound_effect_event(menu_select_option_sound_effect_identifier);
   return;
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
   composite_font_str << title_font_name << " " << title_font_size;
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
   composite_font_str << menu_font_name << " " << menu_font_size;
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
   composite_font_str << copyright_font_name << " " << copyright_font_size;
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
   if (!STATE_AWAITING_USER_INPUT) return;

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



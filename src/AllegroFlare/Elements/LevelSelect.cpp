

#include <AllegroFlare/Elements/LevelSelect.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Logger.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


LevelSelect::LevelSelect(AllegroFlare::EventEmitter* event_emitter, AllegroFlare::FontBin* font_bin, std::vector<std::pair<std::string, std::string>> levels_list, std::set<std::string> locked_list, std::set<std::string> completed_list)
   : event_emitter(event_emitter)
   , font_bin(font_bin)
   , levels_list(levels_list)
   , locked_list(locked_list)
   , completed_list(completed_list)
   , on_menu_choice_callback_func()
   , on_menu_choice_callback_func_user_data(nullptr)
   , place({ 1920/2, 1080/2, 1300, 700 })
   , cursor_x(0)
   , cursor_y(0)
   , selection_box_width(120)
   , selection_box_height(120)
   , selection_box_spacing_x(30)
   , selection_box_spacing_y(30)
   , num_columns(5)
   , num_rows(3)
   , hide_title_when_locked(true)
   , show_completed_text_on_list_item_box(true)
   , drawing_backfill_and_frame(true)
   , drawing_title_text(true)
   , ignore_on_invalid_selection(true)
{
}


LevelSelect::~LevelSelect()
{
}


void LevelSelect::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void LevelSelect::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void LevelSelect::set_levels_list(std::vector<std::pair<std::string, std::string>> levels_list)
{
   this->levels_list = levels_list;
}


void LevelSelect::set_locked_list(std::set<std::string> locked_list)
{
   this->locked_list = locked_list;
}


void LevelSelect::set_completed_list(std::set<std::string> completed_list)
{
   this->completed_list = completed_list;
}


void LevelSelect::set_on_menu_choice_callback_func(std::function<void(AllegroFlare::Elements::LevelSelect*, void*)> on_menu_choice_callback_func)
{
   this->on_menu_choice_callback_func = on_menu_choice_callback_func;
}


void LevelSelect::set_on_menu_choice_callback_func_user_data(void* on_menu_choice_callback_func_user_data)
{
   this->on_menu_choice_callback_func_user_data = on_menu_choice_callback_func_user_data;
}


void LevelSelect::set_selection_box_width(int selection_box_width)
{
   this->selection_box_width = selection_box_width;
}


void LevelSelect::set_selection_box_height(int selection_box_height)
{
   this->selection_box_height = selection_box_height;
}


void LevelSelect::set_selection_box_spacing_x(int selection_box_spacing_x)
{
   this->selection_box_spacing_x = selection_box_spacing_x;
}


void LevelSelect::set_selection_box_spacing_y(int selection_box_spacing_y)
{
   this->selection_box_spacing_y = selection_box_spacing_y;
}


void LevelSelect::set_num_columns(int num_columns)
{
   this->num_columns = num_columns;
}


void LevelSelect::set_num_rows(int num_rows)
{
   this->num_rows = num_rows;
}


void LevelSelect::set_hide_title_when_locked(bool hide_title_when_locked)
{
   this->hide_title_when_locked = hide_title_when_locked;
}


void LevelSelect::set_show_completed_text_on_list_item_box(bool show_completed_text_on_list_item_box)
{
   this->show_completed_text_on_list_item_box = show_completed_text_on_list_item_box;
}


void LevelSelect::set_drawing_backfill_and_frame(bool drawing_backfill_and_frame)
{
   this->drawing_backfill_and_frame = drawing_backfill_and_frame;
}


void LevelSelect::set_drawing_title_text(bool drawing_title_text)
{
   this->drawing_title_text = drawing_title_text;
}


void LevelSelect::set_ignore_on_invalid_selection(bool ignore_on_invalid_selection)
{
   this->ignore_on_invalid_selection = ignore_on_invalid_selection;
}


std::vector<std::pair<std::string, std::string>> LevelSelect::get_levels_list() const
{
   return levels_list;
}


std::set<std::string> LevelSelect::get_locked_list() const
{
   return locked_list;
}


std::set<std::string> LevelSelect::get_completed_list() const
{
   return completed_list;
}


std::function<void(AllegroFlare::Elements::LevelSelect*, void*)> LevelSelect::get_on_menu_choice_callback_func() const
{
   return on_menu_choice_callback_func;
}


void* LevelSelect::get_on_menu_choice_callback_func_user_data() const
{
   return on_menu_choice_callback_func_user_data;
}


AllegroFlare::Placement2D LevelSelect::get_place() const
{
   return place;
}


int LevelSelect::get_cursor_x() const
{
   return cursor_x;
}


int LevelSelect::get_cursor_y() const
{
   return cursor_y;
}


int LevelSelect::get_selection_box_width() const
{
   return selection_box_width;
}


int LevelSelect::get_selection_box_height() const
{
   return selection_box_height;
}


int LevelSelect::get_selection_box_spacing_x() const
{
   return selection_box_spacing_x;
}


int LevelSelect::get_selection_box_spacing_y() const
{
   return selection_box_spacing_y;
}


int LevelSelect::get_num_columns() const
{
   return num_columns;
}


int LevelSelect::get_num_rows() const
{
   return num_rows;
}


bool LevelSelect::get_hide_title_when_locked() const
{
   return hide_title_when_locked;
}


bool LevelSelect::get_show_completed_text_on_list_item_box() const
{
   return show_completed_text_on_list_item_box;
}


bool LevelSelect::get_drawing_backfill_and_frame() const
{
   return drawing_backfill_and_frame;
}


bool LevelSelect::get_drawing_title_text() const
{
   return drawing_title_text;
}


bool LevelSelect::get_ignore_on_invalid_selection() const
{
   return ignore_on_invalid_selection;
}


AllegroFlare::Placement2D &LevelSelect::get_place_ref()
{
   return place;
}


void LevelSelect::add_to_locked_list(std::string level_identifier)
{
   // TODO: Ensure item exists in list of levels
   locked_list.insert(level_identifier);
   return;
}

void LevelSelect::add_to_completed_list(std::string level_identifier)
{
   // TODO: Ensure item exists in list of levels
   completed_list.insert(level_identifier);
   return;
}

bool LevelSelect::is_locked(std::string level_identifier)
{
   // TODO: Test
   return locked_list.find(level_identifier) != locked_list.end();
}

bool LevelSelect::is_completed(std::string level_identifier)
{
   // TODO: Test
   return completed_list.find(level_identifier) != completed_list.end();
}

bool LevelSelect::unlock(std::string level_identifier)
{
   if (!(is_locked(level_identifier)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::unlock]: error: guard \"is_locked(level_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::unlock]: error: guard \"is_locked(level_identifier)\" not met");
   }
   // TODO: Test this
   return locked_list.erase(level_identifier);
}

void LevelSelect::unlock_all()
{
   // TODO: Test this
   return locked_list.clear();
}

bool LevelSelect::mark_as_completed(std::string level_identifier)
{
   if (!(is_locked(level_identifier)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::mark_as_completed]: error: guard \"is_locked(level_identifier)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::mark_as_completed]: error: guard \"is_locked(level_identifier)\" not met");
   }
   // TODO: Test this
   return completed_list.erase(level_identifier);
}

ALLEGRO_COLOR LevelSelect::opaquify(ALLEGRO_COLOR color, float opacity)
{
   color.r *= opacity;
   color.g *= opacity;
   color.b *= opacity;
   color.a *= opacity;
   return color;
}

ALLEGRO_COLOR LevelSelect::change_a(ALLEGRO_COLOR color, float alpha)
{
   color.a *= alpha;
   color.r *= color.a;
   color.g *= color.a;
   color.b *= color.a;
   return color;
}

void LevelSelect::disable_drawing_backfill_and_frame()
{
   drawing_backfill_and_frame = false;
   return;
}

void LevelSelect::disable_drawing_title_text()
{
   drawing_title_text = false;
   return;
}

void LevelSelect::enable_drawing_backfill_and_frame()
{
   drawing_backfill_and_frame = true;
   return;
}

void LevelSelect::enable_drawing_title_text()
{
   drawing_title_text = true;
   return;
}

void LevelSelect::render()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::render]: error: guard \"font_bin\" not met");
   }
   place.start_transform();

   if (drawing_backfill_and_frame) draw_backfill_and_frame();
   if (drawing_title_text) draw_level_select_title_text();
   draw_level_select_boxes_and_cursor();

   place.restore_transform();

   return;
}

void LevelSelect::draw_backfill_and_frame()
{
   ALLEGRO_COLOR backfill_color = change_a(al_color_html("909090"), 0.3);
   ALLEGRO_COLOR border_color = change_a(al_color_html("ffffff"), 0.8);
   float roundness = 8.0f;
   float border_thickness = 8.0f;
   float border_padding = border_thickness * 1.75f;

   al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, roundness, roundness, backfill_color);
   al_draw_rounded_rectangle(
      0 - border_padding,
      0 - border_padding,
      place.size.x + border_padding,
      place.size.y + border_padding,
      roundness,
      roundness,
      border_color,
      border_thickness
   );

   return;
}

void LevelSelect::draw_level_select_title_text()
{
   ALLEGRO_FONT *font = obtain_title_font();
   ALLEGRO_COLOR color = opaquify(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0});
   al_draw_text(font, color, place.size.x/2, 80, ALLEGRO_ALIGN_CENTER, "Level Select");
   return;
}

void LevelSelect::draw_level_select_boxes_and_cursor()
{
   AllegroFlare::Placement2D level_select_boxes_place;
   level_select_boxes_place.position.x = place.size.x * 0.5;
   level_select_boxes_place.position.y = place.size.y * 0.5 + 50;

   // fit the placement to the level select boxes
   int num_column_gutters = std::max(0, (num_columns - 1));
   int num_row_gutters = std::max(0, (num_rows - 1));
   level_select_boxes_place.size.x = num_columns * selection_box_width
                                   + num_column_gutters * selection_box_spacing_x;
   level_select_boxes_place.size.y = num_rows * selection_box_height
                                   + num_row_gutters * selection_box_spacing_y;

   // start the transform
   level_select_boxes_place.start_transform();

   // draw the boxes
   for (int column=0; column<num_columns; column++)
   {
      for (int row=0; row<num_rows; row++)
      {
         int list_item_num = row * num_columns + column;
         std::string label = "";
         bool locked = false;
         bool completed = false;
         if (list_item_num >= levels_list.size()) {}
         else
         {
            label = std::get<0>(levels_list[list_item_num]);
            std::string identifier = std::get<1>(levels_list[list_item_num]);
            locked = is_locked(identifier);
            completed = is_completed(identifier);
         }

         draw_level_list_item_box(
            column * (selection_box_width + selection_box_spacing_x),
            row * (selection_box_height + selection_box_spacing_y),
            selection_box_width,
            selection_box_height,
            label,
            locked,
            completed
         );
      }
   }

   // draw the selection cursor
   ALLEGRO_COLOR color_a = al_color_name("cyan");
   //ALLEGRO_COLOR color_a = al_color_name("bisque");
   ALLEGRO_COLOR color_b = AllegroFlare::color::transparent;
   float speed_multiplier = 0.9;
   float mix_factor = AllegroFlare::interpolator::slow_in(fmod(al_get_time() * speed_multiplier, 1.0));
   ALLEGRO_COLOR color = AllegroFlare::color::mix(color_a, color_b, 0.7 * mix_factor);
   float r = 6;
   float thickness = 8.0;
   float padding = 12.0f;

   float cursor_box_x = cursor_x * (selection_box_width + selection_box_spacing_x);
   float cursor_box_y = cursor_y * (selection_box_height + selection_box_spacing_y);

   al_draw_rounded_rectangle(
      cursor_box_x - padding,
      cursor_box_y - padding,
      cursor_box_x + selection_box_width + padding, //x + cursor_x*spacing + selection_box_width + padding,
      cursor_box_y + selection_box_height + padding, //y + cursor_y*spacing + selection_box_height + padding,
      r,
      r,
      color,
      thickness
   );

   // restore the transform
   level_select_boxes_place.restore_transform();

   return;
}

void LevelSelect::move_cursor_up()
{
   if (!(has_valid_size()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::move_cursor_up]: error: guard \"has_valid_size()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::move_cursor_up]: error: guard \"has_valid_size()\" not met");
   }
   cursor_y--;
   while(cursor_y < 0) cursor_y += num_rows;
   return;
}

void LevelSelect::move_cursor_down()
{
   if (!(has_valid_size()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::move_cursor_down]: error: guard \"has_valid_size()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::move_cursor_down]: error: guard \"has_valid_size()\" not met");
   }
   cursor_y++;
   cursor_y = cursor_y % num_rows;
   return;
}

void LevelSelect::move_cursor_left()
{
   if (!(has_valid_size()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::move_cursor_left]: error: guard \"has_valid_size()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::move_cursor_left]: error: guard \"has_valid_size()\" not met");
   }
   cursor_x--;
   while(cursor_x < 0) cursor_x += num_columns;
   return;
}

void LevelSelect::move_cursor_right()
{
   if (!(has_valid_size()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::move_cursor_right]: error: guard \"has_valid_size()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::move_cursor_right]: error: guard \"has_valid_size()\" not met");
   }
   cursor_x++;
   cursor_x = cursor_x % num_columns;
   return;
}

bool LevelSelect::has_valid_size()
{
   return !(num_columns == 0 || num_rows == 0);
}

bool LevelSelect::list_is_empty()
{
   return levels_list.empty();
}

void LevelSelect::draw_selection_cursor(float x, float y)
{
   // position
   x = 80;
   y = 80;
   float spacing = selection_box_width + 20;

    // color
   ALLEGRO_COLOR color_a = al_color_name("cyan");
   ALLEGRO_COLOR color_b = AllegroFlare::color::transparent;
   float speed_multiplier = 0.9;
   float mix_factor = AllegroFlare::interpolator::slow_in(fmod(al_get_time() * speed_multiplier, 1.0));
   ALLEGRO_COLOR color = AllegroFlare::color::mix(color_a, color_b, 0.7 * mix_factor);
   float r = 6;
   float thickness = 8.0;
   float padding = 12.0f;

   al_draw_rounded_rectangle(
      x + cursor_x*spacing - padding,
      y + cursor_y*spacing - padding,
      x + cursor_x*spacing + selection_box_width + padding,
      y + cursor_y*spacing + selection_box_height + padding,
      r,
      r,
      color,
      thickness
   );
   return;
}

void LevelSelect::draw_level_list_item_box(float x, float y, float w, float h, std::string label, bool locked, bool completed)
{
   ALLEGRO_COLOR backfill_color = opaquify(ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.4});
   ALLEGRO_COLOR text_color = opaquify(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}, locked ? 0.2f : 1.0f);
   float roundness = 6.0f;
   ALLEGRO_FONT *font = obtain_level_label_font();
   float line_height = al_get_font_line_height(font);

   al_draw_filled_rounded_rectangle(x+0, y+0, x+w, y+h, roundness, roundness, backfill_color);
   if (locked)
   {
      // Draw the text "Locked"
      al_draw_text(font, text_color, x+w/2, y+h/2-line_height/2, ALLEGRO_ALIGN_CENTER, "Locked");

      // Draw lock icon
      ALLEGRO_FONT *icon_font = obtain_lock_icon_font();
      ALLEGRO_COLOR icon_color = text_color; //opaquify(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}, 0.6f);
      float icon_font_line_height = al_get_font_line_height(icon_font);
      uint32_t icon = 0xf023;
      draw_unicode_character(
         icon_font,
         icon_color,
         icon,
         ALLEGRO_ALIGN_CENTER,
         x+w-22, y+h-36  // Bottom right (use font-size -23)
         //x+w/2, y+h/2-icon_font_line_height/2 // centered (use font-size -52 or so)
      );
   }
   else
   {
      al_draw_text(font, text_color, x+w/2, y+h/2-line_height/2, ALLEGRO_ALIGN_CENTER, label.c_str());

      if (completed)
      {
         // Draw lock icon
         ALLEGRO_FONT *icon_font = obtain_small_lock_icon_font();
         ALLEGRO_FONT *small_label_font = obtain_small_label_font();
         ALLEGRO_COLOR icon_color = opaquify(ALLEGRO_COLOR{0.5, 1.0, 0.83, 1.0}, 1.0f);
         float icon_font_line_height = al_get_font_line_height(icon_font);
         uint32_t icon = 0xf058;
         draw_unicode_character(
            icon_font,
            icon_color,
            icon,
            ALLEGRO_ALIGN_CENTER,
            x+w-22, y+h-36+6  // Bottom right (use font-size -23)
            //x+w/2, y+h/2-icon_font_line_height/2 // centered (use font-size -52 or so)
         );

         if (show_completed_text_on_list_item_box)
         {
            al_draw_text(small_label_font, icon_color, x+w-22-18, y+h-36, ALLEGRO_ALIGN_RIGHT, "completed");
         }
      }
   }

   return;
}

void LevelSelect::activate_selected_menu_option()
{
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::activate_selected_menu_option]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::activate_selected_menu_option]: error: guard \"event_emitter\" not met");
   }
   if (ignore_on_invalid_selection)
   {
      if (list_is_empty()) return;
      if (!cursor_selection_is_valid()) return;
      std::string current_menu_option_value = infer_current_menu_option_value();
      if (is_locked(current_menu_option_value)) return;
   }

   if (list_is_empty())
   {
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Elements::LevelSelect::activate_selected_menu_option",
         "Can not select a level, the list of levels is empty."
      );
      return;
   }

   // TODO: Test this condition
   if (!cursor_selection_is_valid() && ignore_on_invalid_selection)
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Elements::LevelSelect::activate_selected_menu_option",
         "Can not select the currently highlighted option, the cursor is not over a valid selection."
      );
      return;
   }

   std::string current_menu_option_value = infer_current_menu_option_value();

   if (current_menu_option_value.empty())
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Elements::LevelSelect::activate_selected_menu_option",
         "Can not select the currently highlighted option, it contains an empty value."
      );
      return;
   }
   else if (is_locked(current_menu_option_value))
   {
      AllegroFlare::Logger::warn_from(
         "AllegroFlare::Elements::LevelSelect::activate_selected_menu_option",
         "Can not select the currently highlighted option. It is locked."
      );
      return;
   }
   else
   {
      std::string *string_to_pass = new std::string(current_menu_option_value);
      // TODO: Consider removing this event emission
      event_emitter->emit_event(ALLEGRO_FLARE_EVENT_SELECT_LEVEL, (intptr_t)string_to_pass);

      // TODO: Test this callback
      if (on_menu_choice_callback_func) on_menu_choice_callback_func(this, on_menu_choice_callback_func_user_data);
   }

   return;
}

std::string LevelSelect::infer_current_menu_option_value()
{
   // TODO: Add test for this function
   if (levels_list.empty()) return "";
   int cursor_position = infer_cursor_position();

   if (!cursor_selection_is_valid())
   {
      throw std::runtime_error("[AllegroFlare/Elements/LevelSelect]: error: the cursor_position is not in "
                               "a valid position to get the current menu choice's value.");
   }
   std::string current_menu_option_value = std::get<1>(levels_list[cursor_position]);
   return current_menu_option_value;
}

int LevelSelect::infer_cursor_position()
{
   // TODO: Test this
   return cursor_y * num_columns + cursor_x;
}

bool LevelSelect::cursor_selection_is_valid()
{
   // TODO: Test this
   int cursor_position = infer_cursor_position();
   return (cursor_position >= 0 && cursor_position < levels_list.size());
}

void LevelSelect::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}

ALLEGRO_FONT* LevelSelect::obtain_title_font()
{
   return font_bin->auto_get("Inter-Regular.ttf -46");
}

ALLEGRO_FONT* LevelSelect::obtain_level_label_font()
{
   return font_bin->auto_get("Inter-Regular.ttf -32");
}

ALLEGRO_FONT* LevelSelect::obtain_lock_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::obtain_lock_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::obtain_lock_icon_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier_and_size;
   font_identifier_and_size << "fa-solid-900.ttf " << -23; // -64
   return font_bin->auto_get(font_identifier_and_size.str());
}

ALLEGRO_FONT* LevelSelect::obtain_small_lock_icon_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::LevelSelect::obtain_small_lock_icon_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::LevelSelect::obtain_small_lock_icon_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier_and_size;
   font_identifier_and_size << "fa-solid-900.ttf " << -18; // -64
   return font_bin->auto_get(font_identifier_and_size.str());
}

ALLEGRO_FONT* LevelSelect::obtain_small_label_font()
{
   return font_bin->auto_get("Inter-Regular.ttf -28");
}


} // namespace Elements
} // namespace AllegroFlare



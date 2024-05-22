

#include <AllegroFlare/Elements/MultiList.hpp>

#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/StringTransformer.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


MultiList::MultiList()
   : AllegroFlare::Elements::Base()
   , font_bin(nullptr)
   , cursor_x(0)
   , cursor_y(0)
   , lists({})
   , list_cursor_positions({})
   , selection_cursor_box({})
   , list_item_width(480.0f)
   , list_item_height(48.0f)
   , list_item_margin_x(80.0f)
   , list_item_margin_y(12.0f)
   , wrap_cursor_horizontally(true)
   , wrap_cursors_vertically(true)
   , move_cursor_to_active_item_when_entering_list(true)
   , initialized(false)
{
}


MultiList::~MultiList()
{
}


void MultiList::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[MultiList::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void MultiList::set_wrap_cursor_horizontally(bool wrap_cursor_horizontally)
{
   this->wrap_cursor_horizontally = wrap_cursor_horizontally;
}


void MultiList::set_wrap_cursors_vertically(bool wrap_cursors_vertically)
{
   this->wrap_cursors_vertically = wrap_cursors_vertically;
}


void MultiList::set_move_cursor_to_active_item_when_entering_list(bool move_cursor_to_active_item_when_entering_list)
{
   this->move_cursor_to_active_item_when_entering_list = move_cursor_to_active_item_when_entering_list;
}


int MultiList::get_cursor_x() const
{
   return cursor_x;
}


int MultiList::get_cursor_y() const
{
   return cursor_y;
}


float MultiList::get_list_item_width() const
{
   return list_item_width;
}


float MultiList::get_list_item_height() const
{
   return list_item_height;
}


bool MultiList::get_wrap_cursor_horizontally() const
{
   return wrap_cursor_horizontally;
}


bool MultiList::get_wrap_cursors_vertically() const
{
   return wrap_cursors_vertically;
}


bool MultiList::get_move_cursor_to_active_item_when_entering_list() const
{
   return move_cursor_to_active_item_when_entering_list;
}


bool MultiList::get_initialized() const
{
   return initialized;
}


void MultiList::set_list_item_width(int list_item_width)
{
   // TODO: Test this
   this->list_item_width = list_item_width;
   selection_cursor_box.set_size_quietly(list_item_width, list_item_height); // TODO: See if width can be set without
                                                                             // needing to assign height
   return;
}

void MultiList::set_list_item_height(int list_item_height)
{
   // TODO: Test this
   this->list_item_height = list_item_height;
   selection_cursor_box.set_size_quietly(list_item_width, list_item_height); // TODO: See if height can be set
                                                                             // without needing to assign width
   return;
}

void MultiList::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[MultiList::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultiList::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[MultiList::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultiList::initialize: error: guard \"font_bin\" not met");
   }
   selection_cursor_box.set_size_quietly(list_item_width, list_item_height);
   move_cursor_box_position_to_cursor_location(); // TODO: See if this is necessary
   initialized = true;
   return;
}

bool MultiList::move_cursor_up()
{
   if (lists.empty()) return false; // TODO: Test this case
   //int &list_cursor = list_cursor_positions[cursor_x]; // This option will automatically change the selection
                                                         // in the list
   int &list_cursor = cursor_y;
   list_cursor--;
   if (wrap_cursors_vertically) // TODO: Test this wrapping feature (with and without)
   {
      if (list_cursor < 0) list_cursor += lists[cursor_x].size();
   }
   else
   {
      if (list_cursor < 0) list_cursor = 0;
   }
   move_cursor_box_position_to_cursor_location();
   return true;
}

bool MultiList::move_cursor_down()
{
   if (lists.empty()) return false; // TODO: Test this case
   //int &list_cursor = list_cursor_positions[cursor_x]; // This option will automatically change the selection
                                                         // in the list
   int &list_cursor = cursor_y;
   list_cursor++;
   if (wrap_cursors_vertically) // TODO: Test this wrapping feature (with and without)
   {
      if (list_cursor >= lists[cursor_x].size()) list_cursor -= lists[cursor_x].size();
   }
   else
   {
      if (list_cursor >= lists[cursor_x].size()) list_cursor = lists[cursor_x].size() - 1;
   }
   move_cursor_box_position_to_cursor_location();
   return true;
}

bool MultiList::move_cursor_left()
{
   if (lists.size() <= 1) return false; // TODO: Test this case
   cursor_x--;
   if (wrap_cursor_horizontally) // TODO: Test this wrapping feature (with and without)
   {
      if (cursor_x < 0) cursor_x += lists.size();
   }
   if (move_cursor_to_active_item_when_entering_list)
   {
      cursor_y = list_cursor_positions[cursor_x];
   }
   move_cursor_box_position_to_cursor_location();
   return true;
}

bool MultiList::move_cursor_right()
{
   if (lists.size() <= 1) return false; // TODO: Test this case
   cursor_x++;
   if (wrap_cursor_horizontally) // TODO: Test this wrapping feature (with and without)
   {
      if (cursor_x >= lists.size()) cursor_x -= lists.size();
   }
   if (move_cursor_to_active_item_when_entering_list)
   {
      cursor_y = list_cursor_positions[cursor_x];
   }
   move_cursor_box_position_to_cursor_location();
   return true;
}

void MultiList::move_cursor_box_position_to_cursor_location()
{
   selection_cursor_box.set_position(calculate_cursor_real_x(), calculate_cursor_real_y());
   return;
}

void MultiList::set_lists(std::vector<std::vector<std::pair<std::string, std::string>>> lists)
{
   this->lists = lists;
   list_cursor_positions.clear();
   list_cursor_positions.resize(lists.size(), 0);
   return;
}

void MultiList::activate_selection_at_current_cursor_position()
{
   list_cursor_positions[cursor_x] = cursor_y;
   // TODO: Consider adding a callback
   return;
}

void MultiList::set_cursor_position(int cursor_x, int cursor_y)
{
   if (!((cursor_x >= 0)))
   {
      std::stringstream error_message;
      error_message << "[MultiList::set_cursor_position]: error: guard \"(cursor_x >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultiList::set_cursor_position: error: guard \"(cursor_x >= 0)\" not met");
   }
   if (!((cursor_x < lists.size())))
   {
      std::stringstream error_message;
      error_message << "[MultiList::set_cursor_position]: error: guard \"(cursor_x < lists.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultiList::set_cursor_position: error: guard \"(cursor_x < lists.size())\" not met");
   }
   if (!((cursor_y >= 0)))
   {
      std::stringstream error_message;
      error_message << "[MultiList::set_cursor_position]: error: guard \"(cursor_y >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultiList::set_cursor_position: error: guard \"(cursor_y >= 0)\" not met");
   }
   if (!((cursor_y < lists[cursor_x].size())))
   {
      std::stringstream error_message;
      error_message << "[MultiList::set_cursor_position]: error: guard \"(cursor_y < lists[cursor_x].size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("MultiList::set_cursor_position: error: guard \"(cursor_y < lists[cursor_x].size())\" not met");
   }
   this->cursor_x = cursor_x;
   this->cursor_y = cursor_y;
   //list_cursor_positions[cursor_x] = cursor_y;
   return;
}

float MultiList::calculate_width()
{
   if (lists.empty()) return 0.0f;
   return (lists.size() * list_item_width) + ((lists.size()-1) * list_item_margin_x);
}

float MultiList::calculate_cursor_real_x()
{
   float result = (cursor_x * list_item_width);
   if (cursor_x > 0) result += cursor_x * list_item_margin_x;
   return result;
}

float MultiList::calculate_cursor_real_y()
{
   //int &list_cursor_pos = list_cursor_positions[cursor_x];
   int &list_cursor_pos = cursor_y;
   float result = (list_cursor_pos * list_item_height);
   if (list_cursor_pos > 0) result += list_cursor_pos * list_item_margin_y;
   return result;
}

void MultiList::render()
{
   get_placement_ref().start_transform();

   float list_x_spacing = list_item_width + list_item_margin_x;
   float list_y_spacing = list_item_height + list_item_margin_y;

   bool cursor_is_on_this_list = false;
   bool cursor_is_on_this_list_item = false;

   int list_num = 0;
   for (auto &list : lists)
   {
      cursor_is_on_this_list = (cursor_x == list_num);

      int list_y = 0;
      for (auto &list_item : list)
      {
         //bool this_list_item_is_activated = (list_cursor_positions[cursor_x] == list_y);
         bool item_is_activated_in_this_list =  (list_cursor_positions[list_num] == list_y);
         cursor_is_on_this_list_item = cursor_is_on_this_list && (list_cursor_positions[cursor_x] == list_y);

         // Draw the list item
         std::string &list_item_text = list_item.first;
         draw_list_item(
               list_num * list_x_spacing,
               list_y * list_y_spacing, //list_item_margin_y,
               list_item_width,
               list_item_height,
               list_item_text,
               item_is_activated_in_this_list
            );

         // Increment the list item
         list_y++;
      }

      list_num++;
   }

   selection_cursor_box.render();

   get_placement_ref().restore_transform();

   return;
}

void MultiList::draw_list_item(float x, float y, float width, float height, std::string text, bool is_selected)
{
   text = AllegroFlare::StringTransformer(text).upcase().expand(1).get_text();

   ALLEGRO_COLOR unselected_text_color = ALLEGRO_COLOR{0.92f, 0.9f, 0.82f, 1.0f};
   ALLEGRO_COLOR selected_text_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};

   float label_op = 0.9f;
   ALLEGRO_COLOR unselected_frame_color = ALLEGRO_COLOR{0.2f, 0.2f, 0.2f, 1.0f};
   ALLEGRO_COLOR selected_frame_color = al_color_html("4f5e93");
   //ALLEGRO_COLOR{0.3, 0.3, 0.3, 1.0f};

   float frame_thickness = 2.0f;

   ALLEGRO_COLOR unselected_fill_color = ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f};
   ALLEGRO_COLOR selected_fill_color = al_color_html("394778");
   //ALLEGRO_COLOR{0.3, 0.3, 0.3, 1.0f};

   float dropshadow_op = 0.8f;
   ALLEGRO_COLOR dropshadow_color = ALLEGRO_COLOR{
         0.1f * dropshadow_op,
         0.1f * dropshadow_op,
         0.14f * dropshadow_op,
         dropshadow_op
      };

   AllegroFlare::Placement2D label_and_text_placement;
   label_and_text_placement.position.x = x;
   label_and_text_placement.position.y = y;

   label_and_text_placement.start_transform();
   {
      ALLEGRO_COLOR frame_color = is_selected ? selected_frame_color : unselected_frame_color;
      ALLEGRO_COLOR fill_color = is_selected ? selected_fill_color : unselected_fill_color;
      ALLEGRO_COLOR text_color = is_selected ? selected_text_color : unselected_text_color;

      // Draw the fill
      al_draw_filled_rectangle(
         0,
         0,
         width,
         height,
         fill_color
      );

      // Draw the frame
      al_draw_rectangle(
         0,
         0,
         width,
         height,
         frame_color,
         2.0f
      );

      // Draw the text
      ALLEGRO_FONT *medium_hud_font = obtain_medium_hud_font();
      int text_x = 24;
      int text_y = 7;

      // Draw the dropshadow (if actively selected)
      if (is_selected)
      {
         int dropshadow_offset_x = 3;
         int dropshadow_offset_y = 3;
         // Draw the text
         al_draw_textf(
            medium_hud_font,
            dropshadow_color,
            text_x + dropshadow_offset_x,
            text_y + dropshadow_offset_y,
            ALLEGRO_ALIGN_LEFT,
            text.c_str()
         );
      }

      // Draw the text
      al_draw_textf(
         medium_hud_font,
         text_color,
         text_x,
         text_y,
         ALLEGRO_ALIGN_LEFT,
         text.c_str()
      );
   }
   label_and_text_placement.restore_transform();
   return;
}

ALLEGRO_FONT* MultiList::obtain_small_hud_font()
{
   std::stringstream result_font_identifier;
   result_font_identifier << "Orbitron-Medium.ttf" << " " << -26;
   return font_bin->auto_get(result_font_identifier.str());
}

ALLEGRO_FONT* MultiList::obtain_medium_hud_font()
{
   std::stringstream result_font_identifier;
   result_font_identifier << "Orbitron-Medium.ttf" << " " << -32;
   return font_bin->auto_get(result_font_identifier.str());
}


} // namespace Elements
} // namespace AllegroFlare



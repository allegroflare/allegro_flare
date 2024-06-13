

#include <AllegroFlare/Elements/ListBoxRenderer.hpp>

#include <AllegroFlare/ColorKit.hpp>
#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <algorithm>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


ListBoxRenderer::ListBoxRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, std::vector<std::string> list_items)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , list_items(list_items)
   , cursor_position(0)
   , age(999.0f)
   , width((1920/3.0f))
   , height((1080/5.0f))
   , font_name(DEFAULT_FONT_NAME)
   , font_size(DEFAULT_FONT_SIZE)
   , text_padding_x(52.0f)
   , text_padding_y(40.0f)
   , text_color_selected(DEFAULT_SELECTION_COLOR)
   , text_color_not_selected(DEFAULT_TEXT_NOT_SELECTED_COLOR)
   , frame_backfill_color(calculate_DEFAULT_BACKFILL_COLOR())
   , frame_border_color(calculate_DEFAULT_BORDER_COLOR())
   , selection_frame_color(DEFAULT_SELECTION_COLOR)
{
}


ListBoxRenderer::~ListBoxRenderer()
{
}


void ListBoxRenderer::set_list_items(std::vector<std::string> list_items)
{
   this->list_items = list_items;
}


void ListBoxRenderer::set_cursor_position(int cursor_position)
{
   this->cursor_position = cursor_position;
}


void ListBoxRenderer::set_age(float age)
{
   this->age = age;
}


void ListBoxRenderer::set_width(float width)
{
   this->width = width;
}


void ListBoxRenderer::set_height(float height)
{
   this->height = height;
}


void ListBoxRenderer::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void ListBoxRenderer::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void ListBoxRenderer::set_text_padding_x(float text_padding_x)
{
   this->text_padding_x = text_padding_x;
}


void ListBoxRenderer::set_text_padding_y(float text_padding_y)
{
   this->text_padding_y = text_padding_y;
}


void ListBoxRenderer::set_text_color_selected(ALLEGRO_COLOR text_color_selected)
{
   this->text_color_selected = text_color_selected;
}


void ListBoxRenderer::set_text_color_not_selected(ALLEGRO_COLOR text_color_not_selected)
{
   this->text_color_not_selected = text_color_not_selected;
}


void ListBoxRenderer::set_frame_backfill_color(ALLEGRO_COLOR frame_backfill_color)
{
   this->frame_backfill_color = frame_backfill_color;
}


void ListBoxRenderer::set_frame_border_color(ALLEGRO_COLOR frame_border_color)
{
   this->frame_border_color = frame_border_color;
}


void ListBoxRenderer::set_selection_frame_color(ALLEGRO_COLOR selection_frame_color)
{
   this->selection_frame_color = selection_frame_color;
}


std::vector<std::string> ListBoxRenderer::get_list_items() const
{
   return list_items;
}


int ListBoxRenderer::get_cursor_position() const
{
   return cursor_position;
}


float ListBoxRenderer::get_age() const
{
   return age;
}


float ListBoxRenderer::get_width() const
{
   return width;
}


float ListBoxRenderer::get_height() const
{
   return height;
}


std::string ListBoxRenderer::get_font_name() const
{
   return font_name;
}


int ListBoxRenderer::get_font_size() const
{
   return font_size;
}


float ListBoxRenderer::get_text_padding_x() const
{
   return text_padding_x;
}


float ListBoxRenderer::get_text_padding_y() const
{
   return text_padding_y;
}


ALLEGRO_COLOR ListBoxRenderer::get_text_color_selected() const
{
   return text_color_selected;
}


ALLEGRO_COLOR ListBoxRenderer::get_text_color_not_selected() const
{
   return text_color_not_selected;
}


ALLEGRO_COLOR ListBoxRenderer::get_frame_backfill_color() const
{
   return frame_backfill_color;
}


ALLEGRO_COLOR ListBoxRenderer::get_frame_border_color() const
{
   return frame_border_color;
}


ALLEGRO_COLOR ListBoxRenderer::get_selection_frame_color() const
{
   return selection_frame_color;
}


float ListBoxRenderer::calculate_y_displacement_from_time(float time, float max_displacement)
{
   float inv_curved_time = 1.0 - calculate_curved_time(time);
   return max_displacement * inv_curved_time;
}

float ListBoxRenderer::calculate_curved_time(float time)
{
   float normalized_age = std::max(std::min(1.0f, time), 0.0f);
   return AllegroFlare::interpolator::double_fast_in(normalized_age);
}

void ListBoxRenderer::draw_frame()
{
   AllegroFlare::Placement2D frame_place = { width/2, height/2, width, height, };
   frame_place.position.y += calculate_y_displacement_from_time(age);
   frame_place.start_transform();
   AllegroFlare::Elements::DialogBoxFrame dialog_box_frame(width, height);
   dialog_box_frame.set_backfill_color(frame_backfill_color);
   dialog_box_frame.set_border_color(frame_border_color);
   dialog_box_frame.set_opacity(calculate_curved_time(age));
   dialog_box_frame.render();
   frame_place.restore_transform();
   return;
}

void ListBoxRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   draw_frame();
   draw_choices_with_cursor_and_current_selection();
   return;
}

float ListBoxRenderer::calculate_list_item_max_width()
{
   return (width - (text_padding_x * 2));
}

float ListBoxRenderer::calculate_line_height()
{
   ALLEGRO_FONT* text_font = obtain_text_font();
   return al_get_font_line_height(text_font);
}

float ListBoxRenderer::calculate_item_spacing_padding()
{
   float line_height = calculate_line_height();
   return line_height * 0.75;
}

float ListBoxRenderer::calculate_content_width()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::calculate_content_width]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::calculate_content_width]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::calculate_content_width]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::calculate_content_width]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: Add more tests for this function
   ALLEGRO_FONT* text_font = obtain_text_font();

   // Calculate the item heights
   float max_theoretical_width = 999999; // TODO: Consider using an std::max or something
   float max_content_width = 0;
   for (auto &list_item : list_items)
   {
      std::vector<float> line_widths = calculate_line_widths(text_font, max_theoretical_width, list_item);
      if (line_widths.empty()) continue;
      auto max_element = std::max_element(line_widths.begin(), line_widths.end());

      // Set the max width
      max_content_width = std::max(max_content_width, *max_element);
   }
   return max_content_width;
}

float ListBoxRenderer::calculate_content_height()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::calculate_content_height]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::calculate_content_height]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::calculate_content_height]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::calculate_content_height]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   int num_items = list_items.size();
   if (num_items == 0) return 0;

   ALLEGRO_FONT* text_font = obtain_text_font();
   float item_max_width = calculate_list_item_max_width();
   float line_height = calculate_line_height();

   // Calculate the item heights
   std::vector<float> item_heights;
   for (auto &list_item : list_items)
   {
      std::vector<float> line_widths = calculate_line_widths(text_font, item_max_width, list_item);
      int this_item_num_lines = line_widths.size();
      float this_item_height = this_item_num_lines * line_height;
      item_heights.push_back(this_item_height);
   }

   // Sum the item heights
   float summated_items_height = 0;
   for (auto &item_height : item_heights)
   {
      summated_items_height += item_height;
   }

   // Calculate the padding between items
   float summated_item_spacing_padding = calculate_item_spacing_padding() * (num_items - 1);

   // Return the height and padding
   return summated_items_height + summated_item_spacing_padding;
}

void ListBoxRenderer::set_height_to_fit_content()
{
   height = calculate_content_height() + text_padding_y * 2;
   return;
}

void ListBoxRenderer::set_width_to_fit_content_or_max_and_min(float max, float min)
{
   if (!((max >= min)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::set_width_to_fit_content_or_max_and_min]: error: guard \"(max >= min)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::set_width_to_fit_content_or_max_and_min]: error: guard \"(max >= min)\" not met");
   }
   // TODO: Test this method
   float max_content_width = max - (text_padding_x * 2);
   float min_content_width = min - (text_padding_x * 2);
   float determined_content_width =
         std::max(
            std::min(calculate_content_width(), max_content_width),
            min_content_width
         );
   width = determined_content_width + (text_padding_x * 2);
   return;
}

void ListBoxRenderer::draw_frame_raw()
{
   AllegroFlare::Elements::DialogBoxFrame frame(width, height);
   frame.set_backfill_color(frame_backfill_color);
   frame.set_border_color(frame_border_color);
   frame.render();
   return;
}

void ListBoxRenderer::draw_choices_with_cursor_and_current_selection()
{
   ALLEGRO_FONT* text_font = obtain_text_font();

   int current_selection_num = cursor_position; // TODO: Figure out what to do with an out-of-bounds cursor position
   float item_max_width = calculate_list_item_max_width();
   float line_height = calculate_line_height();
   float item_spacing_padding_y = calculate_item_spacing_padding();
   float x = text_padding_x;
   float render_cursor_y = text_padding_y;

   // Calculate item heights
   std::vector<float> item_heights;
   for (auto &list_item : list_items)
   {
      std::vector<float> line_widths = calculate_line_widths(text_font, item_max_width, list_item);
      int this_item_num_lines = line_widths.size();
      float this_item_height = this_item_num_lines * line_height;
      item_heights.push_back(this_item_height);
   }

   // Render the items
   int list_item_num = 0;
   float time_between_reveals = 0.2f;
   for (auto &list_item : list_items)
   {
      bool this_list_item_is_currently_selected = (list_item_num == current_selection_num);

      float this_item_age = age - list_item_num * time_between_reveals;
      float this_item_y_displacement = calculate_y_displacement_from_time(this_item_age);
      float this_item_reveal_opacity = calculate_curved_time(this_item_age);

      ALLEGRO_COLOR final_color = this_list_item_is_currently_selected
                                ? text_color_selected
                                : text_color_not_selected;
      final_color = AllegroFlare::ColorKit::mix(ALLEGRO_COLOR{0, 0, 0, 0}, final_color, this_item_reveal_opacity);

      AllegroFlare::Placement2D frame_place;
      frame_place.position.y += this_item_y_displacement;
      frame_place.start_transform();
      al_draw_multiline_text(
         text_font,
         final_color,
         x,
         render_cursor_y,
         item_max_width,
         line_height,
         ALLEGRO_ALIGN_LEFT,
         list_item.c_str()
      );
      frame_place.restore_transform();

      render_cursor_y += item_heights[list_item_num] + item_spacing_padding_y;
      list_item_num++;
   }

   return;
}

std::tuple<float, float, float, float> ListBoxRenderer::calculate_dimensions_for_list_item_at_position(int list_item_position)
{
   if (!((!list_items.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::calculate_dimensions_for_list_item_at_position]: error: guard \"(!list_items.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::calculate_dimensions_for_list_item_at_position]: error: guard \"(!list_items.empty())\" not met");
   }
   if (!((list_item_position >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::calculate_dimensions_for_list_item_at_position]: error: guard \"(list_item_position >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::calculate_dimensions_for_list_item_at_position]: error: guard \"(list_item_position >= 0)\" not met");
   }
   if (!((list_item_position < list_items.size())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::calculate_dimensions_for_list_item_at_position]: error: guard \"(list_item_position < list_items.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::calculate_dimensions_for_list_item_at_position]: error: guard \"(list_item_position < list_items.size())\" not met");
   }
   ALLEGRO_FONT* text_font = obtain_text_font();
   float item_max_width = calculate_list_item_max_width();
   float line_height = calculate_line_height();
   float item_spacing_padding_y = calculate_item_spacing_padding();

   // Calculate item heights
   std::vector<float> item_heights;
   for (auto &list_item : list_items)
   {
      std::vector<float> line_widths = calculate_line_widths(text_font, item_max_width, list_item);
      int this_item_num_lines = line_widths.size();
      float this_item_height = this_item_num_lines * line_height;
      item_heights.push_back(this_item_height);
   }

   // Calculate height up to this item position
   float summated_items_height_to_this_item = 0;
   for (int i=0; i<list_item_position; i++)
   {
      summated_items_height_to_this_item += (item_heights[i] + item_spacing_padding_y);
   }

   float this_item_height = item_heights[list_item_position];
   float manual_y_offset_due_to_line_height_being_visually_misaligned_on_this_font = 0;
   float this_item_x = text_padding_x * 0.5;
   float this_item_center_y = text_padding_y
                           + summated_items_height_to_this_item
                           + (this_item_height * 0.5)
                           + manual_y_offset_due_to_line_height_being_visually_misaligned_on_this_font;
   float selection_box_width = item_max_width + (text_padding_x * 2) * 0.5f;
   float selection_box_height = this_item_height + (item_spacing_padding_y * 2) * 0.5f;

                // { x    , y    , width, height }
   return std::tuple<float, float, float, float>{
      this_item_x,
      this_item_center_y - (selection_box_height * 0.5),
      selection_box_width,
      selection_box_height,
   };
}

bool ListBoxRenderer::multiline_text_draw_callback(int line_number, const char* line, int size, void* extra)
{
   // TODO: Improve tests on this
   std::pair<ALLEGRO_FONT*, std::vector<float>> &multiline_text_line_number =
      *((std::pair<ALLEGRO_FONT*, std::vector<float>>*)extra);

   // Guard that the font is valid
   ALLEGRO_FONT *font = multiline_text_line_number.first;
   if (!font)
   {
      AllegroFlare::Logger::throw_error("Elements::ListBoxRenderer::multiline_text_draw_callback",
                                        "font cannot be a nullptr");
   }

   // Confirm the line is null-terminated
   char* buffer = new char[size + 1];
   strncpy(buffer, line, size); // Copy the first 'size' characters from 'input' to 'buffer'
   buffer[size] = '\0'; // Null-terminate the 'buffer' explicitly

   // Calculate the width of this line of text
   float this_line_width = al_get_text_width(font, buffer);

   delete[] buffer; // Free the allocated memory when done

   multiline_text_line_number.second.push_back(this_line_width);
   return true;
}

std::vector<float> ListBoxRenderer::calculate_line_widths(ALLEGRO_FONT* font, float max_width, std::string text)
{
   if (text.empty()) return {};

   std::pair<ALLEGRO_FONT*, std::vector<float>> multiline_text_line_number;
   multiline_text_line_number.first = obtain_text_font();

   al_do_multiline_text(
      font,
      max_width,
      text.c_str(),
      multiline_text_draw_callback,
      (void*)(&multiline_text_line_number)
   );

   // multiline_text_line_number is now modified, and should now be set to the number of lines drawn
   return multiline_text_line_number.second;
}

ALLEGRO_COLOR ListBoxRenderer::calculate_DEFAULT_BACKFILL_COLOR()
{
   return AllegroFlare::Elements::DialogBoxFrame::DEFAULT_BACKFILL_COLOR;
}

ALLEGRO_COLOR ListBoxRenderer::calculate_DEFAULT_BORDER_COLOR()
{
   return AllegroFlare::Elements::DialogBoxFrame::DEFAULT_BORDER_COLOR;
}

ALLEGRO_FONT* ListBoxRenderer::obtain_text_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::obtain_text_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::obtain_text_font]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::obtain_text_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::obtain_text_font]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::ListBoxRenderer::obtain_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::ListBoxRenderer::obtain_text_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}

std::string ListBoxRenderer::concat_text(std::string source_text, int length)
{
   return source_text.substr(0, length);
}


} // namespace Elements
} // namespace AllegroFlare



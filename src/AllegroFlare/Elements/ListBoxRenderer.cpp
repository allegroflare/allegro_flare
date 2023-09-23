

#include <AllegroFlare/Elements/ListBoxRenderer.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


ListBoxRenderer::ListBoxRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, std::vector<std::string> list_items, float width, float height, std::string font_name, int font_size, float text_padding_x, float text_padding_y, ALLEGRO_COLOR text_color_selected, ALLEGRO_COLOR text_color_not_selected, int cursor_position, ALLEGRO_COLOR selection_frame_color)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , list_items(list_items)
   , width(width)
   , height(height)
   , font_name(font_name)
   , font_size(font_size)
   , text_padding_x(text_padding_x)
   , text_padding_y(text_padding_y)
   , text_color_selected(text_color_selected)
   , text_color_not_selected(text_color_not_selected)
   , cursor_position(cursor_position)
   , selection_frame_color(selection_frame_color)
{
}


ListBoxRenderer::~ListBoxRenderer()
{
}


void ListBoxRenderer::set_list_items(std::vector<std::string> list_items)
{
   this->list_items = list_items;
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


void ListBoxRenderer::set_cursor_position(int cursor_position)
{
   this->cursor_position = cursor_position;
}


void ListBoxRenderer::set_selection_frame_color(ALLEGRO_COLOR selection_frame_color)
{
   this->selection_frame_color = selection_frame_color;
}


std::vector<std::string> ListBoxRenderer::get_list_items() const
{
   return list_items;
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


int ListBoxRenderer::get_cursor_position() const
{
   return cursor_position;
}


ALLEGRO_COLOR ListBoxRenderer::get_selection_frame_color() const
{
   return selection_frame_color;
}


void ListBoxRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   AllegroFlare::Elements::DialogBoxFrame(width, height).render();
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

float ListBoxRenderer::calculate_content_height()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::calculate_content_height]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::calculate_content_height: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::calculate_content_height]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::calculate_content_height: error: guard \"al_is_primitives_addon_initialized()\" not met");
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
      int this_item_num_lines = count_num_lines_will_render(text_font, item_max_width, list_item);
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
      int this_item_num_lines = count_num_lines_will_render(text_font, item_max_width, list_item);
      float this_item_height = this_item_num_lines * line_height;
      item_heights.push_back(this_item_height);
   }

   // Render the items
   int list_item_num = 0;
   for (auto &list_item : list_items)
   {
      bool this_list_item_is_currently_selected = (list_item_num == current_selection_num);

      al_draw_multiline_text(
         text_font,
         this_list_item_is_currently_selected ? text_color_selected : text_color_not_selected,
         x,
         render_cursor_y,
         item_max_width,
         line_height,
         ALLEGRO_ALIGN_LEFT,
         list_item.c_str()
      );

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
      error_message << "[ListBoxRenderer::calculate_dimensions_for_list_item_at_position]: error: guard \"(!list_items.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::calculate_dimensions_for_list_item_at_position: error: guard \"(!list_items.empty())\" not met");
   }
   if (!((list_item_position >= 0)))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::calculate_dimensions_for_list_item_at_position]: error: guard \"(list_item_position >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::calculate_dimensions_for_list_item_at_position: error: guard \"(list_item_position >= 0)\" not met");
   }
   if (!((list_item_position < list_items.size())))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::calculate_dimensions_for_list_item_at_position]: error: guard \"(list_item_position < list_items.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::calculate_dimensions_for_list_item_at_position: error: guard \"(list_item_position < list_items.size())\" not met");
   }
   ALLEGRO_FONT* text_font = obtain_text_font();
   float item_max_width = calculate_list_item_max_width();
   float line_height = calculate_line_height();
   float item_spacing_padding_y = calculate_item_spacing_padding();

   // Calculate item heights
   std::vector<float> item_heights;
   for (auto &list_item : list_items)
   {
      int this_item_num_lines = count_num_lines_will_render(text_font, item_max_width, list_item);
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
   int &multiline_text_line_number = *((int*)extra);
   multiline_text_line_number = line_number;
   return true;
}

int ListBoxRenderer::count_num_lines_will_render(ALLEGRO_FONT* font, float max_width, std::string text)
{
   if (text.empty()) return 0;

   int multiline_text_line_number = 0;
   al_do_multiline_text(
      font,
      max_width,
      text.c_str(),
      multiline_text_draw_callback,
      (void*)(&multiline_text_line_number)
   );

   // multiline_text_line_number is now modified, and should now be set to the number of lines drawn
   return multiline_text_line_number + 1;
}

ALLEGRO_FONT* ListBoxRenderer::obtain_text_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::obtain_text_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::obtain_text_font: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::obtain_text_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::obtain_text_font: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::obtain_text_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::obtain_text_font: error: guard \"font_bin\" not met");
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



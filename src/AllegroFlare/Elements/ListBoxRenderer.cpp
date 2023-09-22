

#include <AllegroFlare/Elements/ListBoxRenderer.hpp>

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


ListBoxRenderer::ListBoxRenderer(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::Elements::ListBox* list_box, float width, float height, std::string font_name, int font_size, float text_padding_x, float text_padding_y)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , list_box(list_box)
   , width(width)
   , height(height)
   , font_name(font_name)
   , font_size(font_size)
   , text_padding_x(text_padding_x)
   , text_padding_y(text_padding_y)
{
}


ListBoxRenderer::~ListBoxRenderer()
{
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
   if (!(list_box))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::render]: error: guard \"list_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::render: error: guard \"list_box\" not met");
   }
   AllegroFlare::Elements::DialogBoxFrame(width, height).render();
   draw_choices_with_cursor_and_current_selection(85);
   return;
}

void ListBoxRenderer::draw_choices_with_cursor_and_current_selection(float start_y, std::vector<std::pair<std::string, std::string>> list_items, int current_selection_num)
{
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   //std::vector<std::pair<std::string, std::string>> list_items = obtain_list_box_items();
   //int current_selection_num = obtain_list_box_cursor_position();
   float line_height = al_get_font_line_height(text_font);
   ALLEGRO_COLOR text_color_not_selected = al_color_html("dfdfdf");
   ALLEGRO_COLOR text_color_selected = al_color_html("000000");
   //ALLEGRO_COLOR text_color = al_color_html("66a9bc");
   ALLEGRO_COLOR selection_hilight_color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
   float selection_box_x_padding = 24;
   float selection_box_y_padding = 0;
   float x = 200;

   int option_num = 0;
   for (auto &option : list_items)
   {
      bool this_option_is_currently_selected = (option_num == current_selection_num);
      std::string option_text = option.first;
      if (this_option_is_currently_selected)
      {
         float text_width = al_get_text_width(text_font, option_text.c_str());
         al_draw_filled_rectangle(
            x - selection_box_x_padding,
            start_y - selection_box_y_padding + option_num * line_height,
            x+text_width + selection_box_x_padding,
            start_y+line_height + selection_box_y_padding + option_num * line_height,
            selection_hilight_color
         );
      }
      al_draw_text(
         text_font,
         this_option_is_currently_selected ? text_color_selected : text_color_not_selected,
         x,
         start_y + line_height*option_num,
         ALLEGRO_ALIGN_LEFT,
         option_text.c_str()
      );
      option_num++;
   }
   return;
}

ALLEGRO_FONT* ListBoxRenderer::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::obtain_dialog_font: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::obtain_dialog_font: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ListBoxRenderer::obtain_dialog_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBoxRenderer::obtain_dialog_font: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}

std::vector<std::pair<std::string, std::string>> ListBoxRenderer::obtain_list_box_items()
{
   return list_box->get_items();
}

int ListBoxRenderer::obtain_list_box_cursor_position()
{
   return list_box->get_cursor_position();
}

std::string ListBoxRenderer::concat_text(std::string source_text, int length)
{
   return source_text.substr(0, length);
}


} // namespace Elements
} // namespace AllegroFlare



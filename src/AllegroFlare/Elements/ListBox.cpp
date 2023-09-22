

#include <AllegroFlare/Elements/ListBox.hpp>

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


ListBox::ListBox(AllegroFlare::FontBin* font_bin, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::Elements::DialogBoxes::Choice* choice_dialog_box, float width, float height, std::string font_name, int font_size, float text_padding_x, float text_padding_y)
   : font_bin(font_bin)
   , bitmap_bin(bitmap_bin)
   , choice_dialog_box(choice_dialog_box)
   , width(width)
   , height(height)
   , font_name(font_name)
   , font_size(font_size)
   , text_padding_x(text_padding_x)
   , text_padding_y(text_padding_y)
{
}


ListBox::~ListBox()
{
}


void ListBox::set_width(float width)
{
   this->width = width;
}


void ListBox::set_height(float height)
{
   this->height = height;
}


void ListBox::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void ListBox::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void ListBox::set_text_padding_x(float text_padding_x)
{
   this->text_padding_x = text_padding_x;
}


void ListBox::set_text_padding_y(float text_padding_y)
{
   this->text_padding_y = text_padding_y;
}


float ListBox::get_width() const
{
   return width;
}


float ListBox::get_height() const
{
   return height;
}


std::string ListBox::get_font_name() const
{
   return font_name;
}


int ListBox::get_font_size() const
{
   return font_size;
}


float ListBox::get_text_padding_x() const
{
   return text_padding_x;
}


float ListBox::get_text_padding_y() const
{
   return text_padding_y;
}


void ListBox::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[ListBox::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ListBox::render]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::render: error: guard \"choice_dialog_box\" not met");
   }
   AllegroFlare::Elements::DialogBoxFrame(width, height).render();
   draw_prompt_text();
   draw_choices_with_cursor_and_current_selection(85);
   return;
}

void ListBox::draw_prompt_text()
{
   int dialog_box_num_revealed_characters = 999;
   std::string text = obtain_choice_dialog_box_prompt();
   //float text_padding_x = 40.0f;
   //float text_padding_y = 25.0f;
   float text_box_max_width = width - (text_padding_x * 2);
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   float line_height = al_get_font_line_height(text_font);
   ALLEGRO_COLOR text_color = al_color_html("ffffff");
   //ALLEGRO_COLOR text_color = al_color_html("66a9bc");

   al_draw_multiline_text(
      text_font,
      text_color,
      text_padding_x,
      text_padding_y,
      text_box_max_width,
      line_height,
      ALLEGRO_ALIGN_LEFT,
      concat_text(text, dialog_box_num_revealed_characters).c_str()
   );
   return;
}

void ListBox::draw_choices_with_cursor_and_current_selection(float start_y)
{
   ALLEGRO_FONT* text_font = obtain_dialog_font();
   std::vector<std::pair<std::string, std::string>> options = obtain_choice_dialog_box_options();
   int current_selection_num = obtain_choice_dialog_box_cursor_position();
   float line_height = al_get_font_line_height(text_font);
   ALLEGRO_COLOR text_color_not_selected = al_color_html("dfdfdf");
   ALLEGRO_COLOR text_color_selected = al_color_html("000000");
   //ALLEGRO_COLOR text_color = al_color_html("66a9bc");
   ALLEGRO_COLOR selection_hilight_color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
   float selection_box_x_padding = 24;
   float selection_box_y_padding = 0;
   float x = 200;

   int option_num = 0;
   for (auto &option : options)
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

ALLEGRO_FONT* ListBox::obtain_dialog_font()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ListBox::obtain_dialog_font]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::obtain_dialog_font: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ListBox::obtain_dialog_font]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::obtain_dialog_font: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ListBox::obtain_dialog_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::obtain_dialog_font: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   ALLEGRO_FONT* result_font = font_bin->operator[](font_identifier.str());
   return result_font;
}

std::string ListBox::obtain_choice_dialog_box_prompt()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ListBox::obtain_choice_dialog_box_prompt]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::obtain_choice_dialog_box_prompt: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_prompt();
}

std::vector<std::pair<std::string, std::string>> ListBox::obtain_choice_dialog_box_options()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ListBox::obtain_choice_dialog_box_options]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::obtain_choice_dialog_box_options: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_options();
}

int ListBox::obtain_choice_dialog_box_cursor_position()
{
   if (!(choice_dialog_box))
   {
      std::stringstream error_message;
      error_message << "[ListBox::obtain_choice_dialog_box_cursor_position]: error: guard \"choice_dialog_box\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ListBox::obtain_choice_dialog_box_cursor_position: error: guard \"choice_dialog_box\" not met");
   }
   return choice_dialog_box->get_cursor_position();
}

std::string ListBox::concat_text(std::string source_text, int length)
{
   return source_text.substr(0, length);
}


} // namespace Elements
} // namespace AllegroFlare



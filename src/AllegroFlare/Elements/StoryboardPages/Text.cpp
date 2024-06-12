

#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


Text::Text(AllegroFlare::FontBin* font_bin, std::string text, std::string font_name, int font_size, ALLEGRO_COLOR text_color, float top_padding, float left_padding, float right_padding, float line_height_multiplier, float line_height_padding)
   : AllegroFlare::Elements::StoryboardPages::Base("Text")
   , font_bin(font_bin)
   , text(text)
   , font_name(font_name)
   , font_size(font_size)
   , text_color(text_color)
   , top_padding(top_padding)
   , left_padding(left_padding)
   , right_padding(right_padding)
   , line_height_multiplier(line_height_multiplier)
   , line_height_padding(line_height_padding)
{
}


Text::~Text()
{
}


void Text::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Text::set_text(std::string text)
{
   this->text = text;
}


void Text::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void Text::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void Text::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void Text::set_top_padding(float top_padding)
{
   this->top_padding = top_padding;
}


void Text::set_left_padding(float left_padding)
{
   this->left_padding = left_padding;
}


void Text::set_right_padding(float right_padding)
{
   this->right_padding = right_padding;
}


void Text::set_line_height_multiplier(float line_height_multiplier)
{
   this->line_height_multiplier = line_height_multiplier;
}


void Text::set_line_height_padding(float line_height_padding)
{
   this->line_height_padding = line_height_padding;
}


AllegroFlare::FontBin* Text::get_font_bin() const
{
   return font_bin;
}


std::string Text::get_text() const
{
   return text;
}


std::string Text::get_font_name() const
{
   return font_name;
}


int Text::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR Text::get_text_color() const
{
   return text_color;
}


float Text::get_top_padding() const
{
   return top_padding;
}


float Text::get_left_padding() const
{
   return left_padding;
}


float Text::get_right_padding() const
{
   return right_padding;
}


float Text::get_line_height_multiplier() const
{
   return line_height_multiplier;
}


float Text::get_line_height_padding() const
{
   return line_height_padding;
}


void Text::start()
{
   set_finished(false);
   return;
}

void Text::update()
{
   set_finished(true);
   return;
}

void Text::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Text::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Text::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Text::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Text::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   ALLEGRO_FONT *text_font = obtain_font();

   if (!text.empty())
   {
      float box_width = 1920 - (left_padding + right_padding);
      al_draw_multiline_text(
            text_font,
            text_color,
            left_padding,
            top_padding,
            box_width,
            al_get_font_line_height(text_font)*line_height_multiplier + line_height_padding,
            0,
            text.c_str()
         );
   }

   return;
}

void Text::advance()
{
   if (get_finished()) return;
   else set_finished(true);
   return;
}

ALLEGRO_FONT* Text::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::StoryboardPages::Text::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::StoryboardPages::Text::obtain_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare



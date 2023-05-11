

#include <AllegroFlare/Elements/StoryboardPages/ImageWithAdvancingText.hpp>

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


ImageWithAdvancingText::ImageWithAdvancingText(AllegroFlare::FontBin* font_bin, std::string text, std::string font_name, int font_size, ALLEGRO_COLOR text_color, float top_padding, float left_padding, float right_padding, float line_height_multiplier, float line_height_padding)
   : AllegroFlare::Elements::StoryboardPages::Base(AllegroFlare::Elements::StoryboardPages::ImageWithAdvancingText::TYPE)
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
   , revealed_characters_count(0)
{
}


ImageWithAdvancingText::~ImageWithAdvancingText()
{
}


void ImageWithAdvancingText::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ImageWithAdvancingText::set_text(std::string text)
{
   this->text = text;
}


void ImageWithAdvancingText::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void ImageWithAdvancingText::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void ImageWithAdvancingText::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void ImageWithAdvancingText::set_top_padding(float top_padding)
{
   this->top_padding = top_padding;
}


void ImageWithAdvancingText::set_left_padding(float left_padding)
{
   this->left_padding = left_padding;
}


void ImageWithAdvancingText::set_right_padding(float right_padding)
{
   this->right_padding = right_padding;
}


void ImageWithAdvancingText::set_line_height_multiplier(float line_height_multiplier)
{
   this->line_height_multiplier = line_height_multiplier;
}


void ImageWithAdvancingText::set_line_height_padding(float line_height_padding)
{
   this->line_height_padding = line_height_padding;
}


AllegroFlare::FontBin* ImageWithAdvancingText::get_font_bin() const
{
   return font_bin;
}


std::string ImageWithAdvancingText::get_text() const
{
   return text;
}


std::string ImageWithAdvancingText::get_font_name() const
{
   return font_name;
}


int ImageWithAdvancingText::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR ImageWithAdvancingText::get_text_color() const
{
   return text_color;
}


float ImageWithAdvancingText::get_top_padding() const
{
   return top_padding;
}


float ImageWithAdvancingText::get_left_padding() const
{
   return left_padding;
}


float ImageWithAdvancingText::get_right_padding() const
{
   return right_padding;
}


float ImageWithAdvancingText::get_line_height_multiplier() const
{
   return line_height_multiplier;
}


float ImageWithAdvancingText::get_line_height_padding() const
{
   return line_height_padding;
}


int ImageWithAdvancingText::get_revealed_characters_count() const
{
   return revealed_characters_count;
}


void ImageWithAdvancingText::start()
{
   revealed_characters_count = 0;
   set_finished(false);
   return;
}

void ImageWithAdvancingText::update()
{
   revealed_characters_count++;
   if (revealed_characters_count >= text.size()) set_finished(true);
   return;
}

void ImageWithAdvancingText::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[ImageWithAdvancingText::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ImageWithAdvancingText::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[ImageWithAdvancingText::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ImageWithAdvancingText::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   ALLEGRO_FONT *text_font = obtain_font();

   std::string revealed_text = generate_revealed_text();
   if (!revealed_text.empty())
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
            revealed_text.c_str()
         );
   }

   return;
}

void ImageWithAdvancingText::advance()
{
   if (get_finished()) return;
   if (!all_characters_are_revealed()) reveal_all_characters();
   else
   {
      set_finished(true);
   }

   // TODO - should this also finished = true?
   return;
}

std::string ImageWithAdvancingText::generate_revealed_text()
{
   return text.substr(0, revealed_characters_count);
}

void ImageWithAdvancingText::reveal_all_characters()
{
   revealed_characters_count = text.size();
}

bool ImageWithAdvancingText::all_characters_are_revealed()
{
   return revealed_characters_count >= text.size();
}

ALLEGRO_FONT* ImageWithAdvancingText::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ImageWithAdvancingText::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ImageWithAdvancingText::obtain_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* ImageWithAdvancingText::obtain_next_button_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[ImageWithAdvancingText::obtain_next_button_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ImageWithAdvancingText::obtain_next_button_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size+20;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare



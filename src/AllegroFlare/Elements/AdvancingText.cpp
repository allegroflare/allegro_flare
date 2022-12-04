

#include <AllegroFlare/Elements/AdvancingText.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


AdvancingText::AdvancingText(AllegroFlare::FontBin* font_bin, std::string text, std::string font_name, int font_size, ALLEGRO_COLOR text_color, float width, float line_height_multiplier, float line_height_padding)
   : font_bin(font_bin)
   , text(text)
   , font_name(font_name)
   , font_size(font_size)
   , text_color(text_color)
   , width(width)
   , line_height_multiplier(line_height_multiplier)
   , line_height_padding(line_height_padding)
   , revealed_characters_count(0)
   , finished(false)
{
}


AdvancingText::~AdvancingText()
{
}


void AdvancingText::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void AdvancingText::set_text(std::string text)
{
   this->text = text;
}


void AdvancingText::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void AdvancingText::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void AdvancingText::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void AdvancingText::set_width(float width)
{
   this->width = width;
}


void AdvancingText::set_line_height_multiplier(float line_height_multiplier)
{
   this->line_height_multiplier = line_height_multiplier;
}


void AdvancingText::set_line_height_padding(float line_height_padding)
{
   this->line_height_padding = line_height_padding;
}


void AdvancingText::set_finished(bool finished)
{
   this->finished = finished;
}


AllegroFlare::FontBin* AdvancingText::get_font_bin() const
{
   return font_bin;
}


std::string AdvancingText::get_text() const
{
   return text;
}


std::string AdvancingText::get_font_name() const
{
   return font_name;
}


int AdvancingText::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR AdvancingText::get_text_color() const
{
   return text_color;
}


float AdvancingText::get_width() const
{
   return width;
}


float AdvancingText::get_line_height_multiplier() const
{
   return line_height_multiplier;
}


float AdvancingText::get_line_height_padding() const
{
   return line_height_padding;
}


int AdvancingText::get_revealed_characters_count() const
{
   return revealed_characters_count;
}


bool AdvancingText::get_finished() const
{
   return finished;
}


void AdvancingText::start()
{
   revealed_characters_count = 0;
   finished = false;
   return;
}

void AdvancingText::update()
{
   revealed_characters_count++;
   if (revealed_characters_count >= text.size()) finished = true;
   return;
}

void AdvancingText::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AdvancingText::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancingText::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AdvancingText::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancingText::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   ALLEGRO_FONT *text_font = obtain_font();

   std::string revealed_text = generate_revealed_text();
   if (!revealed_text.empty())
   {
      al_draw_multiline_text(
            text_font,
            text_color,
            0,
            0,
            width,
            al_get_font_line_height(text_font)*line_height_multiplier + line_height_padding,
            0,
            revealed_text.c_str()
         );
   }

   return;
}

void AdvancingText::jump_to_end()
{
   if (get_finished()) return;

   reveal_all_characters();
   finished = true;

   return;
}

void AdvancingText::reveal_all_characters()
{
   revealed_characters_count = text.size();
}

bool AdvancingText::all_characters_are_revealed()
{
   return revealed_characters_count >= text.size();
}

std::string AdvancingText::generate_revealed_text()
{
   return text.substr(0, revealed_characters_count);
}

ALLEGRO_FONT* AdvancingText::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AdvancingText::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancingText::obtain_font: error: guard \"font_bin\" not met");
   }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}


} // namespace Elements
} // namespace AllegroFlare



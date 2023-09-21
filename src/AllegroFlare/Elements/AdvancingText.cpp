

#include <AllegroFlare/Elements/AdvancingText.hpp>

#include <AllegroFlare/Color.hpp>
#include <algorithm>
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
   , reveal_started_at(0.0f)
   , reveal_ended_at(0.0f)
   , reveal_rate_characters_per_second(DEFAULT_REVEAL_RATE_CHARACTERS_PER_SECOND)
   , all_characters_are_revealed(false)
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


float AdvancingText::get_reveal_started_at() const
{
   return reveal_started_at;
}


float AdvancingText::get_reveal_ended_at() const
{
   return reveal_ended_at;
}


float AdvancingText::get_reveal_rate_characters_per_second() const
{
   return reveal_rate_characters_per_second;
}


bool AdvancingText::get_all_characters_are_revealed() const
{
   return all_characters_are_revealed;
}


void AdvancingText::start()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AdvancingText::start]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancingText::start: error: guard \"al_is_system_installed()\" not met");
   }
   reveal_started_at = al_get_time(); // TODO: Replace with injected "time_now"
   reveal_ended_at = 0;
   revealed_characters_count = 0;
   all_characters_are_revealed = false;
   return;
}

void AdvancingText::set_reveal_rate_characters_per_second(float reveal_rate_characters_per_second)
{
   if (!((reveal_rate_characters_per_second >= MIN_REVEAL_RATE_CHARACTERS_PER_SECOND)))
   {
      std::stringstream error_message;
      error_message << "[AdvancingText::set_reveal_rate_characters_per_second]: error: guard \"(reveal_rate_characters_per_second >= MIN_REVEAL_RATE_CHARACTERS_PER_SECOND)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancingText::set_reveal_rate_characters_per_second: error: guard \"(reveal_rate_characters_per_second >= MIN_REVEAL_RATE_CHARACTERS_PER_SECOND)\" not met");
   }
   this->reveal_rate_characters_per_second = reveal_rate_characters_per_second;
   return;
}

void AdvancingText::update()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AdvancingText::update]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancingText::update: error: guard \"al_is_system_installed()\" not met");
   }
   if (all_characters_are_revealed) return;

   float time_now = al_get_time(); // TODO: Replace with injected "time_now"
   float age = (time_now - reveal_started_at);
   int theoretical_revealed_characters_count = (int)(age * reveal_rate_characters_per_second);
   revealed_characters_count = std::min(theoretical_revealed_characters_count, (int)text.size());
   if (revealed_characters_count >= text.size())
   {
      all_characters_are_revealed = true;
      reveal_ended_at = time_now;
   }

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

void AdvancingText::reveal_all_characters()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AdvancingText::reveal_all_characters]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AdvancingText::reveal_all_characters: error: guard \"al_is_system_installed()\" not met");
   }
   revealed_characters_count = text.size();
   all_characters_are_revealed = true;
   reveal_ended_at = al_get_time(); // TODO: Consider passing a "time_now"
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



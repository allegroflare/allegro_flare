

#include <AllegroFlare/Elements/AdvancingText.hpp>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/Color.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


AdvancingText::AdvancingText(AllegroFlare::FontBin* font_bin, std::string text, std::string font_name, int font_size, ALLEGRO_COLOR text_color, float top_padding, float left_padding, float right_padding, float line_height_multiplier, float line_height_padding)
   : font_bin(font_bin)
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


void AdvancingText::set_top_padding(float top_padding)
{
   this->top_padding = top_padding;
}


void AdvancingText::set_left_padding(float left_padding)
{
   this->left_padding = left_padding;
}


void AdvancingText::set_right_padding(float right_padding)
{
   this->right_padding = right_padding;
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


AllegroFlare::FontBin* AdvancingText::get_font_bin()
{
   return font_bin;
}


std::string AdvancingText::get_text()
{
   return text;
}


std::string AdvancingText::get_font_name()
{
   return font_name;
}


int AdvancingText::get_font_size()
{
   return font_size;
}


ALLEGRO_COLOR AdvancingText::get_text_color()
{
   return text_color;
}


float AdvancingText::get_top_padding()
{
   return top_padding;
}


float AdvancingText::get_left_padding()
{
   return left_padding;
}


float AdvancingText::get_right_padding()
{
   return right_padding;
}


float AdvancingText::get_line_height_multiplier()
{
   return line_height_multiplier;
}


float AdvancingText::get_line_height_padding()
{
   return line_height_padding;
}


int AdvancingText::get_revealed_characters_count()
{
   return revealed_characters_count;
}


bool AdvancingText::get_finished()
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
         error_message << "AdvancingText" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "AdvancingText" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
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

void AdvancingText::jump_to_end()
{
   if (get_finished()) return;

   reveal_all_characters();
   finished = true;

   return;
}

std::string AdvancingText::generate_revealed_text()
{
   return text.substr(0, revealed_characters_count);
}

void AdvancingText::reveal_all_characters()
{
   revealed_characters_count = text.size();
}

bool AdvancingText::all_characters_are_revealed()
{
   return revealed_characters_count >= text.size();
}

ALLEGRO_FONT* AdvancingText::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "AdvancingText" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size;
   return font_bin->auto_get(composite_font_str.str());
}

ALLEGRO_FONT* AdvancingText::obtain_next_button_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "AdvancingText" << "::" << "obtain_next_button_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::stringstream composite_font_str;
   composite_font_str << font_name << " " << font_size+20;
   return font_bin->auto_get(composite_font_str.str());
}
} // namespace Elements
} // namespace AllegroFlare



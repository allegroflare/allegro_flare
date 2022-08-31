

#include <AllegroFlare/Elements/StoryboardPages/AdvancingText.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro_font.h>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


AdvancingText::AdvancingText(AllegroFlare::FontBin* font_bin, std::string text, std::string font_name, int font_size, ALLEGRO_COLOR text_color, float top_padding, float left_padding, float right_padding, float line_height_multiplier, float line_height_padding)
   : AllegroFlare::Elements::StoryboardPages::Base("AdvancingText")
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


float AdvancingText::get_top_padding() const
{
   return top_padding;
}


float AdvancingText::get_left_padding() const
{
   return left_padding;
}


float AdvancingText::get_right_padding() const
{
   return right_padding;
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


void AdvancingText::start()
{
   revealed_characters_count = 0;
   set_finished(false);
   return;
}

void AdvancingText::update()
{
   revealed_characters_count++;
   if (revealed_characters_count >= text.size()) set_finished(true);
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

void AdvancingText::advance()
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


} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare



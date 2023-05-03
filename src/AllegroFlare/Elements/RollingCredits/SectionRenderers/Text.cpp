

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Text.hpp>

#include <AllegroFlare/Elements/RollingCredits/Sections/Text.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace SectionRenderers
{


int Text::_multiline_text_line_number = 0;


Text::Text(AllegroFlare::FontBin* font_bin, std::string text, std::string alignment)
   : AllegroFlare::Elements::RollingCredits::SectionRenderers::Base(AllegroFlare::Elements::RollingCredits::SectionRenderers::Text::TYPE)
   , font_bin(font_bin)
   , text(text)
   , alignment(alignment)
   , x(0.0f)
   , y(0.0f)
   , max_width(1920.0f/2.0f)
   , font_name("Inter-Regular.ttf")
   , font_size(-32)
   , text_color(ALLEGRO_COLOR{1, 1, 1, 1})
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


void Text::set_alignment(std::string alignment)
{
   this->alignment = alignment;
}


void Text::set_x(float x)
{
   this->x = x;
}


void Text::set_y(float y)
{
   this->y = y;
}


void Text::set_max_width(float max_width)
{
   this->max_width = max_width;
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


AllegroFlare::FontBin* Text::get_font_bin() const
{
   return font_bin;
}


std::string Text::get_text() const
{
   return text;
}


std::string Text::get_alignment() const
{
   return alignment;
}


float Text::get_x() const
{
   return x;
}


float Text::get_y() const
{
   return y;
}


float Text::get_max_width() const
{
   return max_width;
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


float Text::render(bool only_calculate_height_dont_render)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Text::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Text::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Text::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Text::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   ALLEGRO_FONT *font = obtain_font();
   float font_line_height = (al_get_font_line_height(font) + 1);
   if (!text.empty())
   {
      float x_offset_by_alignment = get_x_offset_by_alignment();
      if (!only_calculate_height_dont_render)
      {
         al_draw_multiline_text(
            font,
            text_color,
            x + -max_width*0.5 + x_offset_by_alignment, // box is centered in the window crawl
            y,
            max_width,
            font_line_height,
            get_al_alignment(),
            text.c_str()
         );
      }
   }
   return count_num_lines_will_render(font, max_width, text) * font_line_height;
}

bool Text::multiline_text_draw_callback(int line_num, const char* line, int size, void* extra)
{
   _multiline_text_line_number = line_num;
   return true;
}

int Text::count_num_lines_will_render(ALLEGRO_FONT* font, float max_width, std::string text)
{
   if (text.empty()) return 0;

   _multiline_text_line_number = 0;
   al_do_multiline_text(font, max_width, text.c_str(), multiline_text_draw_callback, nullptr);

   // multiline_text_line_number is now modified, and should now be set to the number of lines drawn
   return _multiline_text_line_number + 1;
}

int Text::get_al_alignment()
{
   static std::map<std::string, int> alignments = {
      { AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_LEFT,   ALLEGRO_ALIGN_LEFT },
      { AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_RIGHT,  ALLEGRO_ALIGN_RIGHT },
      { AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_CENTER, ALLEGRO_ALIGN_CENTER },
   };

   if (alignments.count(alignment) == 0)
   {
      // TODO: output a warning
      return ALLEGRO_ALIGN_LEFT;
   }
   else
   {
      return alignments[alignment];
   }
}

float Text::get_x_offset_by_alignment()
{
   std::map<std::string, float> alignment_multipliers = {
      { AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_LEFT,   0.0 },
      { AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_RIGHT,  1.0 },
      { AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_CENTER, 0.5 },
   };

   if (alignment_multipliers.count(alignment) == 0)
   {
      // TODO: output a warning
      return 0;
   }
   else
   {
      return alignment_multipliers[alignment] * max_width;
   }
}

ALLEGRO_FONT* Text::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Text::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Text::obtain_font: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   return font_bin->auto_get(font_identifier.str());
}


} // namespace SectionRenderers
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare



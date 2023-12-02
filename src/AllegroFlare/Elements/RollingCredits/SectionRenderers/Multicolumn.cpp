

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Multicolumn.hpp>

#include <iostream>
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


Multicolumn::Multicolumn(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<std::string, std::string>> elements, float x, float y, float gutter_width)
   : AllegroFlare::Elements::RollingCredits::SectionRenderers::Base(AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn::TYPE)
   , font_bin(font_bin)
   , elements(elements)
   , x(x)
   , y(y)
   , font_name("Inter-Regular.ttf")
   , font_size(-32)
   , text_color(ALLEGRO_COLOR{1, 1, 1, 1})
   , gutter_width(gutter_width)
{
}


Multicolumn::~Multicolumn()
{
}


void Multicolumn::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Multicolumn::set_elements(std::vector<std::tuple<std::string, std::string>> elements)
{
   this->elements = elements;
}


void Multicolumn::set_x(float x)
{
   this->x = x;
}


void Multicolumn::set_y(float y)
{
   this->y = y;
}


void Multicolumn::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void Multicolumn::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void Multicolumn::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void Multicolumn::set_gutter_width(float gutter_width)
{
   this->gutter_width = gutter_width;
}


AllegroFlare::FontBin* Multicolumn::get_font_bin() const
{
   return font_bin;
}


std::vector<std::tuple<std::string, std::string>> Multicolumn::get_elements() const
{
   return elements;
}


float Multicolumn::get_x() const
{
   return x;
}


float Multicolumn::get_y() const
{
   return y;
}


std::string Multicolumn::get_font_name() const
{
   return font_name;
}


int Multicolumn::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR Multicolumn::get_text_color() const
{
   return text_color;
}


float Multicolumn::get_gutter_width() const
{
   return gutter_width;
}


float Multicolumn::render(bool only_calculate_height_dont_render)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Multicolumn::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Multicolumn::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Multicolumn::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Multicolumn::render: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   ALLEGRO_FONT *font = obtain_font();
   float cursor_y = 0;
   float h_gutter_width = gutter_width * 0.5;
   float y_spacing = al_get_font_line_height(font) + 4;
   // float line_height = al_get_font_line_height(font); // for multiline-text
   for (auto &element : elements)
   {
      if (!only_calculate_height_dont_render)
      {
         std::string label = std::get<0>(element);
         std::string value = std::get<1>(element);

         // draw the label
         al_draw_text(font, text_color, x - h_gutter_width, y + cursor_y, ALLEGRO_ALIGN_RIGHT, label.c_str());

         // draw the value
         al_draw_text(font, text_color, x + h_gutter_width, y + cursor_y, ALLEGRO_ALIGN_LEFT, value.c_str());
      }

      cursor_y += y_spacing;
   }
   return cursor_y;
}

ALLEGRO_FONT* Multicolumn::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Multicolumn::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Multicolumn::obtain_font: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   return font_bin->auto_get(font_identifier.str());
}


} // namespace SectionRenderers
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare



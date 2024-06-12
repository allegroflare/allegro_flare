

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/ColumnWithLabels.hpp>

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


ColumnWithLabels::ColumnWithLabels(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<std::string, std::string>> elements, float x, float y, float gutter_width)
   : AllegroFlare::Elements::RollingCredits::SectionRenderers::Base("ColumnWithLabels")
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


ColumnWithLabels::~ColumnWithLabels()
{
}


void ColumnWithLabels::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ColumnWithLabels::set_elements(std::vector<std::tuple<std::string, std::string>> elements)
{
   this->elements = elements;
}


void ColumnWithLabels::set_x(float x)
{
   this->x = x;
}


void ColumnWithLabels::set_y(float y)
{
   this->y = y;
}


void ColumnWithLabels::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void ColumnWithLabels::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void ColumnWithLabels::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


void ColumnWithLabels::set_gutter_width(float gutter_width)
{
   this->gutter_width = gutter_width;
}


AllegroFlare::FontBin* ColumnWithLabels::get_font_bin() const
{
   return font_bin;
}


std::vector<std::tuple<std::string, std::string>> ColumnWithLabels::get_elements() const
{
   return elements;
}


float ColumnWithLabels::get_x() const
{
   return x;
}


float ColumnWithLabels::get_y() const
{
   return y;
}


std::string ColumnWithLabels::get_font_name() const
{
   return font_name;
}


int ColumnWithLabels::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR ColumnWithLabels::get_text_color() const
{
   return text_color;
}


float ColumnWithLabels::get_gutter_width() const
{
   return gutter_width;
}


float ColumnWithLabels::render(bool only_calculate_height_dont_render)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels::render]: error: guard \"al_is_font_addon_initialized()\" not met");
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

ALLEGRO_FONT* ColumnWithLabels::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels::obtain_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   return font_bin->auto_get(font_identifier.str());
}


} // namespace SectionRenderers
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare





#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Multicolumn.hpp>

#include <AllegroFlare/Useful.hpp>
#include <algorithm>
#include <allegro5/allegro_primitives.h>
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


Multicolumn::Multicolumn(AllegroFlare::FontBin* font_bin, std::vector<std::vector<std::string>> elements, float x, float y, float width, float gutter_width)
   : AllegroFlare::Elements::RollingCredits::SectionRenderers::Base(AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn::TYPE)
   , font_bin(font_bin)
   , elements(elements)
   , x(x)
   , y(y)
   , width(width)
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


void Multicolumn::set_elements(std::vector<std::vector<std::string>> elements)
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


void Multicolumn::set_width(float width)
{
   this->width = width;
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


std::vector<std::vector<std::string>> Multicolumn::get_elements() const
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


float Multicolumn::get_width() const
{
   return width;
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
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Multicolumn::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Multicolumn::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   bool draw_debugging_guides = true;
   ALLEGRO_FONT *font = obtain_font();
   float cursor_x = 0;
   float cursor_y = 0;
   float h_gutter_width = gutter_width * 0.5;
   float y_spacing = al_get_font_line_height(font) + 4;
   // float line_height = al_get_font_line_height(font); // for multiline-text
   float column_width = (width - (gutter_width * (elements.size() - 1))) / (float)elements.size();
   float xx = (x - width / 2);
   std::vector<float> column_heights;
   for (auto &column : elements)
   {
      for (auto &column_element : column)
      {
         if (!only_calculate_height_dont_render)
         {
            al_draw_text(font, text_color, xx + cursor_x, y + cursor_y, ALLEGRO_ALIGN_LEFT, column_element.c_str());
         }
         cursor_y += y_spacing;
      }

      // Store the column heights
      float column_height = cursor_y;
      column_heights.push_back(column_height);

      // Render debug rectangle container for this column
      if (draw_debugging_guides)
      {
         al_draw_rectangle(
            xx + cursor_x,
            y,
            xx + cursor_x + column_width,
            y+column_height,
            ALLEGRO_COLOR{0.65, 0.69, 0.9, 1.0},
            2.0f
         );
      }

      // Advance to the next column
      cursor_y = 0;
      cursor_x += (column_width + gutter_width);
   }

   // Render more debugging
   if (draw_debugging_guides)
   {
      AllegroFlare::draw_crosshair(x, y, ALLEGRO_COLOR{0.9, 0.3, 0.25, 1.0}, 50);
   }

   if (column_heights.empty()) return 0; // TODO: Test this
   return *std::max_element(column_heights.begin(), column_heights.end()); // TODO: Test this
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



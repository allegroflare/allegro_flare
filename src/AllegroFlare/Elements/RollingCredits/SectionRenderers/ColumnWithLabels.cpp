

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/ColumnWithLabels.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace SectionRenderers
{


ColumnWithLabels::ColumnWithLabels(AllegroFlare::FontBin* font_bin, std::vector<std::tuple<std::string, std::string>> elements, float x, float y, float gutter_width)
   : font_bin(font_bin)
   , elements(elements)
   , x(x)
   , y(y)
   , font_name("Inter-Medium.ttf")
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


AllegroFlare::FontBin* ColumnWithLabels::get_font_bin()
{
   return font_bin;
}


std::vector<std::tuple<std::string, std::string>> ColumnWithLabels::get_elements()
{
   return elements;
}


float ColumnWithLabels::get_x()
{
   return x;
}


float ColumnWithLabels::get_y()
{
   return y;
}


std::string ColumnWithLabels::get_font_name()
{
   return font_name;
}


int ColumnWithLabels::get_font_size()
{
   return font_size;
}


ALLEGRO_COLOR ColumnWithLabels::get_text_color()
{
   return text_color;
}


float ColumnWithLabels::get_gutter_width()
{
   return gutter_width;
}


float ColumnWithLabels::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "ColumnWithLabels" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "ColumnWithLabels" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_FONT *font = obtain_font();
   float cursor_y = 0;
   float h_gutter_width = gutter_width * 0.5;
   float y_spacing = al_get_font_line_height(font) + 4;
   // float line_height = al_get_font_line_height(font); // for multiline-text
   for (auto &element : elements)
   {
      std::string label = std::get<0>(element);
      std::string value = std::get<1>(element);

      // draw the label
      al_draw_text(font, text_color, x - h_gutter_width, y + cursor_y, ALLEGRO_ALIGN_RIGHT, label.c_str());

      // draw the value
      al_draw_text(font, text_color, x + h_gutter_width, y + cursor_y, ALLEGRO_ALIGN_LEFT, value.c_str());

      cursor_y += y_spacing;
   }
   return al_get_font_line_height(font);
}

ALLEGRO_FONT* ColumnWithLabels::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "ColumnWithLabels" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   return font_bin->auto_get(font_identifier.str());
}
} // namespace SectionRenderers
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare



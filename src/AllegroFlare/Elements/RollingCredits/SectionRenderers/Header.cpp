

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Header.hpp>
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


Header::Header(AllegroFlare::FontBin* font_bin, std::string text)
   : font_bin(font_bin)
   , text(text)
   , x(0.0f)
   , y(0.0f)
   , font_name("Inter-Medium.ttf")
   , font_size(-32)
   , text_color(ALLEGRO_COLOR{1, 1, 1, 1})
{
}


Header::~Header()
{
}


void Header::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Header::set_text(std::string text)
{
   this->text = text;
}


void Header::set_x(float x)
{
   this->x = x;
}


void Header::set_y(float y)
{
   this->y = y;
}


void Header::set_font_name(std::string font_name)
{
   this->font_name = font_name;
}


void Header::set_font_size(int font_size)
{
   this->font_size = font_size;
}


void Header::set_text_color(ALLEGRO_COLOR text_color)
{
   this->text_color = text_color;
}


AllegroFlare::FontBin* Header::get_font_bin()
{
   return font_bin;
}


std::string Header::get_text()
{
   return text;
}


float Header::get_x()
{
   return x;
}


float Header::get_y()
{
   return y;
}


std::string Header::get_font_name()
{
   return font_name;
}


int Header::get_font_size()
{
   return font_size;
}


ALLEGRO_COLOR Header::get_text_color()
{
   return text_color;
}


float Header::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Header" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Header" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_FONT *font = obtain_font();
   if (!text.empty())
   {
      al_draw_text(font, text_color, x, y, ALLEGRO_ALIGN_CENTER, text.c_str());
   }
   return al_get_font_line_height(font);
}

ALLEGRO_FONT* Header::obtain_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Header" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
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



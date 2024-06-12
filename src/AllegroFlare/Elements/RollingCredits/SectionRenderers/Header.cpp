

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Header.hpp>

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


Header::Header(AllegroFlare::FontBin* font_bin, std::string text)
   : AllegroFlare::Elements::RollingCredits::SectionRenderers::Base("Header")
   , font_bin(font_bin)
   , text(text)
   , x(0.0f)
   , y(0.0f)
   , font_name("Inter-Regular.ttf")
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


AllegroFlare::FontBin* Header::get_font_bin() const
{
   return font_bin;
}


std::string Header::get_text() const
{
   return text;
}


float Header::get_x() const
{
   return x;
}


float Header::get_y() const
{
   return y;
}


std::string Header::get_font_name() const
{
   return font_name;
}


int Header::get_font_size() const
{
   return font_size;
}


ALLEGRO_COLOR Header::get_text_color() const
{
   return text_color;
}


float Header::render(bool only_calculate_height_dont_render)
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::SectionRenderers::Header::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::SectionRenderers::Header::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::SectionRenderers::Header::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::SectionRenderers::Header::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   ALLEGRO_FONT *font = obtain_font();
   if (!text.empty())
   {
      if (!only_calculate_height_dont_render)
      {
         al_draw_text(font, text_color, x, y, ALLEGRO_ALIGN_CENTER, text.c_str());
      }
   }
   return al_get_font_line_height(font);
}

ALLEGRO_FONT* Header::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::SectionRenderers::Header::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::SectionRenderers::Header::obtain_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier;
   font_identifier << font_name << " " << font_size;
   return font_bin->auto_get(font_identifier.str());
}


} // namespace SectionRenderers
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare



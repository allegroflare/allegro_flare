

#include <AllegroFlare/Elements/HealthBars/Hearts.hpp>

#include <AllegroFlare/FontAwesome.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace HealthBars
{


Hearts::Hearts(AllegroFlare::FontBin* font_bin, int max, int value, ALLEGRO_COLOR fill_color, ALLEGRO_COLOR empty_color, ALLEGRO_COLOR outline_color, int heart_size, float heart_spacing, bool drawing_outline)
   : AllegroFlare::Elements::Base()
   , font_bin(font_bin)
   , max(max)
   , value(value)
   , fill_color(fill_color)
   , empty_color(empty_color)
   , outline_color(outline_color)
   , heart_size(heart_size)
   , heart_spacing(heart_spacing)
   , drawing_outline(drawing_outline)
   , font_awesome_solid_font_name("fa-solid-900.ttf")
   , font_awesome_outline_font_name("fa-regular-400.ttf")
{
}


Hearts::~Hearts()
{
}


void Hearts::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Hearts::set_max(int max)
{
   this->max = max;
}


void Hearts::set_value(int value)
{
   this->value = value;
}


void Hearts::set_fill_color(ALLEGRO_COLOR fill_color)
{
   this->fill_color = fill_color;
}


void Hearts::set_empty_color(ALLEGRO_COLOR empty_color)
{
   this->empty_color = empty_color;
}


void Hearts::set_outline_color(ALLEGRO_COLOR outline_color)
{
   this->outline_color = outline_color;
}


void Hearts::set_heart_size(int heart_size)
{
   this->heart_size = heart_size;
}


void Hearts::set_heart_spacing(float heart_spacing)
{
   this->heart_spacing = heart_spacing;
}


void Hearts::set_drawing_outline(bool drawing_outline)
{
   this->drawing_outline = drawing_outline;
}


int Hearts::get_max() const
{
   return max;
}


int Hearts::get_value() const
{
   return value;
}


ALLEGRO_COLOR Hearts::get_fill_color() const
{
   return fill_color;
}


ALLEGRO_COLOR Hearts::get_empty_color() const
{
   return empty_color;
}


ALLEGRO_COLOR Hearts::get_outline_color() const
{
   return outline_color;
}


int Hearts::get_heart_size() const
{
   return heart_size;
}


float Hearts::get_heart_spacing() const
{
   return heart_spacing;
}


bool Hearts::get_drawing_outline() const
{
   return drawing_outline;
}


void Hearts::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::HealthBars::Hearts::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::HealthBars::Hearts::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::HealthBars::Hearts::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::HealthBars::Hearts::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(al_is_ttf_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::HealthBars::Hearts::render]: error: guard \"al_is_ttf_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::HealthBars::Hearts::render]: error: guard \"al_is_ttf_addon_initialized()\" not met");
   }
   ALLEGRO_FONT *font_awesome_solid_font = obtain_font_awesome_solid_font();
   ALLEGRO_FONT *font_awesome_outline_font = obtain_font_awesome_outline_font();
   const uint32_t heart_glyph = AllegroFlare::FontAwesome::heart;
   const uint32_t heart_empty_glyph = AllegroFlare::FontAwesome::heart;
   const uint32_t outline_heart_glyph = 0xf004;

   get_placement_ref().start_transform();

   for (int i=0; i<max; i++)
   {
      if (i <= (value - 1))
      {
         // draw filled heart
         draw_unicode_character(
            font_awesome_solid_font,
            fill_color,
            heart_glyph,
            ALLEGRO_ALIGN_CENTRE,
            i*heart_spacing
         );
      }
      else
      {
         // draw empty heart
         draw_unicode_character(
            font_awesome_solid_font,
            empty_color,
            heart_glyph,
            ALLEGRO_ALIGN_CENTRE,
            i*heart_spacing
         );
      }
   }

   if (drawing_outline)
   {
      for (int i=0; i<max; i++)
      {
         // draw outline stroke heart
         draw_unicode_character(
            font_awesome_outline_font,
            outline_color,
            outline_heart_glyph,
            ALLEGRO_ALIGN_CENTRE,
            i*heart_spacing,
            -1
         );
      }
   }

   get_placement_ref().restore_transform();
   return;
}

void Hearts::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}

ALLEGRO_FONT* Hearts::obtain_font_awesome_solid_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::HealthBars::Hearts::obtain_font_awesome_solid_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::HealthBars::Hearts::obtain_font_awesome_solid_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier_and_size;
   font_identifier_and_size << font_awesome_solid_font_name << " " << heart_size;
   return font_bin->auto_get(font_identifier_and_size.str());
}

ALLEGRO_FONT* Hearts::obtain_font_awesome_outline_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::HealthBars::Hearts::obtain_font_awesome_outline_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::HealthBars::Hearts::obtain_font_awesome_outline_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier_and_size;
   font_identifier_and_size << font_awesome_outline_font_name << " " << (heart_size+2);
   return font_bin->auto_get(font_identifier_and_size.str());
}


} // namespace HealthBars
} // namespace Elements
} // namespace AllegroFlare



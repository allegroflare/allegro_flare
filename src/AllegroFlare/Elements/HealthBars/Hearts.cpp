

#include <AllegroFlare/Elements/HealthBars/Hearts.hpp>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace HealthBars
{


Hearts::Hearts(AllegroFlare::FontBin* font_bin, int max, int value, ALLEGRO_COLOR fill_color, ALLEGRO_COLOR empty_color, float heart_size, float heart_spacing)
   : AllegroFlare::Elements::Base()
   , font_bin(font_bin)
   , max(max)
   , value(value)
   , fill_color(fill_color)
   , empty_color(empty_color)
   , heart_size(heart_size)
   , heart_spacing(heart_spacing)
   , font_awesome_font_name("fa-solid-900.ttf")
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


void Hearts::set_heart_size(float heart_size)
{
   this->heart_size = heart_size;
}


void Hearts::set_heart_spacing(float heart_spacing)
{
   this->heart_spacing = heart_spacing;
}


int Hearts::get_max()
{
   return max;
}


int Hearts::get_value()
{
   return value;
}


ALLEGRO_COLOR Hearts::get_fill_color()
{
   return fill_color;
}


ALLEGRO_COLOR Hearts::get_empty_color()
{
   return empty_color;
}


float Hearts::get_heart_size()
{
   return heart_size;
}


float Hearts::get_heart_spacing()
{
   return heart_spacing;
}


void Hearts::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Hearts" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Hearts" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_ttf_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Hearts" << "::" << "render" << ": error: " << "guard \"al_is_ttf_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   ALLEGRO_COLOR outline_color = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_FONT *font_awesome_font = obtain_font_awesome_font();

   get_placement_ref().start_transform();

   for (int i=0; i<max; i++)
   {
      if (i <= value)
      {
         // draw filled heart
         draw_unicode_character(font_awesome_font, fill_color, 61444, ALLEGRO_ALIGN_CENTRE, i*heart_spacing);
      }
      else
      {
         // draw empty heart
         draw_unicode_character(font_awesome_font, empty_color, 61444, ALLEGRO_ALIGN_CENTRE, i*heart_spacing);
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

ALLEGRO_FONT* Hearts::obtain_font_awesome_font()
{
   if (!(font_bin))
      {
         std::stringstream error_message;
         error_message << "Hearts" << "::" << "obtain_font_awesome_font" << ": error: " << "guard \"font_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   std::stringstream font_identifier_and_size;
   font_identifier_and_size << font_awesome_font_name << " " << heart_size;
   return font_bin->auto_get(font_identifier_and_size.str());
}
} // namespace HealthBars
} // namespace Elements
} // namespace AllegroFlare



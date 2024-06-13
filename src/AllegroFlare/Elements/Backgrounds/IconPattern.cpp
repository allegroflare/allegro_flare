

#include <AllegroFlare/Elements/Backgrounds/IconPattern.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


IconPattern::IconPattern(AllegroFlare::FontBin* font_bin)
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::IconPattern::TYPE)
   , font_bin(font_bin)
   , background_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0})
   , icon_a(0)
   , icon_b(0)
   , font_awesome_font_name("fa-solid-900.ttf")
   , time(0)
{
}


IconPattern::~IconPattern()
{
}


void IconPattern::set_background_color(ALLEGRO_COLOR background_color)
{
   this->background_color = background_color;
}


ALLEGRO_COLOR IconPattern::get_background_color() const
{
   return background_color;
}


void IconPattern::update()
{
   time = al_get_time();
   return;
}

void IconPattern::render()
{
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::IconPattern::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::IconPattern::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::IconPattern::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::IconPattern::render]: error: guard \"font_bin\" not met");
   }
   al_clear_to_color(background_color);
   ALLEGRO_FONT *font = obtain_font_awesome_font();
   //ALLEGRO_COLOR font_color = AllegroFlare::Color::HotPink;

   int display_width = 1920;
   int display_height = 1080;

   int spacing = 110;
   float offset_x = spacing * 0.5;
   float offset_y = spacing * 0.25;
   AllegroFlare::Placement2D place;
   place.rotation = -0.25;
   place.size = {(float)display_width, (float)display_height};
   place.scale = {1.3, 1.3};
   place.position = place.size / 2;

   place.start_transform();
   int step = 0;
   for (int step_y=-1; (step_y*spacing)<display_height; step_y++)
      for (int step_x=-1; (step_x*spacing)<display_width; step_x++)
      {
         ALLEGRO_COLOR font_color = AllegroFlare::Color::HotPink;
         float x = step_x * spacing + offset_x;
         float y = step_y * spacing + offset_y;
         uint32_t icon = 0xf6be;

         if (step_y % 2 == 0) x += spacing / 2;
         if (step % 3 == 0) icon = 0xf002;
         if (step % 2 == 0) font_color = AllegroFlare::color::color(font_color, 0.6);

         draw_unicode_character(font, font_color, icon, ALLEGRO_ALIGN_CENTER, x, y);
         step++;
      }
   place.restore_transform();
   return;
}

void IconPattern::draw_unicode_character(ALLEGRO_FONT* font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
   return;
}

ALLEGRO_FONT* IconPattern::obtain_font_awesome_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::IconPattern::obtain_font_awesome_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::IconPattern::obtain_font_awesome_font]: error: guard \"font_bin\" not met");
   }
   std::stringstream font_identifier_and_size;
   font_identifier_and_size << font_awesome_font_name << " " << -40;
   return font_bin->auto_get(font_identifier_and_size.str());
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare



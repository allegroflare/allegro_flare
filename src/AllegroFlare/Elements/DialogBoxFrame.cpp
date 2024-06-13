

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>

#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


DialogBoxFrame::DialogBoxFrame(float width, float height)
   : width(width)
   , height(height)
   , backfill_opacity(0.8)
   , backfill_color(DEFAULT_BACKFILL_COLOR)
   , border_color(DEFAULT_BORDER_COLOR)
   , opacity(1.0f)
   , roundness(8.0f)
   , border_thickness(6.0f)
{
}


DialogBoxFrame::~DialogBoxFrame()
{
}


void DialogBoxFrame::set_width(float width)
{
   this->width = width;
}


void DialogBoxFrame::set_height(float height)
{
   this->height = height;
}


void DialogBoxFrame::set_backfill_opacity(float backfill_opacity)
{
   this->backfill_opacity = backfill_opacity;
}


void DialogBoxFrame::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void DialogBoxFrame::set_border_color(ALLEGRO_COLOR border_color)
{
   this->border_color = border_color;
}


void DialogBoxFrame::set_opacity(float opacity)
{
   this->opacity = opacity;
}


void DialogBoxFrame::set_roundness(float roundness)
{
   this->roundness = roundness;
}


void DialogBoxFrame::set_border_thickness(float border_thickness)
{
   this->border_thickness = border_thickness;
}


float DialogBoxFrame::get_width() const
{
   return width;
}


float DialogBoxFrame::get_height() const
{
   return height;
}


float DialogBoxFrame::get_opacity() const
{
   return opacity;
}


float DialogBoxFrame::get_roundness() const
{
   return roundness;
}


float DialogBoxFrame::get_border_thickness() const
{
   return border_thickness;
}


void DialogBoxFrame::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxFrame::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxFrame::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxFrame::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxFrame::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::DialogBoxFrame::render]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::DialogBoxFrame::render]: error: guard \"al_get_current_display()\" not met");
   }
   float border_inner_padding = border_thickness * 2.25;
   ALLEGRO_COLOR backfill_color_with_opacity =
      AllegroFlare::color::color(backfill_color, backfill_opacity * opacity);
   ALLEGRO_COLOR border_color_with_opacity = AllegroFlare::color::color(border_color, opacity);

   // draw backfill
   al_draw_filled_rounded_rectangle(
      0,
      0,
      width,
      height,
      roundness * 1.0,
      roundness * 1.0,
      backfill_color_with_opacity
   );

   // draw "inner" backfill
   al_draw_filled_rounded_rectangle(
      0 + border_inner_padding,
      0 + border_inner_padding,
      width - border_inner_padding,
      height - border_inner_padding,
      roundness * 0.5,
      roundness * 0.5,
      backfill_color_with_opacity
   );

   // draw border
   al_draw_rounded_rectangle(
      0,
      0,
      width,
      height,
      roundness,
      roundness,
      border_color_with_opacity,
      border_thickness
   );

   return;
}


} // namespace Elements
} // namespace AllegroFlare



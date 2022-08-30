

#include <AllegroFlare/Elements/DialogBoxFrame.hpp>
#include <AllegroFlare/Color.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


DialogBoxFrame::DialogBoxFrame(float width, float height)
   : width(width)
   , height(height)
   , backfill_opacity(0.8)
   , backfill_color(ALLEGRO_COLOR{0.065f, 0.065f, 0.065f, 0.9f})
   , border_color(al_color_html("909090"))
   , opacity(1.0f)
{
}


DialogBoxFrame::~DialogBoxFrame()
{
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


void DialogBoxFrame::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFrame" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFrame" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "DialogBoxFrame" << "::" << "render" << ": error: " << "guard \"al_get_current_display()\" not met";
      throw std::runtime_error(error_message.str());
   }
   float roundness = 13.0f;
   float border_thickness = 6.0f;
   float border_inner_padding = border_thickness * 2.25;
   ALLEGRO_COLOR backfill_color_with_opacity = AllegroFlare::color::color(backfill_color, backfill_opacity * opacity);
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



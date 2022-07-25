

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
   , opacity(0.8)
   , fill_color(ALLEGRO_COLOR{0.05f, 0.02f, 0.12f, 1.0f})
   , border_color(al_color_html("345761"))
{
}


DialogBoxFrame::~DialogBoxFrame()
{
}


void DialogBoxFrame::set_opacity(float opacity)
{
   this->opacity = opacity;
}


void DialogBoxFrame::set_fill_color(ALLEGRO_COLOR fill_color)
{
   this->fill_color = fill_color;
}


void DialogBoxFrame::set_border_color(ALLEGRO_COLOR border_color)
{
   this->border_color = border_color;
}


float DialogBoxFrame::get_width()
{
   return width;
}


float DialogBoxFrame::get_height()
{
   return height;
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
   float roundness = 18.0f;
   float border_thickness = 6.0f;
   float border_inner_padding = border_thickness * 2.5;
   //ALLEGRO_COLOR fill_color = al_color_html("162428");
   //ALLEGRO_COLOR fill_color = ALLEGRO_COLOR{0.02f*opacity, 0.0f*opacity, 0.1f*opacity, opacity};
   //ALLEGRO_COLOR border_color = al_color_html("244751");
   ALLEGRO_COLOR fill_color_with_opacity = AllegroFlare::color::color(fill_color, opacity);

   // draw backfill
   al_draw_filled_rounded_rectangle(
      0,
      0,
      width,
      height,
      roundness * 1.0,
      roundness * 1.0,
      fill_color_with_opacity
   );
   // draw "inner" backfill
   al_draw_filled_rounded_rectangle(
      0 + border_inner_padding,
      0 + border_inner_padding,
      width - border_inner_padding,
      height - border_inner_padding,
      roundness * 0.5,
      roundness * 0.5,
      fill_color_with_opacity
   );
   // draw border
   al_draw_rounded_rectangle(
      0,
      0,
      width,
      height,
      roundness,
      roundness,
      border_color,
      border_thickness
   );

   return;
}
} // namespace Elements
} // namespace AllegroFlare



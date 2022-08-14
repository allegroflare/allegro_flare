

#include <AllegroFlare/Elements/Scrollbar.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


Scrollbar::Scrollbar(float x, float y, float height, float position, ALLEGRO_COLOR bar_color, ALLEGRO_COLOR handle_color, float handle_height, float rail_thickness, float handle_thickness)
   : x(x)
   , y(y)
   , height(height)
   , position(position)
   , bar_color(bar_color)
   , handle_color(handle_color)
   , handle_height(handle_height)
   , rail_thickness(rail_thickness)
   , handle_thickness(handle_thickness)
{
}


Scrollbar::~Scrollbar()
{
}


void Scrollbar::set_x(float x)
{
   this->x = x;
}


void Scrollbar::set_y(float y)
{
   this->y = y;
}


void Scrollbar::set_height(float height)
{
   this->height = height;
}


void Scrollbar::set_position(float position)
{
   this->position = position;
}


void Scrollbar::set_bar_color(ALLEGRO_COLOR bar_color)
{
   this->bar_color = bar_color;
}


void Scrollbar::set_handle_color(ALLEGRO_COLOR handle_color)
{
   this->handle_color = handle_color;
}


void Scrollbar::set_handle_height(float handle_height)
{
   this->handle_height = handle_height;
}


void Scrollbar::set_rail_thickness(float rail_thickness)
{
   this->rail_thickness = rail_thickness;
}


void Scrollbar::set_handle_thickness(float handle_thickness)
{
   this->handle_thickness = handle_thickness;
}


float Scrollbar::get_x()
{
   return x;
}


float Scrollbar::get_y()
{
   return y;
}


float Scrollbar::get_height()
{
   return height;
}


float Scrollbar::get_position()
{
   return position;
}


ALLEGRO_COLOR Scrollbar::get_bar_color()
{
   return bar_color;
}


ALLEGRO_COLOR Scrollbar::get_handle_color()
{
   return handle_color;
}


float Scrollbar::get_handle_height()
{
   return handle_height;
}


float Scrollbar::get_rail_thickness()
{
   return rail_thickness;
}


float Scrollbar::get_handle_thickness()
{
   return handle_thickness;
}


void Scrollbar::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Scrollbar" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Scrollbar" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   float h_rail_thickness = rail_thickness * 0.5;
   float h_handle_thickness = handle_thickness * 0.5;
   float denormalized_handle_position = position * height;

   // draw the rail
   al_draw_filled_rounded_rectangle(
      x-h_rail_thickness,
      y,
      x+h_rail_thickness,
      y+height,
      h_rail_thickness,
      h_rail_thickness,
      bar_color
   );

   // draw the handle
   al_draw_filled_rounded_rectangle(
      x-h_handle_thickness,
      y+denormalized_handle_position - handle_height * 0.5,
      x+h_handle_thickness,
      y+denormalized_handle_position + handle_height * 0.5,
      h_handle_thickness,
      h_handle_thickness,
      handle_color
   );
   return;
}
} // namespace Elements
} // namespace AllegroFlare



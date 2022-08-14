

#include <AllegroFlare/Elements/ScrollBar.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{


ScrollBar::ScrollBar(float x, float y, float height, float handle_height, float position, float rail_thickness, float handle_thickness)
   : x(x)
   , y(y)
   , height(height)
   , handle_height(handle_height)
   , position(position)
   , rail_thickness(rail_thickness)
   , handle_thickness(handle_thickness)
{
}


ScrollBar::~ScrollBar()
{
}


void ScrollBar::set_x(float x)
{
   this->x = x;
}


void ScrollBar::set_y(float y)
{
   this->y = y;
}


void ScrollBar::set_height(float height)
{
   this->height = height;
}


void ScrollBar::set_handle_height(float handle_height)
{
   this->handle_height = handle_height;
}


void ScrollBar::set_position(float position)
{
   this->position = position;
}


void ScrollBar::set_rail_thickness(float rail_thickness)
{
   this->rail_thickness = rail_thickness;
}


void ScrollBar::set_handle_thickness(float handle_thickness)
{
   this->handle_thickness = handle_thickness;
}


float ScrollBar::get_x()
{
   return x;
}


float ScrollBar::get_y()
{
   return y;
}


float ScrollBar::get_height()
{
   return height;
}


float ScrollBar::get_handle_height()
{
   return handle_height;
}


float ScrollBar::get_position()
{
   return position;
}


float ScrollBar::get_rail_thickness()
{
   return rail_thickness;
}


float ScrollBar::get_handle_thickness()
{
   return handle_thickness;
}


void ScrollBar::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "ScrollBar" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_primitives_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "ScrollBar" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   float h_rail_thickness = rail_thickness * 0.5;
   float h_handle_thickness = handle_thickness * 0.5;
   ALLEGRO_COLOR bar_color = ALLEGRO_COLOR{0.4, 0.405, 0.41, 1.0};
   ALLEGRO_COLOR handle_color = ALLEGRO_COLOR{0.7, 0.705, 0.71, 1.0};
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



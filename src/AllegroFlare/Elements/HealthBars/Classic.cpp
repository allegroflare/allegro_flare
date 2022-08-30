

#include <AllegroFlare/Elements/HealthBars/Classic.hpp>
#include <allegro5/allegro_primitives.h>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace Elements
{
namespace HealthBars
{


Classic::Classic(int max, int value, ALLEGRO_COLOR fill_color, float bar_width, float bar_spacing, float bar_height, float bar_stroke_thickness)
   : AllegroFlare::Elements::Base()
   , max(max)
   , value(value)
   , fill_color(fill_color)
   , bar_width(bar_width)
   , bar_spacing(bar_spacing)
   , bar_height(bar_height)
   , bar_stroke_thickness(bar_stroke_thickness)
{
}


Classic::~Classic()
{
}


void Classic::set_max(int max)
{
   this->max = max;
}


void Classic::set_value(int value)
{
   this->value = value;
}


void Classic::set_fill_color(ALLEGRO_COLOR fill_color)
{
   this->fill_color = fill_color;
}


void Classic::set_bar_width(float bar_width)
{
   this->bar_width = bar_width;
}


void Classic::set_bar_spacing(float bar_spacing)
{
   this->bar_spacing = bar_spacing;
}


void Classic::set_bar_height(float bar_height)
{
   this->bar_height = bar_height;
}


void Classic::set_bar_stroke_thickness(float bar_stroke_thickness)
{
   this->bar_stroke_thickness = bar_stroke_thickness;
}


int Classic::get_max() const
{
   return max;
}


int Classic::get_value() const
{
   return value;
}


ALLEGRO_COLOR Classic::get_fill_color() const
{
   return fill_color;
}


float Classic::get_bar_width() const
{
   return bar_width;
}


float Classic::get_bar_spacing() const
{
   return bar_spacing;
}


float Classic::get_bar_height() const
{
   return bar_height;
}


float Classic::get_bar_stroke_thickness() const
{
   return bar_stroke_thickness;
}


void Classic::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Classic" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Classic" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   float h_thickness = bar_stroke_thickness * 0.5;
   ALLEGRO_COLOR outline_color = ALLEGRO_COLOR{1, 1, 1, 1};

   get_placement_ref().start_transform();

   for (int i=0; i<max; i++)
   {
      if (i <= value)
      {
         al_draw_filled_rectangle(i*bar_spacing, 0, i*bar_spacing+bar_width, bar_height, fill_color);
      }
      else
      {
         al_draw_rectangle(
               i*bar_spacing + h_thickness,
               0 + h_thickness,
               i*bar_spacing+bar_width - h_thickness,
               bar_height - h_thickness,
               outline_color,
               bar_stroke_thickness
            );
      }
   }
   get_placement_ref().restore_transform();
   return;
}
} // namespace HealthBars
} // namespace Elements
} // namespace AllegroFlare



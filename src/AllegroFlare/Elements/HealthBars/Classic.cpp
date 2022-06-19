

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


Classic::Classic(int max, int value, ALLEGRO_COLOR color, float bar_width, float bar_spacing, float bar_height, float bar_thickness)
   : AllegroFlare::Elements::Base()
   , max(max)
   , value(value)
   , color(color)
   , bar_width(bar_width)
   , bar_spacing(bar_spacing)
   , bar_height(bar_height)
   , bar_thickness(bar_thickness)
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


void Classic::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
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


void Classic::set_bar_thickness(float bar_thickness)
{
   this->bar_thickness = bar_thickness;
}


int Classic::get_max()
{
   return max;
}


int Classic::get_value()
{
   return value;
}


ALLEGRO_COLOR Classic::get_color()
{
   return color;
}


float Classic::get_bar_width()
{
   return bar_width;
}


float Classic::get_bar_spacing()
{
   return bar_spacing;
}


float Classic::get_bar_height()
{
   return bar_height;
}


float Classic::get_bar_thickness()
{
   return bar_thickness;
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
   float h_thickness = bar_thickness * 0.5;
   ALLEGRO_COLOR outline_color = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_COLOR fill_color = ALLEGRO_COLOR{0.86, 0.08, 0.24, 1}; // crimson

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
               bar_thickness
            );
      }
   }
   get_placement_ref().restore_transform();
   return;
}
} // namespace HealthBars
} // namespace Elements
} // namespace AllegroFlare



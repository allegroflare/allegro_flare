

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


Classic::Classic(int max, int value, ALLEGRO_COLOR color)
   : AllegroFlare::Elements::Base()
   , max(max)
   , value(value)
   , color(color)
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
   int bar_width = 4*8;
   int bar_spacing = 8*8;
   int bar_height = 9*8;
   int bar_thickness = 3.0f;

   get_placement_ref().start_transform();
   al_draw_rectangle(0, 0, bar_spacing * max, bar_height, ALLEGRO_COLOR{1, 1, 1, 1}, bar_thickness);
   get_placement_ref().restore_transform();
   return;
}
} // namespace HealthBars
} // namespace Elements
} // namespace AllegroFlare



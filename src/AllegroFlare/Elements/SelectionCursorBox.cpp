

#include <AllegroFlare/Elements/SelectionCursorBox.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{


SelectionCursorBox::SelectionCursorBox()
   : cursor_location({})
   , cursor_location_destination({})
   , cursor_size(80, 80)
   , cursor_size_destination(80, 80)
   , cursor_reposition_multiplier(DEFAULT_CURSOR_REPOSITION_MULTIPLIER)
{
}


SelectionCursorBox::~SelectionCursorBox()
{
}


float SelectionCursorBox::get_cursor_reposition_multiplier() const
{
   return cursor_reposition_multiplier;
}


void SelectionCursorBox::reposition_to(float x, float y)
{
   cursor_location_destination = AllegroFlare::Vec2D(x, y);
   return;
}

void SelectionCursorBox::update()
{
   cursor_location = (cursor_location_destination - cursor_location)
                   * cursor_reposition_multiplier + cursor_location;
   cursor_size = (cursor_size_destination - cursor_size)
               * cursor_reposition_multiplier + cursor_size;
   return;
}

void SelectionCursorBox::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[SelectionCursorBox::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SelectionCursorBox::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[SelectionCursorBox::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SelectionCursorBox::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   draw_cursor();
   return;
}

ALLEGRO_COLOR SelectionCursorBox::build_cursor_color()
{
   ALLEGRO_COLOR color_a = al_color_name("aquamarine");
   ALLEGRO_COLOR color_b = AllegroFlare::color::transparent;
   float speed_multiplier = 0.9;
   float mix_factor = AllegroFlare::interpolator::slow_in(fmod(al_get_time() * speed_multiplier, 1.0));
   return AllegroFlare::color::mix(color_a, color_b, 0.7 * mix_factor);
}

void SelectionCursorBox::draw_cursor_rectangle(float x, float y, float w, float h)
{
   // color
   ALLEGRO_COLOR color = build_cursor_color();
   float roundness = 8;
   float thickness = 6.0;

   al_draw_rounded_rectangle(x, y, x + w, y + h, roundness, roundness, color, thickness);
   return;
}

void SelectionCursorBox::draw_cursor()
{
   draw_cursor_rectangle(cursor_location.x, cursor_location.y, cursor_size.x, cursor_size.y);
   return;
}


} // namespace Elements
} // namespace AllegroFlare



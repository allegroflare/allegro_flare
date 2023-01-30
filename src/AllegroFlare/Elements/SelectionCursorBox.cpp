

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
   : cursor_position({})
   , cursor_position_destination({})
   , cursor_size(80, 80)
   , cursor_size_destination(80, 80)
   , cursor_reposition_multiplier(DEFAULT_CURSOR_REPOSITION_MULTIPLIER)
   , last_repositioned_at(0.0f)
{
}


SelectionCursorBox::~SelectionCursorBox()
{
}


float SelectionCursorBox::get_cursor_reposition_multiplier() const
{
   return cursor_reposition_multiplier;
}


float SelectionCursorBox::get_last_repositioned_at() const
{
   return last_repositioned_at;
}


void SelectionCursorBox::set_position(float x, float y, float time_now)
{
   cursor_position_destination = AllegroFlare::Vec2D(x, y);
   cursor_position = cursor_position_destination;
   last_repositioned_at = time_now;
}

void SelectionCursorBox::set_size(float x, float y, float time_now)
{
   cursor_size_destination = AllegroFlare::Vec2D(x, y);
   cursor_size = cursor_size_destination;
   last_repositioned_at = time_now; // TODO: change this to a "last_resized_at"
}

void SelectionCursorBox::reposition_to(float x, float y, float time_now)
{
   cursor_position_destination = AllegroFlare::Vec2D(x, y);
   last_repositioned_at = time_now;
   return;
}

void SelectionCursorBox::resize_to(float x, float y, float time_now)
{
   cursor_size_destination = AllegroFlare::Vec2D(x, y);
   last_repositioned_at = time_now; // TODO: change this to a "last_resized_at"
   return;
}

void SelectionCursorBox::update()
{
   cursor_position = (cursor_position_destination - cursor_position)
                   * cursor_reposition_multiplier + cursor_position;
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
   float mix_factor = AllegroFlare::interpolator::slow_in(fmod(infer_cursor_change_age() * speed_multiplier, 1.0));
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
   draw_cursor_rectangle(cursor_position.x, cursor_position.y, cursor_size.x, cursor_size.y);
   return;
}

float SelectionCursorBox::infer_cursor_change_age(float time_now)
{
   return (time_now - last_repositioned_at);
}


} // namespace Elements
} // namespace AllegroFlare



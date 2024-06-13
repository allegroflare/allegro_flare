

#include <AllegroFlare/Elements/HealthBars/Basic.hpp>

#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace HealthBars
{


Basic::Basic(float value, float max, ALLEGRO_COLOR fill_color, ALLEGRO_COLOR backfill_color, float bar_width, float bar_height, float min_render_threshold)
   : AllegroFlare::Elements::Base()
   , value(value)
   , max(max)
   , fill_color(fill_color)
   , backfill_color(backfill_color)
   , bar_width(bar_width)
   , bar_height(bar_height)
   , min_render_threshold(min_render_threshold)
{
}


Basic::~Basic()
{
}


void Basic::set_value(float value)
{
   this->value = value;
}


void Basic::set_max(float max)
{
   this->max = max;
}


void Basic::set_fill_color(ALLEGRO_COLOR fill_color)
{
   this->fill_color = fill_color;
}


void Basic::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


void Basic::set_bar_width(float bar_width)
{
   this->bar_width = bar_width;
}


void Basic::set_bar_height(float bar_height)
{
   this->bar_height = bar_height;
}


void Basic::set_min_render_threshold(float min_render_threshold)
{
   this->min_render_threshold = min_render_threshold;
}


float Basic::get_value() const
{
   return value;
}


float Basic::get_max() const
{
   return max;
}


ALLEGRO_COLOR Basic::get_fill_color() const
{
   return fill_color;
}


ALLEGRO_COLOR Basic::get_backfill_color() const
{
   return backfill_color;
}


float Basic::get_bar_width() const
{
   return bar_width;
}


float Basic::get_bar_height() const
{
   return bar_height;
}


float Basic::get_min_render_threshold() const
{
   return min_render_threshold;
}


void Basic::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::HealthBars::Basic::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::HealthBars::Basic::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::HealthBars::Basic::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::HealthBars::Basic::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   get_placement_ref().start_transform();

   al_draw_filled_rectangle(0, 0, bar_width, bar_height, backfill_color);
   if (value > min_render_threshold)
   {
      float normalized_value = max / value;
      float limited_normalized_value = std::min(1.0f, std::max(0.0f, value));
      al_draw_filled_rectangle(0, 0, bar_width*limited_normalized_value, bar_height, fill_color);
   }

   get_placement_ref().restore_transform();
   return;
}


} // namespace HealthBars
} // namespace Elements
} // namespace AllegroFlare



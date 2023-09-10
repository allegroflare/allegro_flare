

#include <AllegroFlare/MusicNotation/Beam.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


Beam::Beam(float staff_line_distance, float start_x, float start_staff_pos, Beam::Alignment start_alignment, float end_x, float end_staff_pos, Beam::Alignment end_alignment, ALLEGRO_COLOR color)
   : staff_line_distance(staff_line_distance)
   , start_x(start_x)
   , start_staff_pos(start_staff_pos)
   , start_alignment(start_alignment)
   , end_x(end_x)
   , end_staff_pos(end_staff_pos)
   , end_alignment(end_alignment)
   , color(color)
{
}


Beam::~Beam()
{
}


void Beam::set_staff_line_distance(float staff_line_distance)
{
   this->staff_line_distance = staff_line_distance;
}


void Beam::set_start_x(float start_x)
{
   this->start_x = start_x;
}


void Beam::set_start_staff_pos(float start_staff_pos)
{
   this->start_staff_pos = start_staff_pos;
}


void Beam::set_start_alignment(Beam::Alignment start_alignment)
{
   this->start_alignment = start_alignment;
}


void Beam::set_end_x(float end_x)
{
   this->end_x = end_x;
}


void Beam::set_end_staff_pos(float end_staff_pos)
{
   this->end_staff_pos = end_staff_pos;
}


void Beam::set_end_alignment(Beam::Alignment end_alignment)
{
   this->end_alignment = end_alignment;
}


void Beam::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


float Beam::get_staff_line_distance() const
{
   return staff_line_distance;
}


float Beam::get_start_x() const
{
   return start_x;
}


float Beam::get_start_staff_pos() const
{
   return start_staff_pos;
}


Beam::Alignment Beam::get_start_alignment() const
{
   return start_alignment;
}


float Beam::get_end_x() const
{
   return end_x;
}


float Beam::get_end_staff_pos() const
{
   return end_staff_pos;
}


Beam::Alignment Beam::get_end_alignment() const
{
   return end_alignment;
}


ALLEGRO_COLOR Beam::get_color() const
{
   return color;
}


void Beam::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(staff_line_distance > 0))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"staff_line_distance > 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"staff_line_distance > 0\" not met");
   }
   if (!(start_alignment != Beam::Alignment::UNDEFINED))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"start_alignment != Beam::Alignment::UNDEFINED\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"start_alignment != Beam::Alignment::UNDEFINED\" not met");
   }
   if (!(end_alignment != Beam::Alignment::UNDEFINED))
   {
      std::stringstream error_message;
      error_message << "[Beam::render]: error: guard \"end_alignment != Beam::Alignment::UNDEFINED\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::render: error: guard \"end_alignment != Beam::Alignment::UNDEFINED\" not met");
   }
   float staff_line_h_distance = staff_line_distance * 0.5;
   float top_x1 = start_x;
   float top_y1 = start_staff_pos * staff_line_h_distance
                + staff_line_h_distance * alignment_vertical_offset_for(start_alignment);
   float top_x2 = end_x;
   float top_y2 = end_staff_pos * staff_line_h_distance
                + staff_line_h_distance * alignment_vertical_offset_for(end_alignment);
   float bottom_x3 = top_x2;
   float bottom_y3 = top_y2 + staff_line_h_distance;
   float bottom_x4 = top_x1;
   float bottom_y4 = top_y1 + staff_line_h_distance;

   ALLEGRO_VERTEX v[6] = {
      ALLEGRO_VERTEX{.x = top_x1, .y = top_y1, .z = 0, .color = color, .u = 0, .v = 0},
      ALLEGRO_VERTEX{.x = top_x2, .y = top_y2, .z = 0, .color = color, .u = 0, .v = 0},
      ALLEGRO_VERTEX{.x = bottom_x3, .y = bottom_y3, .z = 0, .color = color, .u = 0, .v = 0},

      ALLEGRO_VERTEX{.x = bottom_x3, .y = bottom_y3, .z = 0, .color = color, .u = 0, .v = 0},
      ALLEGRO_VERTEX{.x = bottom_x4, .y = bottom_y4, .z = 0, .color = color, .u = 0, .v = 0},
      ALLEGRO_VERTEX{.x = top_x1, .y = top_y1, .z = 0, .color = color, .u = 0, .v = 0},
   };

   al_draw_prim(v, nullptr, nullptr, 0, 6, ALLEGRO_PRIM_TRIANGLE_LIST);

   // Draw a debug guide "through" line
   al_draw_line(
      start_x,
      start_staff_pos * staff_line_h_distance,
      end_x,
      end_staff_pos * staff_line_h_distance,
      ALLEGRO_COLOR{0, 0.5, 1.0, 1.0},
      1.0
   );

   return;
}

float Beam::alignment_vertical_offset_for(Beam::Alignment alignment)
{
   if (!((alignment != Beam::Alignment::UNDEFINED)))
   {
      std::stringstream error_message;
      error_message << "[Beam::alignment_vertical_offset_for]: error: guard \"(alignment != Beam::Alignment::UNDEFINED)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Beam::alignment_vertical_offset_for: error: guard \"(alignment != Beam::Alignment::UNDEFINED)\" not met");
   }
   if (alignment == Beam::Alignment::TOP) return -1.0;
   else if (alignment == Beam::Alignment::BOTTOM) return 0.0;
   else if (alignment == Beam::Alignment::MIDDLE) return -0.5;
   throw std::runtime_error("alignment_vertical_offset_for cannot handle case for beam alignment type");
}


} // namespace MusicNotation
} // namespace AllegroFlare



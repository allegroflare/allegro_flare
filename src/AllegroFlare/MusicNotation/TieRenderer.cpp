

#include <AllegroFlare/MusicNotation/TieRenderer.hpp>

#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace MusicNotation
{


TieRenderer::TieRenderer(AllegroFlare::Vec2D start_point, int length, int height, ALLEGRO_COLOR color, float narrow_line_thickness, float thick_line_thickness)
   : start_point(start_point)
   , length(length)
   , height(height)
   , color(color)
   , narrow_line_thickness(narrow_line_thickness)
   , thick_line_thickness(thick_line_thickness)
{
}


TieRenderer::~TieRenderer()
{
}


void TieRenderer::set_start_point(AllegroFlare::Vec2D start_point)
{
   this->start_point = start_point;
}


void TieRenderer::set_length(int length)
{
   this->length = length;
}


void TieRenderer::set_height(int height)
{
   this->height = height;
}


void TieRenderer::set_color(ALLEGRO_COLOR color)
{
   this->color = color;
}


void TieRenderer::set_narrow_line_thickness(float narrow_line_thickness)
{
   this->narrow_line_thickness = narrow_line_thickness;
}


void TieRenderer::set_thick_line_thickness(float thick_line_thickness)
{
   this->thick_line_thickness = thick_line_thickness;
}


AllegroFlare::Vec2D TieRenderer::get_start_point() const
{
   return start_point;
}


int TieRenderer::get_length() const
{
   return length;
}


int TieRenderer::get_height() const
{
   return height;
}


ALLEGRO_COLOR TieRenderer::get_color() const
{
   return color;
}


float TieRenderer::get_narrow_line_thickness() const
{
   return narrow_line_thickness;
}


float TieRenderer::get_thick_line_thickness() const
{
   return thick_line_thickness;
}


void TieRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::TieRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::TieRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::TieRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::TieRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   float h_thickness = thick_line_thickness * 0.5;
   // TODO: Render multiple arcs for thickness
   render_arc(start_point, length, height, color, narrow_line_thickness);
   render_arc(start_point, length, height+h_thickness, color, narrow_line_thickness);
   render_arc(start_point, length, height-h_thickness, color, narrow_line_thickness);

   return;
}

void TieRenderer::render_arc(AllegroFlare::Vec2D start_point, float length, float height, ALLEGRO_COLOR color, float line_thickness)
{
   float points[8];

   // TODO: Make these points controlable, but do not allow them to be (< 0), (> 1), or overlapping
   float point2_position_normalized = 0.30;
   float point3_position_normalized = 0.70;

   // Calculate the spline points
   points[0] = start_point.x;
   points[1] = start_point.y;
   points[2] = start_point.x + length * point2_position_normalized;
   points[3] = start_point.y + height;
   points[4] = start_point.x + length * point3_position_normalized;
   points[5] = start_point.y + height;
   points[6] = start_point.x + length;
   points[7] = start_point.y;

   // Draw the primary spline
   al_draw_spline(points, color, line_thickness);
   return;
}


} // namespace MusicNotation
} // namespace AllegroFlare



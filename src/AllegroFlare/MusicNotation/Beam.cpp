

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


Beam::Beam(float staff_line_distance, float start_x, int start_staff_pos, Beam::Alignment start_alignment, float end_x, int end_staff_pos, Beam::Alignment end_alignment, ALLEGRO_COLOR color, std::vector<std::tuple<int, float, float>> secondary_beams)
   : staff_line_distance(staff_line_distance)
   , start_x(start_x)
   , start_staff_pos(start_staff_pos)
   , start_alignment(start_alignment)
   , end_x(end_x)
   , end_staff_pos(end_staff_pos)
   , end_alignment(end_alignment)
   , color(color)
   , secondary_beams(secondary_beams)
   , render_with_debugging_visuals(false)
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


void Beam::set_start_staff_pos(int start_staff_pos)
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


void Beam::set_end_staff_pos(int end_staff_pos)
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


void Beam::set_secondary_beams(std::vector<std::tuple<int, float, float>> secondary_beams)
{
   this->secondary_beams = secondary_beams;
}


void Beam::set_render_with_debugging_visuals(bool render_with_debugging_visuals)
{
   this->render_with_debugging_visuals = render_with_debugging_visuals;
}


float Beam::get_staff_line_distance() const
{
   return staff_line_distance;
}


float Beam::get_start_x() const
{
   return start_x;
}


int Beam::get_start_staff_pos() const
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


int Beam::get_end_staff_pos() const
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


std::vector<std::tuple<int, float, float>> Beam::get_secondary_beams() const
{
   return secondary_beams;
}


bool Beam::get_render_with_debugging_visuals() const
{
   return render_with_debugging_visuals;
}


float Beam::calculate_beam_thickness()
{
   return staff_line_distance * 0.48;
}

void Beam::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::Beam::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::Beam::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::Beam::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::Beam::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(staff_line_distance > 0))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::Beam::render]: error: guard \"staff_line_distance > 0\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::Beam::render]: error: guard \"staff_line_distance > 0\" not met");
   }
   if (!(start_alignment != Beam::Alignment::UNDEFINED))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::Beam::render]: error: guard \"start_alignment != Beam::Alignment::UNDEFINED\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::Beam::render]: error: guard \"start_alignment != Beam::Alignment::UNDEFINED\" not met");
   }
   if (!(end_alignment != Beam::Alignment::UNDEFINED))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::Beam::render]: error: guard \"end_alignment != Beam::Alignment::UNDEFINED\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::Beam::render]: error: guard \"end_alignment != Beam::Alignment::UNDEFINED\" not met");
   }
   float staff_line_h_distance = staff_line_distance * 0.5;
   float centering_y_offset = staff_line_h_distance * 0.5;
   float beam_h_thickness = calculate_beam_thickness() * 0.5;

   float top_x1 = start_x;
   float top_y1 = start_staff_pos * staff_line_h_distance
                + staff_line_h_distance * alignment_vertical_offset_for(start_alignment)
                + centering_y_offset
                - beam_h_thickness;
   float top_x2 = end_x;
   float top_y2 = end_staff_pos * staff_line_h_distance
                + staff_line_h_distance * alignment_vertical_offset_for(end_alignment)
                + centering_y_offset
                - beam_h_thickness;

   ALLEGRO_COLOR primary_beam_color = render_with_debugging_visuals ? ALLEGRO_COLOR{0.0, 0.5, 0.5, 0.5} : color;
   ALLEGRO_COLOR secondary_beam_color = render_with_debugging_visuals ? ALLEGRO_COLOR{0.5, 0.25, 0.0, 0.5} : color;

   render_beam(top_x1, top_y1, top_x2, top_y2, primary_beam_color);
   // TODO: Replace these two demonstrations of secondary beams with "secondary_beams" property
   for (auto &secondary_beam : secondary_beams)
   {
      int vertical_position = std::get<0>(secondary_beam);
      float x1_normalized = std::get<1>(secondary_beam);
      float x2_normalized = std::get<2>(secondary_beam);
      render_secondary_beam(
         top_x1,
         top_y1,
         top_x2,
         top_y2,
         x1_normalized,
         x2_normalized,
         vertical_position,
         secondary_beam_color
      );
   }
   //render_secondary_beam(top_x1, top_y1, top_x2, top_y2, 0.0, 0.5, 1, secondary_beam_color);
   //render_secondary_beam(top_x1, top_y1, top_x2, top_y2, 0.8, 1.0, 1);
   //render_secondary_beam(top_x1, top_y1, top_x2, top_y2, 0.8, 1.0, 1, secondary_beam_color);
   return;
}

void Beam::render_beam(float top_x1, float top_y1, float top_x2, float top_y2, ALLEGRO_COLOR _color)
{
   float staff_line_h_distance = calculate_beam_thickness(); //staff_line_distance * 0.5;
   //float top_x1 = start_x;
   //float top_y1 = start_staff_pos * staff_line_h_distance
                //+ staff_line_h_distance * alignment_vertical_offset_for(start_alignment);
   //float top_x2 = end_x;
   //float top_y2 = end_staff_pos * staff_line_h_distance
                //+ staff_line_h_distance * alignment_vertical_offset_for(end_alignment);
   float bottom_x3 = top_x2;
   float bottom_y3 = top_y2 + staff_line_h_distance;
   float bottom_x4 = top_x1;
   float bottom_y4 = top_y1 + staff_line_h_distance;

   ALLEGRO_VERTEX v[6] = {
      ALLEGRO_VERTEX{.x = top_x1, .y = top_y1, .z = 0, .u = 0, .v = 0, .color = color},
      ALLEGRO_VERTEX{.x = top_x2, .y = top_y2, .z = 0, .u = 0, .v = 0, .color = color},
      ALLEGRO_VERTEX{.x = bottom_x3, .y = bottom_y3, .z = 0, .u = 0, .v = 0, .color = color},

      ALLEGRO_VERTEX{.x = bottom_x3, .y = bottom_y3, .z = 0, .u = 0, .v = 0, .color = color},
      ALLEGRO_VERTEX{.x = bottom_x4, .y = bottom_y4, .z = 0, .u = 0, .v = 0, .color = color},
      ALLEGRO_VERTEX{.x = top_x1, .y = top_y1, .z = 0, .u = 0, .v = 0, .color = color},
   };

   al_draw_prim(v, nullptr, nullptr, 0, 6, ALLEGRO_PRIM_TRIANGLE_LIST);

   // Draw a debug guide "through" line
   if (render_with_debugging_visuals)
   {
      al_draw_line(
         start_x,
         start_staff_pos * staff_line_h_distance,
         end_x,
         end_staff_pos * staff_line_h_distance,
         ALLEGRO_COLOR{0, 0.5, 1.0, 1.0},
         1.0
      );
   }

   return;
}

void Beam::render_secondary_beam(float primary_beam_top_x1, float primary_beam_top_y1, float primary_beam_top_x2, float primary_beam_top_y2, float x1_normalized, float x2_normalized, int vertical_position, ALLEGRO_COLOR _color)
{
   float y_position_offset_distance = staff_line_distance * 3.0f / 4.0f;
   float slope = (primary_beam_top_y2 - primary_beam_top_y1) / (primary_beam_top_x2 - primary_beam_top_x1);
   bool divide_by_zero_could_occour = (std::abs(primary_beam_top_x2 - primary_beam_top_x1) < 1e-6);
   if (divide_by_zero_could_occour)
   {
      throw std::runtime_error("MusicNotation::Beam: error: the slope is vertical, divide by 0 is possible");
   }

   float length = primary_beam_top_x2 - primary_beam_top_x1;
   float x1 = x1_normalized * length + primary_beam_top_x1;
   float y1 = (x1_normalized * length) * slope + primary_beam_top_y1
            + y_position_offset_distance * vertical_position;
   float x2 = x2_normalized * length + primary_beam_top_x1;
   float y2 = (x2_normalized * length) * slope + primary_beam_top_y1
            + y_position_offset_distance * vertical_position;

   render_beam(x1, y1, x2, y2, _color);

   return;
}

float Beam::alignment_vertical_offset_for(Beam::Alignment alignment)
{
   if (!(alignment != Beam::Alignment::UNDEFINED))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MusicNotation::Beam::alignment_vertical_offset_for]: error: guard \"alignment != Beam::Alignment::UNDEFINED\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MusicNotation::Beam::alignment_vertical_offset_for]: error: guard \"alignment != Beam::Alignment::UNDEFINED\" not met");
   }
   if (alignment == Beam::Alignment::TOP) return -1.0;
   else if (alignment == Beam::Alignment::BOTTOM) return 0.0;
   else if (alignment == Beam::Alignment::MIDDLE) return -0.5;
   throw std::runtime_error("alignment_vertical_offset_for cannot handle case for beam alignment type");
}


} // namespace MusicNotation
} // namespace AllegroFlare



#pragma once


#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include <AllegroFlare/DrawingInterfaces/Base.hpp>
#include <AllegroFlare/FontBin.hpp>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class MusicNotation
      // TODO: guard all functions properly when drawing_interface is nullptr
      {
      public:
         enum spacing_method_t
         {
            SPACING_UNDEF = 0,
            SPACING_FIXED,
            SPACING_AESTHETIC
         };

      private:
         AllegroFlare::DrawingInterfaces::Base *drawing_interface;
         AllegroFlare::FontBin *font_bin;
         float staff_line_distance;
         float quarter_note_spacing;
         spacing_method_t spacing_method;
         bool int_cast_y;

         float calculate_staff_position_y_offset(int staff_position);
         void prepare_drawing_surface();
         void finish_drawing_surface(std::string output_file_basename="");
         float draw_raw(float x, float y, std::string content);

      public:
         MusicNotation(
            AllegroFlare::DrawingInterfaces::Base *drawing_interface=nullptr,
            AllegroFlare::FontBin *font_bin=nullptr,
            float staff_line_distance=10
         );
         ~MusicNotation();

         float get_quarter_note_spacing();
         void set_quarter_note_spacing(int);
         void set_spacing_method(spacing_method_t method);
         static float get_duration_fixed_width(int duration, float quarter_note_width, int num_dots);
         char duration_denominator_to_char(int denominator);
         float draw(float x, float y, std::string content, std::string output_file_basename="");
         void set_staff_line_distance(float distance);
         void draw_ledger_lines_to(
            float x,
            float y,
            int staff_pos,
            float staff_line_thickness,
            float head_width,
            const ALLEGRO_COLOR &color
         );
         void draw_staff_lines(
            float x,
            float y,
            float width,
            float line_distance,
            const ALLEGRO_COLOR &color,
            float thickness
         );
         void draw_music_symbol(int32_t symbol, float x, float y, const ALLEGRO_COLOR &color, float font_size_px);
         int get_music_symbol_width(int32_t symbol);
         void draw_line(float x1, float y1, float x2, float y2, const ALLEGRO_COLOR &color, float thickness);
         void use_drawing_interface(AllegroFlare::DrawingInterfaces::Base *drawing_interface);
         ALLEGRO_FONT *obtain_font_bravura();
      };
   }
}



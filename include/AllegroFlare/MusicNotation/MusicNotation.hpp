#pragma once


#include <string>
#include <vector>
#include <allegro5/allegro.h> // for ALLEGRO_COLOR
#include <AllegroFlare/DrawingInterfaces/Base.hpp>
#include <AllegroFlare/FontBin.hpp>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class MusicNotation
      // TODO: escape all functions properly when there is drawing_interface==NULL;
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
         float staff_line_distance;
         float staff_line_thickness;
         float font_size_px;
         float quarter_note_spacing;
         float stem_thickness;
         spacing_method_t spacing_method;
         AllegroFlare::FontBin *font_bin;
         int current_note_duration;
         bool current_note_is_rest;
         int current_accidental;
         bool int_cast_y;
         bool ignore_spaces;

         float _get_staff_position_offset(int staff_position);
         void prepare_drawing_surface();
         void finish_drawing_surface(std::string output_file_basename="");
         int draw_raw(float x, float y, std::string content);
         void recalculate_rendering_metrics();

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
         int draw(float x, float y, std::string content, std::string output_file_basename="");
         void set_staff_line_distance(float distance);
         void draw_ledger_lines_to(float x, float y, int staff_pos, float head_width, const ALLEGRO_COLOR &color);
         void draw_staff_lines(
            float x,
            float y,
            float width,
            float line_distance,
            const ALLEGRO_COLOR &color,
            float thickness
         );
         void draw_music_symbol(int32_t symbol, float x, float y, const ALLEGRO_COLOR &color);
         int get_music_symbol_width(int32_t symbol);
         void draw_line(float x1, float y1, float x2, float y2, const ALLEGRO_COLOR &color, float thickness);
         void use_drawing_interface(AllegroFlare::DrawingInterfaces::Base *drawing_interface);
         ALLEGRO_FONT *obtain_font_bravura();
      };
   }
}



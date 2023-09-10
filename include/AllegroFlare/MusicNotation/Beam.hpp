#pragma once


#include <allegro5/allegro.h>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class Beam
      {
      public:

         enum Alignment
         {
            UNDEFINED = 0,
            TOP,
            MIDDLE,
            BOTTOM,
         };
      private:
         float staff_line_distance;
         float start_x;
         float start_staff_pos;
         Beam::Alignment start_alignment;
         float end_x;
         float end_staff_pos;
         Beam::Alignment end_alignment;
         ALLEGRO_COLOR color;
         std::vector<std::tuple<int, float, float>> secondary_beams;
         bool render_with_debugging_visuals;

      protected:


      public:
         Beam(float staff_line_distance=0, float start_x=0, float start_staff_pos=0, Beam::Alignment start_alignment=Beam::Alignment::UNDEFINED, float end_x=0.0f, float end_staff_pos=0.0f, Beam::Alignment end_alignment=Beam::Alignment::UNDEFINED, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, std::vector<std::tuple<int, float, float>> secondary_beams={});
         ~Beam();

         void set_staff_line_distance(float staff_line_distance);
         void set_start_x(float start_x);
         void set_start_staff_pos(float start_staff_pos);
         void set_start_alignment(Beam::Alignment start_alignment);
         void set_end_x(float end_x);
         void set_end_staff_pos(float end_staff_pos);
         void set_end_alignment(Beam::Alignment end_alignment);
         void set_color(ALLEGRO_COLOR color);
         void set_secondary_beams(std::vector<std::tuple<int, float, float>> secondary_beams);
         void set_render_with_debugging_visuals(bool render_with_debugging_visuals);
         float get_staff_line_distance() const;
         float get_start_x() const;
         float get_start_staff_pos() const;
         Beam::Alignment get_start_alignment() const;
         float get_end_x() const;
         float get_end_staff_pos() const;
         Beam::Alignment get_end_alignment() const;
         ALLEGRO_COLOR get_color() const;
         std::vector<std::tuple<int, float, float>> get_secondary_beams() const;
         bool get_render_with_debugging_visuals() const;
         float calculate_beam_thickness();
         void render();
         void render_beam(float top_x1=0.0f, float top_y1=0.0f, float top_x2=0.0f, float top_y2=0.0f, ALLEGRO_COLOR _color=ALLEGRO_COLOR{1, 1, 1, 1});
         void render_secondary_beam(float primary_beam_top_x1=0.0f, float primary_beam_top_y1=0.0f, float primary_beam_top_x2=0.0f, float primary_beam_top_y2=0.0f, float x1_normalized=0.0f, float x2_normalized=1.0f, int vertical_position=0, ALLEGRO_COLOR _color=ALLEGRO_COLOR{1, 1, 1, 1});
         float alignment_vertical_offset_for(Beam::Alignment alignment=Beam::Alignment::UNDEFINED);
      };
   }
}




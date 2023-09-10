#pragma once


#include <allegro5/allegro.h>


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

      protected:


      public:
         Beam(float staff_line_distance=0, float start_x=0, float start_staff_pos=0, Beam::Alignment start_alignment=Beam::Alignment::UNDEFINED, float end_x=0.0f, float end_staff_pos=0.0f, Beam::Alignment end_alignment=Beam::Alignment::UNDEFINED, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
         ~Beam();

         void set_staff_line_distance(float staff_line_distance);
         void set_start_x(float start_x);
         void set_start_staff_pos(float start_staff_pos);
         void set_start_alignment(Beam::Alignment start_alignment);
         void set_end_x(float end_x);
         void set_end_staff_pos(float end_staff_pos);
         void set_end_alignment(Beam::Alignment end_alignment);
         void set_color(ALLEGRO_COLOR color);
         float get_staff_line_distance() const;
         float get_start_x() const;
         float get_start_staff_pos() const;
         Beam::Alignment get_start_alignment() const;
         float get_end_x() const;
         float get_end_staff_pos() const;
         Beam::Alignment get_end_alignment() const;
         ALLEGRO_COLOR get_color() const;
         void render();
         float alignment_vertical_offset_for(Beam::Alignment alignment=Beam::Alignment::UNDEFINED);
      };
   }
}




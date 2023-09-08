#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace MusicNotation
   {
      class TieRenderer
      {
      private:
         AllegroFlare::Vec2D start_point;
         int length;
         int height;
         ALLEGRO_COLOR color;
         float narrow_line_thickness;
         float thick_line_thickness;

      protected:


      public:
         TieRenderer();
         ~TieRenderer();

         void set_start_point(AllegroFlare::Vec2D start_point);
         void set_length(int length);
         void set_height(int height);
         void set_color(ALLEGRO_COLOR color);
         void set_narrow_line_thickness(float narrow_line_thickness);
         void set_thick_line_thickness(float thick_line_thickness);
         AllegroFlare::Vec2D get_start_point() const;
         int get_length() const;
         int get_height() const;
         ALLEGRO_COLOR get_color() const;
         float get_narrow_line_thickness() const;
         float get_thick_line_thickness() const;
         void render();
      };
   }
}




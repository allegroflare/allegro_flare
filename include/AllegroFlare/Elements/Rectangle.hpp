#pragma once


#include <AllegroFlare/Elements/Rectangle.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      class Rectangle
      {
      private:

      protected:


      public:
         float x1;
         float y1;
         float x2;
         float y2;
         Rectangle();
         ~Rectangle();

         float w();
         float h();
         void scale(float scale_x=1.0f, float scale_y=1.0f);
         void draw(ALLEGRO_COLOR color=ALLEGRO_COLOR{0.9961, 0.3451, 0.3412, 1.0}, float line_thickness=1.0f);
         static AllegroFlare::Elements::Rectangle build_xywh(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f);
         static AllegroFlare::Elements::Rectangle build_x1y1x2y2(float x1=0.0f, float y1=0.0f, float x2=0.0f, float y2=0.0f);
         bool collides(AllegroFlare::Vec2D point={});
      };
   }
}




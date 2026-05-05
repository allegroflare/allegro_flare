#pragma once


#include <AllegroFlare/Elements/Rectangle.hpp>
#include <AllegroFlare/Vec2D.hpp>


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
         AllegroFlare::Elements::Rectangle build_xywh(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f);
         bool collides(AllegroFlare::Vec2D point={});
      };
   }
}




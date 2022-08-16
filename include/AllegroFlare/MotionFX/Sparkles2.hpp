#pragma once


#include <AllegroFlare/FontBin.hpp>


namespace AllegroFlare
{
   namespace MotionFX
   {
      class Sparkles2
      {
      private:
         AllegroFlare::FontBin* font_bin;
         float x;
         float y;

      public:
         Sparkles2(AllegroFlare::FontBin* font_bin=nullptr, float x=0.0f, float y=0.0f);
         ~Sparkles2();

         void set_x(float x);
         void set_y(float y);
         float get_x();
         float get_y();
         void update();
         void render();
      };
   }
}




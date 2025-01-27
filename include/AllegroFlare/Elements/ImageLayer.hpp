#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      class ImageLayer
      {
      public:
         static constexpr ALLEGRO_COLOR DEFAULT_TINT_COLOR = ALLEGRO_COLOR{1, 1, 1, 1};

      private:

      protected:


      public:
         int tmj_id;
         std::string name;
         std::string image_filename;
         ALLEGRO_BITMAP* bitmap;
         bool bitmap_is_owned;
         int pixel_scale;
         float offset_x;
         float offset_y;
         float parallax_x;
         float parallax_y;
         bool repeat_x;
         bool repeat_y;
         float opacity;
         bool tint_color_is_set;
         ALLEGRO_COLOR tint_color;
         bool destroyed;
         ImageLayer(int tmj_id=0, std::string name="[unset-name]", std::string image_filename="[unset-image_filename]", ALLEGRO_BITMAP* bitmap=nullptr, bool bitmap_is_owned=false, int pixel_scale=1, float offset_x=0.0f, float offset_y=0.0f, float parallax_x=0.0f, float parallax_y=0.0f, bool repeat_x=false, bool repeat_y=false, float opacity=0.0f, bool tint_color_is_set=false, ALLEGRO_COLOR tint_color=DEFAULT_TINT_COLOR, bool destroyed=false);
         ~ImageLayer();

         void destroy_bitmap_if_owned();
      };
   }
}




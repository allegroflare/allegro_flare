#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class ParallaxLayer
         {
         public:
            static constexpr ALLEGRO_COLOR DEFAULT_TINT_COLOR = ALLEGRO_COLOR{1, 1, 1, 1};

         private:
            float anchor_x;
            float anchor_y;
            float offset_rate;
            ALLEGRO_BITMAP* bitmap;

         protected:


         public:
            int tmj_id;
            std::string name;
            std::string image_filename;
            float offset_x;
            float offset_y;
            float parallax_x;
            float parallax_y;
            bool repeat_x;
            bool repeat_y;
            float opacity;
            bool tint_color_is_set;
            ALLEGRO_COLOR tint_color;
            ParallaxLayer(float anchor_x=0.0f, float anchor_y=0.0f, float offset_rate=1.0, ALLEGRO_BITMAP* bitmap=nullptr, int tmj_id=0, std::string name="[unset-name]", std::string image_filename="[unset-image_filename]", float offset_x=0.0f, float offset_y=0.0f, float parallax_x=0.0f, float parallax_y=0.0f, bool repeat_x=false, bool repeat_y=false, float opacity=0.0f, bool tint_color_is_set=false, ALLEGRO_COLOR tint_color=DEFAULT_TINT_COLOR);
            ~ParallaxLayer();

            void set_anchor_x(float anchor_x);
            void set_anchor_y(float anchor_y);
            void set_offset_rate(float offset_rate);
            void set_bitmap(ALLEGRO_BITMAP* bitmap);
            float get_anchor_x() const;
            float get_anchor_y() const;
            float get_offset_rate() const;
            ALLEGRO_BITMAP* get_bitmap() const;
         };
      }
   }
}




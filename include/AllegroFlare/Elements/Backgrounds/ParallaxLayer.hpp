#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class ParallaxLayer
         {
         private:
            float anchor_x;
            float anchor_y;
            float offset_rate;
            ALLEGRO_BITMAP* bitmap;

         protected:


         public:
            ParallaxLayer(float anchor_x=0.0f, float anchor_y=0.0f, float offset_rate=1.0, ALLEGRO_BITMAP* bitmap=nullptr);
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




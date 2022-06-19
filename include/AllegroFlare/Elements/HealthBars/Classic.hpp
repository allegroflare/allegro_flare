#pragma once


#include <AllegroFlare/Elements/Base.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace HealthBars
      {
         class Classic : public AllegroFlare::Elements::Base
         {
         private:
            int max;
            int value;
            ALLEGRO_COLOR color;

         public:
            Classic(int max=10, int value=10, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
            ~Classic();

            void set_max(int max);
            void set_value(int value);
            void set_color(ALLEGRO_COLOR color);
            int get_max();
            int get_value();
            ALLEGRO_COLOR get_color();
            void render();
         };
      }
   }
}




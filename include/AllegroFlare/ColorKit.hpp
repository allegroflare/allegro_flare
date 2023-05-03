#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class ColorKit
   {
   private:

   protected:


   public:
      ColorKit();
      ~ColorKit();

      static ALLEGRO_COLOR invert(ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1});
      static ALLEGRO_COLOR fade(ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float amount=1.0f);
      static ALLEGRO_COLOR mix(ALLEGRO_COLOR c1=ALLEGRO_COLOR{1, 1, 1, 1}, ALLEGRO_COLOR c2=ALLEGRO_COLOR{1, 1, 1, 1}, float scale=1.0f);
   };
}




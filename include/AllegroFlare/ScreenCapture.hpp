#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class ScreenCapture
   {
   private:

   protected:


   public:
      ScreenCapture();
      ~ScreenCapture();

      static ALLEGRO_BITMAP* create_capture();
      static ALLEGRO_BITMAP* clone_as_scaled_bitmap();
   };
}




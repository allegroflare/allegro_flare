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

      ALLEGRO_BITMAP* create_capture();
   };
}




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
      static ALLEGRO_BITMAP* create_capture_as_scaled_bitmap(int destination_width=1920, int destination_height=1080);
   };
}




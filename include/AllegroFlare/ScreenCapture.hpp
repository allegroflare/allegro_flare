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

      static ALLEGRO_BITMAP* create_backbuffer_capture();
      static ALLEGRO_BITMAP* create_frontbuffer_capture();
      static ALLEGRO_BITMAP* create_capture(bool flip_display_for_capture=false);
      static ALLEGRO_BITMAP* create_frontbuffer_capture_as_scaled_bitmap(int destination_width=1920, int destination_height=1080);
      static ALLEGRO_BITMAP* create_backbuffer_capture_as_scaled_bitmap(int destination_width=1920, int destination_height=1080);
      static ALLEGRO_BITMAP* create_capture_as_scaled_bitmap(int destination_width=1920, int destination_height=1080, bool flip_display_for_capture=false);
   };
}




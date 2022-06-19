#pragma once


#include <vector>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class Framework;
   namespace Frameworks
   {
      class Full;
   }


   class Display
   {
   public:
      enum resolution_t
      {
         RESOLUTION_XGA,
         RESOLUTION_WXGA,
         RESOLUTION_WXGA_PLUS, // WXGA+
         RESOLUTION_HD_1080,
         RESOLUTION_HD_720,
         RESOLUTION_RETINA,
         FULLSCREEN_AUTO
      };

   private:
      friend class Framework;
      friend class Frameworks::Full;
      friend class ScreenManager; // <- eh for now, because of the display <-> screen relationship
      static std::vector<Display *> displays; // used to be "instance"
      static Display *find_display(ALLEGRO_DISPLAY *display);
      ALLEGRO_COLOR _background_color;
      int _width, _height;

   public:
      Display(int width=1920, int height=1080, int display_flags=0);
      virtual ~Display();

      ALLEGRO_DISPLAY *al_display;
      virtual void display_close_func();

      void set_as_target_bitmap();
      void set_orthographic_projection(float left, float top, float right, float bottom);

      int get_width();
      int get_height();
      float get_middle();
      float get_center();

      void flip();
      void background_color(const ALLEGRO_COLOR &color);
   };
}



#pragma once


#include <vector>
#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class Framework;


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
      friend class Screens; // <- eh for now, because of the display <-> screen relationship
      static std::vector<Display *> displays; // used to be "instance"
      static Display *find_display(ALLEGRO_DISPLAY *display);
      ALLEGRO_COLOR _background_color;
      int _width, _height;

   public:
      Display(int width, int height, int display_flags); // you must use AllegroFlare::create_display
      virtual ~Display();

      ALLEGRO_DISPLAY *al_display;
      virtual void display_close_func();

      void set_as_target_bitmap();

      int width();
      int height();
      float middle();
      float center();

      void flip();
      void background_color(const ALLEGRO_COLOR &color);
   };
}



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
      //TODO: int DEFAULT_DISPLAY_FLAGS

   private:
      friend class Framework;
      friend class Frameworks::Full;
      friend class ScreenManager; // <- eh for now, because of the display <-> screen relationship
      static std::vector<Display *> displays; // used to be "instance"
      static Display *find_display(ALLEGRO_DISPLAY *display);
      //ALLEGRO_COLOR _background_color;
      int width, height;
      int display_flags__depreciated;
      int samples_requested_at_creation;
      int samples;
      int depth_size;
      int adapter;
      bool fullscreen;
      bool resizable;
      bool initialized;
      bool destroyed;

      bool result_fullscreen;
      bool result_resizable;

   public:
      Display(
         int width=1920,
         int height=1080,
         int display_flags__depreciated=0,
         int samples=4,
         int depth_size=32,
         int adapter=-1,
         bool fullscreen=false,
         bool resizable=true
      );
      virtual ~Display();

      ALLEGRO_DISPLAY *al_display;
      virtual void display_close_func();

      void initialize();
      void destroy();

      void set_as_target_bitmap();
      void set_orthographic_projection(float left, float top, float right, float bottom);

      int get_width();
      int get_height();
      float get_middle();
      float get_center();

      int get_samples_requested_at_creation();
      int get_samples();

      void set_fullscreen(bool fullscreen);
      bool get_result_fullscreen();

      void flip();
   };
}



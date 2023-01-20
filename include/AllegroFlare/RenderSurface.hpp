#pragma once

#define ALLEGRO_UNSTABLE


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   class RenderSurface
   {
   private:
      ALLEGRO_BITMAP* surface;
      ALLEGRO_COLOR clear_color;
      ALLEGRO_STATE previous_state;
      bool surface_is_setup;

   public:
      RenderSurface();
      ~RenderSurface();

      void setup_surface(int w, int h, int multisamples=0, int depth=0);
      void set_as_target(bool clear_to_color=true, bool clear_depth=true);
      void restore_previous_target();

      void set_clear_color(ALLEGRO_COLOR clear_color);
      ALLEGRO_COLOR get_clear_color();

      ALLEGRO_BITMAP *get_surface_bitmap();
   };
}




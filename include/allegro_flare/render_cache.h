#ifndef __AF_RENDER_CACHE_HEADER
#define __AF_RENDER_CACHE_HEADER




#define ALLEGRO_UNSTABLE

#include <allegro5/allegro.h>




namespace allegro_flare
{
   class RenderCache
   {
   private:
      ALLEGRO_BITMAP *render;
      int padding;
      ALLEGRO_STATE previous_state;
      int previous_samples; // should not be necessairy in future versions of Allegro
      int previous_depth;
      bool dirty;

   public:
      RenderCache();
      void setup_surface(int w, int h, int multisamples=0, int depth=0);
      void finish_surface();
      void draw(float origin_x, float origin_y);
      void mark_as_dirty();
      void mark_as_clean();
      bool is_dirty();

      ALLEGRO_BITMAP *get_surface_bitmap();
   };
}




#endif

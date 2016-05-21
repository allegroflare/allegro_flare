#ifndef __AF_RENDER_CACHE_HEADER
#define __AF_RENDER_CACHE_HEADER



#define ALLEGRO_UNSTABLE

#include <allegro5/allegro.h>


class RenderCache
{
private:
  ALLEGRO_BITMAP *render;
  int padding;
  ALLEGRO_STATE previous_state;
  int previous_samples; // should not be necessairy in future versions of Allegro
  int previous_depth;

public:
  RenderCache();
  void setup_surface(int w, int h, int multisamples=0, int depth=0);
  void finish_surface();
  void draw(float origin_x, float origin_y);
};



#endif

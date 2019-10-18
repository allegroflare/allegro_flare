



#include <allegro_flare/frustum.h>




namespace allegro_flare
{
   Frustum::Frustum(int width, int height, int znear, float multiplier)
      : znear(znear * multiplier)
      , zfar(30000)
      , top(height/2 * multiplier)
      , left(-width/2 * multiplier)
      , right(width/2 * multiplier)
      , bottom(-height/2 * multiplier)
   {}
}




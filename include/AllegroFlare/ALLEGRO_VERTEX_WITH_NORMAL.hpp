#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   typedef struct
   {
      float x, y, z;
      float u, v;
      ALLEGRO_COLOR color;
      float nx, ny, nz;
   } ALLEGRO_VERTEX_WITH_NORMAL;
} // namespace AllegroFlare



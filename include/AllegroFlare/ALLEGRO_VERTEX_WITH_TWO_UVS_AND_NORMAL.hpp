#pragma once


#include <allegro5/allegro.h>


namespace AllegroFlare
{
   typedef struct
   {
      float x, y, z;
      float u1, v1;
      float u2, v2;
      ALLEGRO_COLOR color;
      float nx, ny, nz;
   } ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL;
}



#pragma once


#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>


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

   ALLEGRO_VERTEX_DECL *create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration();
} // namespace AllegroFlare;



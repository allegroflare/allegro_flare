#pragma once


#include <allegro5/allegro.h>


typedef struct
{
   float x, y, z;
   float texture_u, texture_v;
   float normal_u, normal_v;
   float height_u, height_v; // this one might not be used in the end
   float height;
   ALLEGRO_COLOR color;
} TILEO_TILE_VERTEX;



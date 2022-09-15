#pragma once

#include <AllegroFlare/Cubemap.hpp>
//#include <allegro_flare/allegro_flare.h> // a bit much, but not sure where ALLEGRO_FLARE_CUBEMAP_TEXTURE is


#include <allegro_flare/shader.h>
#include <allegro_flare/cubemap.h>
using allegro_flare::ALLEGRO_FLARE_CUBEMAP_TEXTURE;


class CubeMapRepository
{
private:
   ALLEGRO_FLARE_CUBEMAP_TEXTURE *cube_map_A;
   ALLEGRO_FLARE_CUBEMAP_TEXTURE *cube_map_B;
   //AllegroFlare::Cubemap *cube_map_A;
   //AllegroFlare::Cubemap *cube_map_B;
   bool initialized;

public:
   CubeMapRepository();

   void initialize();
   //AllegroFlare::Cubemap *get_cube_map_A();
   //AllegroFlare::Cubemap *get_cube_map_B();
   ALLEGRO_FLARE_CUBEMAP_TEXTURE *get_cube_map_A();
   ALLEGRO_FLARE_CUBEMAP_TEXTURE *get_cube_map_B();
};




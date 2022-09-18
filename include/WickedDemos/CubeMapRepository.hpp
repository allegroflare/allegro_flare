#pragma once



#include <AllegroFlare/Cubemap.hpp>


class CubeMapRepository
{
private:
   AllegroFlare::Cubemap *cube_map_A;
   AllegroFlare::Cubemap *cube_map_B;
   bool initialized;

public:
   CubeMapRepository();

   void initialize();
   AllegroFlare::Cubemap *get_cube_map_A();
   AllegroFlare::Cubemap *get_cube_map_B();
};




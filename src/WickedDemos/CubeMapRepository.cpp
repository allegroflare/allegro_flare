
#include <WickedDemos/CubeMapRepository.hpp>
#include <AllegroFlare/CubemapBuilder.hpp>



#include <iostream>


CubeMapRepository::CubeMapRepository()
   : cube_map_A(nullptr)
   , cube_map_B(nullptr)
   , initialized(false)
{}


void CubeMapRepository::initialize()
{
   AllegroFlare::CubemapBuilder builder;

   if (initialized) return;

   // TODO: update this bitmap_bin so that it is injected and the path can be dynamically coded
   std::string BASE_PATH = "/Users/markoates/Repos/allegro_flare/bin/programs/";

   cube_map_A = builder.glsl_create_cubemap_from_vertical_strip(
      (BASE_PATH + std::string("data/bitmaps/sky4.png")).c_str());
   cube_map_B = builder.glsl_create_cubemap_from_vertical_strip(
      (BASE_PATH + std::string("data/bitmaps/sky5_with_grid.png")).c_str());

   initialized = true;
};


AllegroFlare::Cubemap *CubeMapRepository::get_cube_map_A()
{
   if (!initialized) throw std::runtime_error("!!! CubeMapRepository called without being initialized.");
   return cube_map_A;
}


AllegroFlare::Cubemap *CubeMapRepository::get_cube_map_B()
{
   if (!initialized) throw std::runtime_error("!!! CubeMapRepository called without being initialized.");
   return cube_map_B;
}




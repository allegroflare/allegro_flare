#include <WickedDemos/CubeMapRepository.hpp>
#include <AllegroFlare/CubemapBuilder.hpp>



//using allegro_flare::glsl_create_cubemap_from_vertical_strip;

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

   //AllegroFlare::Cubemap *af_cube_map_A = nullptr;
   //AllegroFlare::Cubemap *af_cube_map_B = nullptr;
   //af_cube_map_A = builder.glsl_create_cubemap_from_vertical_strip("data/bitmaps/sky4.png");
   //af_cube_map_B = builder.glsl_create_cubemap_from_vertical_strip("data/bitmaps/sky5_with_grid.png");
   cube_map_A = builder.glsl_create_cubemap_from_vertical_strip("data/bitmaps/sky4.png");
   cube_map_B = builder.glsl_create_cubemap_from_vertical_strip("data/bitmaps/sky5_with_grid.png");

   //cube_map_A = new ALLEGRO_FLARE_CUBEMAP_TEXTURE{af_cube_map_A->get_id()};
   //cube_map_B = new ALLEGRO_FLARE_CUBEMAP_TEXTURE{af_cube_map_B->get_id()};


   //if (!cube_map_A) std::cout << "!!! Could not load cube_map_A" << std::endl;
   //if (!cube_map_B) std::cout << "!!! Could not load cube_map_B" << std::endl;


   initialized = true;
};

//ALLEGRO_FLARE_CUBEMAP_TEXTURE *CubeMapRepository::get_cube_map_A()
//{
   //if (!initialized) throw std::runtime_error("!!! CubeMapRepository called without being initialized.");
   //return cube_map_A;
//}

//ALLEGRO_FLARE_CUBEMAP_TEXTURE *CubeMapRepository::get_cube_map_B()
//{
   //if (!initialized) throw std::runtime_error("!!! CubeMapRepository called without being initialized.");
   //return cube_map_B;
//}


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





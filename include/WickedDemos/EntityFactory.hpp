#pragma once


#include <WickedDemos/ModelRepository.hpp>
#include <WickedDemos/CubeMapRepository.hpp>
#include <AllegroFlare/Random.hpp>
#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Vec3D.hpp>


#include <Wicked/Entity.hpp>
using Wicked::Entity;
using AllegroFlare::BitmapBin;
using AllegroFlare::vec2d;
using AllegroFlare::vec3d;


//#include <allegro_flare/shader.h>
//using allegro_flare::ALLEGRO_FLARE_CUBEMAP_TEXTURE;
//using allegro_flare::Shader;

#include <AllegroFlare/Shader.hpp>
#include <AllegroFlare/Cubemap.hpp>


class EntityFactory
{
private:
   ModelRepository model_repository;
   CubeMapRepository cube_map_repository;
   BitmapBin bitmap_bin;
   //ALLEGRO_FLARE_CUBEMAP_TEXTURE *cube_map_A;
   //ALLEGRO_FLARE_CUBEMAP_TEXTURE *cube_map_B;
   AllegroFlare::Shader *cubemap_shader;
   AllegroFlare::Shader *simple_map_shader;
   AllegroFlare::Shader *standard_compound_shader;
   bool initialized;
   Tileo::Atlas atlas;
   //Tileo::Mesh *mesh;
   AllegroFlare::Random random;


public:
   EntityFactory();

   Tileo::Atlas &get_atlas();

   void initialize();

   Entity *create_basic_mesh(int num_columns=3, int num_rows=5, vec3d position=vec3d{0, 0, 0});
   Entity *create_skybox(ALLEGRO_COLOR cube_box_color=ALLEGRO_COLOR{1.0, 0.74, 0.0, 1.0}, float cube_box_opacity=0.6);
   Entity *create_10x10_floor(vec3d position=vec3d{0, 0, 0});
   Entity *create_wood_plank_01(vec3d position=vec3d{0, 0, 0});
   Entity *create_ladder_01(vec3d position=vec3d{0, 0, 0});
   Entity *create_bridge_01(vec3d position=vec3d{0, 0, 0});
   Entity *create_platform_01(vec3d position=vec3d{0, 0, 0});
   Entity *create_pillar_1x1x3(vec3d position=vec3d{0, 0, 0});
   Entity *create_as_basic(std::string model_identifier, std::string texture, std::string type, vec3d position=vec3d{0, 0, 0});
   Entity *create_mushed_up_cube(vec3d position=vec3d{0, 0, 0});
   Entity *create_cube(vec3d position=vec3d{0, 0, 0});
   Entity *create_coin_ring(vec3d position=vec3d{0, 0, 0});
   Entity *create_stone_fence(vec3d position=vec3d{0, 0, 0});
   Entity *create_archway(vec3d position=vec3d{0, 0, 0});
   Entity *create_black_stone(vec3d position=vec3d{0, 0, 0});
   Entity *create_metal_cube(vec3d position=vec3d{0, 0, 0});
   Entity *create_stairbox(vec3d position=vec3d{0, 0, 0}, float y_rotation=0);
   Entity *create_pointer(vec3d position={0, 0, 0});
   Entity *create_plate_2x2(vec3d position={0, 0, 0}, float y_rotation=0);
   Entity *create_plate_2x10(vec3d position={0, 0, 0}, float y_rotation=0);
   Entity *create_plate_10x10(vec3d position={0, 0, 0}, float y_rotation=0);
   Entity *create_by_type(std::string type);

   float random_float(float min, float max);
   int random_sign();
};




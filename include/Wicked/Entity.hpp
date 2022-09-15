#pragma once

#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <Tileo/Atlas.hpp>
#include <Tileo/Mesh.hpp>
#include <AllegroFlare/Model3D.hpp>
//#include <AllegroFlare/Shader.hpp>
#include <AllegroFlare/Cubemap.hpp>


#include <allegro_flare/shader.h>
using allegro_flare::Shader;
using allegro_flare::ALLEGRO_FLARE_CUBEMAP_TEXTURE;

using AllegroFlare::vec2d;



namespace Wicked
{


class Entity
{
private:
   static int next_id;
   int id;

public:
  AllegroFlare::Placement3D place;
  AllegroFlare::Placement3D velocity;
  AllegroFlare::Model3D *model;
  bool shader_applies_transform;


  Tileo::Atlas *atlas;
  Tileo::Mesh *mesh;


  // Eventually, there could be n shaders for each model
  // for example, one for each named object.  Initially,
  // however, we'll stick with one shader and texture set
  // per entity.
  Shader *shader;

  // union of shader datas (should separate into derived shaders)
  ALLEGRO_BITMAP *diffuse_texture;
  ALLEGRO_BITMAP *normal_texture;
  ALLEGRO_BITMAP *specular_texture;
  ALLEGRO_FLARE_CUBEMAP_TEXTURE *cube_map_A;
  ALLEGRO_FLARE_CUBEMAP_TEXTURE *cube_map_B;
  //AllegroFlare::Cubemap *cube_map_A;
  //AllegroFlare::Cubemap *cube_map_B;
  bool cube_map_reflecting;
  ALLEGRO_COLOR cube_box_color;
  float cube_box_opacity;

  bool is_selected_with_cursor;
  std::string name;
  std::string type;

  int get_id();
  static int get_last_id();
  void __set_id(int id);
  static void __set_next_id(int next_id);

  Entity();

  void draw_for_depth_pass(Shader *shader_for_depth_pass);
  void draw(AllegroFlare::vec3d camera_position,
      AllegroFlare::vec3d light_position,
      ALLEGRO_TRANSFORM *shadow_map_depth_pass_transform=nullptr,
      ALLEGRO_BITMAP *shadow_map_depth_pass_surface=nullptr,
      AllegroFlare::vec2d texture_offset=0
   );
};
//int Entity::next_id = 1;


} // namesapce Wicked




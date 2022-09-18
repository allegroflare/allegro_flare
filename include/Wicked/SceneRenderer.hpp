#pragma once


#include <allegro5/allegro.h> // for ALLEGRO_BITMAP
//#include <AllegroFlare/Shader.hpp>
#include <Wicked/Entity.hpp>
#include <Wicked/ShadowCastingLight.hpp>
//#include <AllegroFlare/Placement3D.hpp>


using AllegroFlare::Placement3D;
//using allegro_flare::placement3d;
using AllegroFlare::vec3d;
using AllegroFlare::vec2d;
using AllegroFlare::Shader;

//#include <allegro_flare/shader.h>
//using allegro_flare::Shader;


namespace Wicked
{

class SceneRenderer
{
private:
   ALLEGRO_BITMAP *backbuffer_sub_bitmap;
   AllegroFlare::Shader *depth_shader;
   float shadow_scale_divisor; // note, increasing this divisor will
         // expand the range of the light projection, but it will reduce its resolution, a divisor of 1 will have a good
         // quality of shadow, but will have a range of about 15-20 meters; a divisor of 2 will double that size,
         // but reduce. the resolution of the shadow. Original engine had a default of 1.0f;
   bool initialized;

public:
   SceneRenderer();

   void initialize();

   void set_shadow_scale_divisor(float shadow_scale_divisor=1.0f);

   void set_backbuffer_sub_bitmap(ALLEGRO_BITMAP *backbuffer_sub_bitmap);

   void refresh_shadow_map(
         std::vector<Entity *> *_entities=nullptr,
         ShadowCastingLight casting_light={},
         ALLEGRO_TRANSFORM *shadow_map_depth_pass_transform=nullptr,
         ALLEGRO_BITMAP *shadow_map_depth_pass_surface=nullptr,
         Entity *pointer=nullptr
      );

   void setup_projection_SHADOW(ShadowCastingLight &shadow_casting_light, ALLEGRO_TRANSFORM *transform_to_fill=nullptr);

   void setup_projection_SCENE(AllegroFlare::Camera3D &camera, ALLEGRO_TRANSFORM *transform_to_fill=nullptr);

   void draw_entities(
         vec3d camera_real_position,
         vec3d light_position,
         Entity *skybox,
         std::vector<Entity *> *_entities, 
         ALLEGRO_TRANSFORM *shadow_map_depth_pass_transform=nullptr,
         ALLEGRO_BITMAP *shadow_map_depth_pass_surface=nullptr,
         vec2d texture_offset=0,
         Entity *pointer=nullptr,
         vec3d camera_looking_at_point=vec3d{0, 0, 0}
      );

   void draw_scene();

   void render();
};
} // namespace Wicked



#pragma once

#include <vector>
#include <Wicked/Entity.hpp>
#include <Wicked/Camera3.hpp>
#include <Wicked/ShadowCastingLight.hpp>
#include <WickedDemos/EntityFactory.hpp>


class SceneFactory
{
public:
   void create_ring_of_rings(
      std::vector<Entity*> *_entities,
      EntityFactory &entity_factory,
      vec3d central_position=vec3d{0, 0, 0},
      float radius=2
   );

   void load_level_from_file(
      std::vector<Entity*> *_entities,
      EntityFactory &entity_factory,
      Entity **skybox,
      std::string filename,
      Wicked::Camera3 &camera,
      ShadowCastingLight &casting_light
   );

   void construct_scene(
      std::vector<Entity*> *_entities,
      EntityFactory &entity_factory,
      Entity **skybox
   );
};





#include <Wicked/SceneFactory.hpp>

#include <Wicked/LevelLoader.hpp>



   void SceneFactory::create_ring_of_rings(
      std::vector<Entity*> *_entities,
      EntityFactory &entity_factory,
      vec3d central_position,
      float radius
   )
   {
      if (!_entities) throw std::runtime_error("need entities in SceneFactory");
      std::vector<Entity*> &entities = (*_entities);
      Entity *entity = nullptr;

      int coin_count = 6;
      float TAU = 3.141592653 * 2;

      entity = entity_factory.create_coin_ring(vec3d(central_position.x, central_position.y+0.5, central_position.z));
      entities.push_back(entity);
         
      for (int i=0; i<coin_count; i++)
      {
         float pass = TAU / coin_count * i;
         float x = sin(pass) * radius;
         float z = cos(pass) * radius;
         //float x = 0;
         //float y = 0;
         //float z = 0;

         entity = entity_factory.create_coin_ring(vec3d(central_position.x+x, central_position.y+0.5, central_position.z+z));
         entities.push_back(entity);
      }
   }



   void SceneFactory::load_level_from_file(
      std::vector<Entity*> *_entities,
      EntityFactory &entity_factory,
      Entity **skybox,
      std::string filename,
      AllegroFlare::Camera3D &camera,
      ShadowCastingLight &casting_light
   )
   {
      if (!_entities) throw std::runtime_error("need entities in SceneFactory");
      if (!(skybox)) throw std::runtime_error("need skybox in SceneFactory");
      std::vector<Entity*> &entities = (*_entities);

      LevelLoader level_loader(filename);
      std::vector<Entity *> loaded_entities;
      
      //Entity *skybox = nullptr;
      level_loader.load(entity_factory, loaded_entities, skybox, camera, casting_light);

      entities.clear(); // todo delete the existing entities
      entities = loaded_entities;
   }



   void SceneFactory::construct_scene(std::vector<Entity*> *_entities, EntityFactory &entity_factory, Entity **skybox)
   {
      if (!_entities) throw std::runtime_error("need entities in SceneFactory::construct_scene");
      if (!(skybox)) throw std::runtime_error("need skybox in SceneFactory::construct_scene");

      (*skybox) = entity_factory.create_skybox(ALLEGRO_COLOR{1.0, 0.74, 0.0, 1.0}, 0.6);

      std::vector<Entity*> &entities = (*_entities);
      Entity *entity = nullptr;

      // add the floors
      entity = entity_factory.create_10x10_floor(vec3d(0, 0, 0));
         entities.push_back(entity);

      // round the plane
      entity = entity_factory.create_10x10_floor(vec3d(10, 1, 0));
         entities.push_back(entity);
      entity = entity_factory.create_10x10_floor(vec3d(-10, -1, 0));
         entities.push_back(entity);
      entity = entity_factory.create_10x10_floor(vec3d(0, -1, 10));
         entities.push_back(entity);
      entity = entity_factory.create_plate_10x10(vec3d(0, 2, -10));
         entities.push_back(entity);


      // add plate
      entity = entity_factory.create_plate_2x2(vec3d(0, 2.5, -10));
         entities.push_back(entity);


      // add a walkway
      entity = entity_factory.create_plate_2x10(vec3d(10, 2.5, -10), 0.25);
         entities.push_back(entity);
      // big plate
      entity = entity_factory.create_10x10_floor(vec3d(20, 2.0, -10));
         entities.push_back(entity);
      //entity = entity_factory.create_plate_2x10(vec3d(10, 2.5, -10), 0.25);
         //entities.push_back(entity);
      entity = entity_factory.create_plate_2x10(vec3d(20, 1.5, 0), 0);
         entities.push_back(entity);

   
      //// add all the random rounded cubes
      //for (unsigned i=0; i<5; i++)
      //{
         ////entity = entity_factory.create_cube(vec3d(random_float(-5, 5), random_float(0, 5), random_float(-5, 5)));
         ////entities.push_back(entity);
      //}


      create_ring_of_rings(_entities, entity_factory);


      //// add all the coin rings
      //vec3d central_position = vec3d{0, 0, 0};
      //float radius 2;
      //float count = 5;
      //for (unsigned i=0; i<5; i++)
      //{
         //entity = entity_factory.create_coin_ring(vec3d(random_float(-5, 5), 0.5, random_float(-5, 5)));
         //entities.push_back(entity);
      //}


      //// add the archway, and surrounding fencing
      entity = entity_factory.create_archway(vec3d(-10, -1, 0));
      entities.push_back(entity);
      entity = entity_factory.create_stone_fence(vec3d(-10, -1, -4));
      entities.push_back(entity);
      entity = entity_factory.create_stone_fence(vec3d(-10, -1, 4));
      entities.push_back(entity);


      entity = entity_factory.create_archway(vec3d(10, 1, 0));
      entities.push_back(entity);
      entity = entity_factory.create_stone_fence(vec3d(10, 1, -4));
      entities.push_back(entity);
      entity = entity_factory.create_stone_fence(vec3d(10, 1, 4));
      entities.push_back(entity);




      // add a few black-rock stones
      for (unsigned i=0; i<4; i++)
      {
         entity = entity_factory.create_black_stone(vec3d(1.5 * i - 1, 0.5, -4));
         entities.push_back(entity);
      }



      //entity = entity_factory.create_stairbox(vec3d(0, 0.5, -4));
      //entities.push_back(entity);


      entity = entity_factory.create_stairbox(vec3d(4, 0, 0), 0.75);
      entities.push_back(entity);


      //// add all the metal cubes
      //for (unsigned i=0; i<5; i++)
      //{
         //entity = entity_factory.create_metal_cube(vec3d(random_float(-5, 5), 0.5, random_float(-5, 5)));
         //entities.push_back(entity);
      //}
   }






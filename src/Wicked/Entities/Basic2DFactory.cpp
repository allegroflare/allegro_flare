

#include <Wicked/Entities/Basic2DFactory.hpp>

#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <Tileo/TMJMeshLoader.hpp>
#include <Wicked/Entities/Doors/Basic2D.hpp>
#include <Wicked/Entities/MovementStrategies2D/BackAndForthHorizontal.hpp>
#include <Wicked/Entities/MovementStrategies2D/FallOnTrackingRange.hpp>
#include <Wicked/Entities/MovementStrategies2D/Flapping.hpp>
#include <Wicked/Entities/MovementStrategies2D/FlappingWithRandomness.hpp>
#include <Wicked/Entities/MovementStrategies2D/HoppingLeft.hpp>
#include <Wicked/Entities/MovementStrategies2D/MoveInDirection.hpp>
#include <Wicked/Entities/MovementStrategies2D/ReflectOffWalls.hpp>
#include <Wicked/Entities/MovementStrategies2D/Tracking.hpp>
#include <Wicked/EntityFlagNames.hpp>
#include <WickedDemos/TileMaps/Basic2D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{


Basic2DFactory::Basic2DFactory(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
   , enemy_debug_box_color(ALLEGRO_COLOR{0.827, 0.184, 0.184, 1.0})
   , player_collectable_box_color(ALLEGRO_COLOR{0.96, 0.93, 0.06, 1.0})
   , goalpost_box_color(ALLEGRO_COLOR{0.06, 0.93, 0.184, 1.0})
{
}


Basic2DFactory::~Basic2DFactory()
{
}


Wicked::Entities::Basic2D* Basic2DFactory::create_from_bitmap_filename(std::string map_name, std::string bitmap_filename, std::string bitmap_alignment_strategy)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::Basic2DFactory::create_from_bitmap_filename]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::Basic2DFactory::create_from_bitmap_filename]: error: guard \"bitmap_bin\" not met");
   }
   ALLEGRO_BITMAP *bitmap = bitmap_bin->operator[](bitmap_filename);
   Wicked::Entities::Basic2D *result = new Wicked::Entities::Basic2D;
   result->set_bitmap(bitmap);
   result->fit_to_bitmap();
   result->set_bitmap_alignment_strategy(bitmap_alignment_strategy);
   result->set(ON_MAP_NAME, map_name);
   return result;
}

Wicked::Entities::Basic2D* Basic2DFactory::create_for_aabb2d(std::string map_name, float width, float height)
{
   //ALLEGRO_BITMAP *bitmap = bitmap_bin->operator[](bitmap_filename);
   Wicked::Entities::Basic2D *result = new Wicked::Entities::Basic2D;
   result->get_place_ref().size.x = width;
   result->get_place_ref().size.y = height;
   //result->set_bitmap(bitmap);
   result->set(ON_MAP_NAME, map_name);
   //result->fit_to_bitmap();
   //result->set_bitmap_alignment_strategy(bitmap_alignment_strategy);
   return result;
}

Wicked::Entities::Basic2D* Basic2DFactory::create_player_projectile(std::string map_name, float x, float y, float width, float height, AllegroFlare::vec2d vector, float magnitude)
{
   vector = vector.normalized();
   vector *= magnitude;
   Wicked::Entities::Basic2D *created_entity = new Wicked::Entities::Basic2D;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;
   created_entity->get_place_ref().size.x = width;
   created_entity->get_place_ref().size.y = height;
   created_entity->get_velocity_ref().position.x = vector.x;
   created_entity->get_velocity_ref().position.y = vector.y;
   created_entity->set(NOT_AFFECTED_BY_GRAVITY);
   created_entity->get(DOES_NOT_COLLIDE_WITH_WORLD);

   created_entity->set(ON_MAP_NAME, map_name);

   return created_entity;
}

Wicked::Entities::Enemies::Base* Basic2DFactory::create_enemy_move_left(std::string map_name, float x, float y, float width, float height)
{
   // create the enemy
   Wicked::Entities::Enemies::Base *created_entity = new Wicked::Entities::Enemies::Base;
   created_entity->get_place_ref().size.x = width;
   created_entity->get_place_ref().size.y = height;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // create the movement strategy
   Wicked::Entities::MovementStrategies2D::HoppingLeft* movement_strategy =
      new Wicked::Entities::MovementStrategies2D::HoppingLeft(created_entity);

   // assign the movement strategy to the entity
   created_entity->set_movement_strategy(movement_strategy);

   // set as "damages_player"
   // created_entity->set("damages_player"); // <-- soon

   // give it a "enemy" debug box color
   created_entity->set_debug_box_color(enemy_debug_box_color);

   created_entity->set(ON_MAP_NAME, map_name);

   // return the entity
   return created_entity;
}

Wicked::Entities::Enemies::Base* Basic2DFactory::create_tracking_enemy(std::string map_name, Wicked::Entities::Basic2D* tracked_entity, float x, float y, float width, float height)
{
   // create the enemy
   Wicked::Entities::Enemies::Base *created_entity = new Wicked::Entities::Enemies::Base;
   created_entity->get_place_ref().size.x = width;
   created_entity->get_place_ref().size.y = height;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // create the movement strategy
   Wicked::Entities::MovementStrategies2D::ReflectOffWalls* movement_strategy =
      new Wicked::Entities::MovementStrategies2D::ReflectOffWalls(created_entity);

   // create the movement strategy
   //Wicked::Entities::MovementStrategies2D::Tracking* movement_strategy =
   //   new Wicked::Entities::MovementStrategies2D::Tracking(created_entity, tracked_entity);

   // create the movement strategy
   //Wicked::Entities::MovementStrategies2D::FallOnTrackingRange* movement_strategy =
   //   new Wicked::Entities::MovementStrategies2D::FallOnTrackingRange(created_entity, tracked_entity);

   // assign the movement strategy to the entity
   created_entity->set_movement_strategy(movement_strategy);

   // set as "damages_player"
   // created_entity->set("damages_player"); // <-- soon

   // give it a "enemy" debug box color
   created_entity->set_debug_box_color(enemy_debug_box_color);

   created_entity->set(ON_MAP_NAME, map_name);

   // return the entity
   return created_entity;
}

Wicked::Entities::Enemies::Base* Basic2DFactory::create_flapping_enemy(std::string map_name, float x, float y, float width, float height, float target_elevation, float flap_strength, float flap_recovery_rate)
{
   static unsigned int seed = 7654;
   seed++;
   // create the enemy
   Wicked::Entities::Enemies::Base *created_entity = new Wicked::Entities::Enemies::Base;
   created_entity->get_place_ref().size.x = width;
   created_entity->get_place_ref().size.y = height;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // create the movement strategy
   Wicked::Entities::MovementStrategies2D::FlappingWithRandomness* movement_strategy =
      new Wicked::Entities::MovementStrategies2D::FlappingWithRandomness(created_entity);
   movement_strategy->set_target_elevation(target_elevation);
   movement_strategy->set_flap_strength(flap_strength);
   movement_strategy->set_flap_recovery_rate(flap_recovery_rate);
   movement_strategy->set_random_seed(seed);

   // assign the movement strategy to the entity
   created_entity->set_movement_strategy(movement_strategy);

   // set as "damages_player"
   // created_entity->set("damages_player"); // <-- soon

   // give it a "enemy" debug box color
   created_entity->set_debug_box_color(enemy_debug_box_color);

   created_entity->set(ON_MAP_NAME, map_name);

   // return the entity
   return created_entity;
}

Wicked::Entities::Basic2D* Basic2DFactory::create_collectable(std::string map_name, float x, float y)
{
   // create the enemy
   Wicked::Entities::Basic2D *created_entity = new Wicked::Entities::Basic2D;
   created_entity->get_place_ref().size.x = 15.0f;
   created_entity->get_place_ref().size.y = 15.0f;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // give it a noticable box color
   created_entity->set_debug_box_color(player_collectable_box_color);

   created_entity->set(COLLECTABLE_BY_PLAYER);
   created_entity->set(ON_MAP_NAME, map_name);

   // return the entity
   return created_entity;
}

Wicked::Entities::Basic2D* Basic2DFactory::create_door(std::string map_name, float x, float y, std::string target_map_name, float target_spawn_x, float target_spawn_y)
{
   // create the enemy
   Wicked::Entities::Doors::Basic2D *created_door = new Wicked::Entities::Doors::Basic2D;
   created_door->get_place_ref().size.x = (32.0f - 8.0f) - 1.0f;
   created_door->get_place_ref().size.y = (32.0f + 8.0f) - 1.0f;
   created_door->get_place_ref().position.x = x;
   created_door->get_place_ref().position.y = y;
   created_door->set_game_event_name_to_emit(""); // TODO: fix this requirement:
                                                  // this must be set to blank to not activate as an event
   created_door->set_target_map_name(target_map_name);
   created_door->set_target_spawn_x(target_spawn_x);
   created_door->set_target_spawn_y(target_spawn_y);

   // give it a noticable box color
   created_door->set_debug_box_color(goalpost_box_color);

   created_door->set(TYPE, DOOR);
   created_door->set(ON_MAP_NAME, map_name);

   // return the entity
   return created_door;
}

Wicked::Entities::Basic2D* Basic2DFactory::create_game_event_door(std::string map_name, float x, float y, std::string game_event_name_to_emit)
{
   // create the enemy
   Wicked::Entities::Doors::Basic2D *created_door = new Wicked::Entities::Doors::Basic2D;
   created_door->get_place_ref().size.x = (32.0f - 8.0f) - 1.0f;
   created_door->get_place_ref().size.y = (32.0f + 8.0f) - 1.0f;
   created_door->get_place_ref().position.x = x;
   created_door->get_place_ref().position.y = y;
   created_door->set_game_event_name_to_emit(game_event_name_to_emit);
   //created_door->set_target_map_name(target_map_name);
   //created_door->set_target_spawn_x(target_spawn_x);
   //created_door->set_target_spawn_y(target_spawn_y);

   // give it a noticable box color
   created_door->set_debug_box_color(goalpost_box_color);

   created_door->set(TYPE, DOOR);
   created_door->set(ON_MAP_NAME, map_name);

   // return the entity
   return created_door;
}

Wicked::Entities::Basic2D* Basic2DFactory::create_goalpost(std::string map_name, float x, float y)
{
   // create the enemy
   Wicked::Entities::Basic2D *created_entity = new Wicked::Entities::Basic2D;
   created_entity->get_place_ref().size.x = 16.0f - 1.0f;
   created_entity->get_place_ref().size.y = 32.0f - 1.0f;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // give it a noticable box color
   created_entity->set_debug_box_color(goalpost_box_color);

   created_entity->set(TYPE, GOALPOST);
   created_entity->set(ON_MAP_NAME, map_name);

   // return the entity
   return created_entity;
}

Wicked::Entities::Basic2D* Basic2DFactory::create_tile_map(std::string map_json_filename, std::string map_name)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::Basic2DFactory::create_tile_map]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::Basic2DFactory::create_tile_map]: error: guard \"bitmap_bin\" not met");
   }
   //throw std::runtime_error("create_tile_map not implemented!!");
   //AllegroFlare::TileMaps::Basic2D *created_map = nullptr;
   WickedDemos::TileMaps::Basic2D *created_map = nullptr;
   AllegroFlare::TileMaps::PrimMeshAtlas *tile_atlas = nullptr; //  = tmj_mesh_loader.get_tile_atlas();
   AllegroFlare::TileMaps::PrimMesh *tile_mesh = nullptr; // = tmj_mesh_loader.get_mesh();
   AllegroFlare::TileMaps::TileMap<int> *collision_tile_mesh = nullptr; //tmj_mesh_loader.get_collision_tile_map();


   //created_map = new AllegroFlare::TileMaps::Basic2D;
   created_map = new WickedDemos::TileMaps::Basic2D;

   Tileo::TMJMeshLoader tmj_mesh_loader(bitmap_bin, map_json_filename);

   tmj_mesh_loader.load();

   tile_atlas = tmj_mesh_loader.get_tile_atlas();
   tile_mesh = tmj_mesh_loader.get_mesh();
   collision_tile_mesh = tmj_mesh_loader.get_collision_tile_map();


   if (!tile_mesh)
   {
      throw std::runtime_error("ERROR Basic2DFactory::create_tile_map could not create tile_mesh");
   }

   created_map->set_tile_atlas(tile_atlas);
   created_map->set_tile_mesh(tile_mesh);
   created_map->set_collision_tile_mesh(collision_tile_mesh);
   created_map->set(MAP_NAME, map_name); //"map_a"); //set_collision_tile_mesh(collision_tile_mesh);

   return created_map;
   //entities.push_back(created_map); // TODO: prevent maps from having the same name
}


} // namespace Entities
} // namespace Wicked



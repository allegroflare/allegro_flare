

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Doors/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/BackAndForthHorizontal.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/FallOnTrackingRange.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/Flapping.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/FlappingWithRandomness.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/HoppingLeft.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/MoveInDirection.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/ReflectOffWalls.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/MovementStrategies2D/Tracking.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/TileMaps/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/TMJMeshLoader.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoader.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/PrimMeshAtlas.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{


Basic2DFactory::Basic2DFactory(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FrameAnimation::Book* animation_book)
   : bitmap_bin(bitmap_bin)
   , animation_book(animation_book)
   , init_entities_drawing_debug(false)
   , enemy_debug_box_color(ALLEGRO_COLOR{0.827, 0.184, 0.184, 1.0})
   , player_collectable_box_color(ALLEGRO_COLOR{0.96, 0.93, 0.06, 1.0})
   , goalpost_box_color(ALLEGRO_COLOR{0.06, 0.93, 0.184, 1.0})
{
}


Basic2DFactory::~Basic2DFactory()
{
}


void Basic2DFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void Basic2DFactory::set_animation_book(AllegroFlare::FrameAnimation::Book* animation_book)
{
   this->animation_book = animation_book;
}


void Basic2DFactory::set_init_entities_drawing_debug(bool init_entities_drawing_debug)
{
   this->init_entities_drawing_debug = init_entities_drawing_debug;
}


AllegroFlare::BitmapBin* Basic2DFactory::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FrameAnimation::Book* Basic2DFactory::get_animation_book() const
{
   return animation_book;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Basic2DFactory::create_from_bitmap_filename(std::string map_name, std::string bitmap_filename, std::string bitmap_alignment_strategy) const
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Basic2DFactory::create_from_bitmap_filename]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2DFactory::create_from_bitmap_filename: error: guard \"bitmap_bin\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   ALLEGRO_BITMAP *bitmap = bitmap_bin->operator[](bitmap_filename);
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D *result =
      new AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D;
   result->set_bitmap(bitmap);
   result->fit_to_bitmap();
   result->set_bitmap_alignment_strategy(bitmap_alignment_strategy);
   result->set(ON_MAP_NAME, map_name);

   if (init_entities_drawing_debug) result->set_draw_debug(true);
   return result;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Basic2DFactory::create_for_aabb2d(std::string map_name, float width, float height) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   //ALLEGRO_BITMAP *bitmap = bitmap_bin->operator[](bitmap_filename);
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D *result =
      new AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D;
   result->get_place_ref().size.x = width;
   result->get_place_ref().size.y = height;
   //result->set_bitmap(bitmap);
   result->set(ON_MAP_NAME, map_name);
   //result->fit_to_bitmap();
   //result->set_bitmap_alignment_strategy(bitmap_alignment_strategy);
   if (init_entities_drawing_debug) result->set_draw_debug(true);
   return result;
}

AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D* Basic2DFactory::create_frame_animated(std::string map_name, float x, float y, float w, float h, std::string initial_animation_name, std::string bitmap_alignment_strategy) const
{
   if (!(animation_book))
   {
      std::stringstream error_message;
      error_message << "[Basic2DFactory::create_frame_animated]: error: guard \"animation_book\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2DFactory::create_frame_animated: error: guard \"animation_book\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   using namespace AllegroFlare::Prototypes::Platforming2D;

   Entities::FrameAnimated2D *result = new Entities::FrameAnimated2D;
   result->set_animation_book(animation_book);
   result->get_place_ref().position.x = x;
   result->get_place_ref().position.y = y;
   result->get_place_ref().size.x = w;
   result->get_place_ref().size.y = h;
   result->set_animation(initial_animation_name);
   //result->fit_to_bitmap(); // <-- TODO: don't think this is necessary, done automatically with "set_animation"
   result->set_bitmap_alignment_strategy(bitmap_alignment_strategy);
   result->get_bitmap_placement_ref().scale =
      {
         1.0f / animation_book->get_sprite_sheet_scale(),
         1.0f / animation_book->get_sprite_sheet_scale(),
      };

   result->set(ON_MAP_NAME, map_name);

   if (init_entities_drawing_debug) result->set_draw_debug(true);
   return result;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Basic2DFactory::create_player_projectile(std::string map_name, float x, float y, float width, float height, AllegroFlare::vec2d vector, float magnitude) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   vector = vector.normalized();
   vector *= magnitude;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D *created_entity = new AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;
   created_entity->get_place_ref().size.x = width;
   created_entity->get_place_ref().size.y = height;
   created_entity->get_velocity_ref().position.x = vector.x;
   created_entity->get_velocity_ref().position.y = vector.y;
   created_entity->set(NOT_AFFECTED_BY_GRAVITY);
   created_entity->get(DOES_NOT_COLLIDE_WITH_WORLD);

   created_entity->set(ON_MAP_NAME, map_name);

   if (init_entities_drawing_debug) created_entity->set_draw_debug(true);
   return created_entity;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base* Basic2DFactory::create_enemy(std::string map_name, float x, float y, float width, float height) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // create the enemy
   AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base *created_entity =
      new AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base;
   created_entity->get_place_ref().size.x = width;
   created_entity->get_place_ref().size.y = height;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // create the movement strategy
   //AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft* movement_strategy =
   //new AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft(created_entity);

   // assign the movement strategy to the entity
   //created_entity->set_movement_strategy(movement_strategy);

   // set as "damages_player"
   // created_entity->set("damages_player"); // <-- soon

   // give it a "enemy" debug box color
   created_entity->set_debug_box_color(enemy_debug_box_color);

   created_entity->set(ON_MAP_NAME, map_name);

   // return the entity
   if (init_entities_drawing_debug) created_entity->set_draw_debug(true);
   return created_entity;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base* Basic2DFactory::create_enemy_move_left(std::string map_name, float x, float y, float width, float height) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // create the enemy
   AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base *created_entity =
      new AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base;
   created_entity->get_place_ref().size.x = width;
   created_entity->get_place_ref().size.y = height;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // create the movement strategy
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft* movement_strategy =
   new AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::HoppingLeft(created_entity);

   // assign the movement strategy to the entity
   created_entity->set_movement_strategy(movement_strategy);

   // set as "damages_player"
   // created_entity->set("damages_player"); // <-- soon

   // give it a "enemy" debug box color
   created_entity->set_debug_box_color(enemy_debug_box_color);

   created_entity->set(ON_MAP_NAME, map_name);

   // return the entity
   if (init_entities_drawing_debug) created_entity->set_draw_debug(true);
   return created_entity;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base* Basic2DFactory::create_tracking_enemy(std::string map_name, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* tracked_entity, float x, float y, float width, float height) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // create the enemy
   AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base *created_entity =
      new AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base;
   created_entity->get_place_ref().size.x = width;
   created_entity->get_place_ref().size.y = height;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // create the movement strategy
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::ReflectOffWalls* movement_strategy =
   new AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::ReflectOffWalls(created_entity);

   // create the movement strategy
   //AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Tracking* movement_strategy =
   //   new AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Tracking(created_entity, tracked_entity);

   // create the movement strategy
   //AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::FallOnTrackingRange* movement_strategy =
   //   new AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::FallOnTrackingRange(created_entity, tracked_entity);

   // assign the movement strategy to the entity
   created_entity->set_movement_strategy(movement_strategy);

   // set as "damages_player"
   // created_entity->set("damages_player"); // <-- soon

   // give it a "enemy" debug box color
   created_entity->set_debug_box_color(enemy_debug_box_color);

   created_entity->set(ON_MAP_NAME, map_name);

   // return the entity
   if (init_entities_drawing_debug) created_entity->set_draw_debug(true);
   return created_entity;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base* Basic2DFactory::create_flapping_enemy(std::string map_name, float x, float y, float width, float height, float target_elevation, float flap_strength, float flap_recovery_rate) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   static unsigned int seed = 7654;
   seed++;
   // create the enemy
   AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base *created_entity =
      new AllegroFlare::Prototypes::Platforming2D::Entities::Enemies::Base;
   created_entity->get_place_ref().size.x = width;
   created_entity->get_place_ref().size.y = height;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // create the movement strategy
   AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::FlappingWithRandomness* movement_strategy =
   new AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::FlappingWithRandomness(created_entity);
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
   if (init_entities_drawing_debug) created_entity->set_draw_debug(true);
   return created_entity;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Basic2DFactory::create_collectable(std::string map_name, float x, float y) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // create the entity
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D *created_entity =
      new AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D;
   created_entity->get_place_ref().size.x = 15.0f;
   created_entity->get_place_ref().size.y = 15.0f;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // give it a noticable box color
   created_entity->set_debug_box_color(player_collectable_box_color);

   created_entity->set(COLLECTABLE_BY_PLAYER);
   created_entity->set(ON_MAP_NAME, map_name);

   // return the collectable entity
   if (init_entities_drawing_debug) created_entity->set_draw_debug(true);
   return created_entity;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Basic2DFactory::create_door(std::string map_name, float x, float y, std::string target_map_name, float target_spawn_x, float target_spawn_y) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // create the door entity
   AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D *created_door =
      new AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D;
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
   if (init_entities_drawing_debug) created_door->set_draw_debug(true);
   return created_door;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Basic2DFactory::create_game_event_door(std::string map_name, float x, float y, std::string game_event_name_to_emit) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // create the enemy
   AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D *created_door = new AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D;
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
   if (init_entities_drawing_debug) created_door->set_draw_debug(true);
   return created_door;
}

AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Basic2DFactory::create_goalpost(std::string map_name, float x, float y) const
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // create the enemy
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D *created_entity =
      new AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D;
   created_entity->get_place_ref().size.x = 16.0f - 1.0f;
   created_entity->get_place_ref().size.y = 32.0f - 1.0f;
   created_entity->get_place_ref().position.x = x;
   created_entity->get_place_ref().position.y = y;

   // give it a noticable box color
   created_entity->set_debug_box_color(goalpost_box_color);

   created_entity->set(TYPE, GOALPOST);
   created_entity->set(ON_MAP_NAME, map_name);

   // return the entity
   if (init_entities_drawing_debug) created_entity->set_draw_debug(true);
   return created_entity;
}

AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* Basic2DFactory::create_tile_map(std::string map_name, std::string map_json_filename, std::string tile_atlas_bitmap_identifier) const
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Basic2DFactory::create_tile_map]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2DFactory::create_tile_map: error: guard \"bitmap_bin\" not met");
   }
   // TODO: Note that "tile_atlas_bitmap_identifier" will need to be paired with more data, such as tile size
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D *created_map = nullptr;
   AllegroFlare::TileMaps::PrimMeshAtlas *tile_atlas = nullptr;
   AllegroFlare::TileMaps::PrimMesh *tile_mesh = nullptr;
   AllegroFlare::TileMaps::TileMap<int> *collision_tile_mesh = nullptr;
   created_map = new AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D;

   AllegroFlare::Prototypes::Platforming2D::TMJMeshLoader tmj_mesh_loader(
      bitmap_bin,
      map_json_filename,
      tile_atlas_bitmap_identifier
   );
   tmj_mesh_loader.load();

   tile_atlas = tmj_mesh_loader.get_tile_atlas();
   tile_mesh = tmj_mesh_loader.get_mesh();
   collision_tile_mesh = tmj_mesh_loader.get_collision_tile_map();

   if (!tile_atlas)
   {
      // TODO: Test this failure
      throw std::runtime_error("ERROR Basic2DFactory::create_tile_map could not create tile_atlas");
   }
   if (!tile_mesh)
   {
      // TODO: Test this failure
      throw std::runtime_error("ERROR Basic2DFactory::create_tile_map could not create tile_mesh");
   }
   if (!collision_tile_mesh)
   {
      // TODO: Test this failure
      throw std::runtime_error("ERROR Basic2DFactory::create_tile_map could not create collision_tile_mesh");
   }

   created_map->set_tile_atlas(tile_atlas);
   created_map->set_tile_mesh(tile_mesh);
   created_map->set_collision_tile_mesh(collision_tile_mesh);
   created_map->set(MAP_NAME, map_name);

   if (init_entities_drawing_debug) created_map->set_draw_debug(true);

   return created_map;
}

void Basic2DFactory::create_entities_from_map__tmj_obj_loader_callback_func(std::string object_type, float x, float y, float width, float height, int id, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties, void* data)
{
   if (!(data))
   {
      std::stringstream error_message;
      error_message << "[Basic2DFactory::create_entities_from_map__tmj_obj_loader_callback_func]: error: guard \"data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2DFactory::create_entities_from_map__tmj_obj_loader_callback_func: error: guard \"data\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // Cast our data param to its constituent parts
   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* entity_pool = nullptr;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory* basic2dfactory = nullptr;

   auto data_to_pass =
      static_cast<
         std::tuple<
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*,
            AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*
            // TODO: Add a "unhandled_tmj_object_type_callback" (or something to that effect)
         >*
      >(data);

   entity_pool = std::get<0>(*data_to_pass);
   basic2dfactory = std::get<1>(*data_to_pass);

   if (object_type == "hopper")
   {
      entity_pool->push_back(basic2dfactory->create_enemy_move_left("unset-map-name", x, y));
      entity_pool->back()->set(TMJ_OBJECT_TYPE, "hopper");
   }
   else if (object_type == "door")
   {
      // TODO: Parse these values from custom params
      std::string target_map_name = "yet-to-be-parsed-target-map_name";
      float target_spawn_x = 123.0f;
      float target_spawn_y = 456.0f;
      entity_pool->push_back(
         basic2dfactory->create_door("unset-map-name", x, y, target_map_name, target_spawn_x, target_spawn_y)
      );
      entity_pool->back()->set(TMJ_OBJECT_TYPE, "door");
   }
   else // An unrecognized object type
   {
      // TODO: Test this error emission
      // TODO: Add option to "throw_error" instead of "error_from" here
      // TODO: Add a custom callback option
      AllegroFlare::Logger::error_from(
         "AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory::"
            "create_entities_from_map__tmj_obj_loader_callback_func",
         "Unable to handle object_type \"" + object_type + "\"."
      );
   }

   return;
}

void Basic2DFactory::create_entities_from_map__tmj_obj_loader_with_callback_provided_func(std::string object_type, float x, float y, float width, float height, int id, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties, void* data)
{
   if (!(data))
   {
      std::stringstream error_message;
      error_message << "[Basic2DFactory::create_entities_from_map__tmj_obj_loader_with_callback_provided_func]: error: guard \"data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2DFactory::create_entities_from_map__tmj_obj_loader_with_callback_provided_func: error: guard \"data\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // Create variables for the constituent parts of *data
   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* entity_pool = nullptr;
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory* basic2dfactory = nullptr;
   std::function<void(
      std::string,
      float,
      float,
      float,
      float,
      AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, 
      std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*,
      AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*,
      void*)
   > user_callback;
   void* user_callback_data = nullptr;

   // Cast *data to the expected type
   auto data_to_pass =
      static_cast<
         std::tuple<
            std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*,
            AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*,
            decltype(user_callback),
            void*
            // TODO: Add a "unhandled_tmj_object_type_callback" (or something to that effect)
         >*
      >(data);

   // Assign the casted *data to the constituent parts
   entity_pool = std::get<0>(*data_to_pass);
   basic2dfactory = std::get<1>(*data_to_pass);
   user_callback = std::get<2>(*data_to_pass);
   user_callback_data = std::get<3>(*data_to_pass);


   if (!user_callback) {} // TODO: Do something here

   // Call the user callback, passing along the more friendly formatted parameters
   user_callback(
      object_type,
      x,
      y,
      width,
      height,
      custom_properties,
      entity_pool,
      basic2dfactory,
      user_callback_data
   );

   return;
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> Basic2DFactory::create_entities_from_map(std::string map_tmj_filename, std::string map_name, std::function<void( std::string, float, float, float, float, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*, void*) > callback, void* callback_data)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> result_entity_pool;

   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoader loader(map_tmj_filename);

   if (callback) // A callback is provided by the user, build data to pass into the factory's callback which includes
                 // the user's callback.
   {
      auto data_to_pass = std::tuple<
         std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*,
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*,
         decltype(callback),
         void*
      >(&result_entity_pool, this, callback, callback_data);

      loader.set_object_parsed_callback(create_entities_from_map__tmj_obj_loader_with_callback_provided_func);
      loader.set_object_parsed_callback_user_data((void*)(&data_to_pass));
   }
   else // If no callback is provided, use the default callback here in the factory
   {
      auto data_to_pass = std::tuple<
         std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*,
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*
      >(&result_entity_pool, this);

      loader.set_object_parsed_callback(create_entities_from_map__tmj_obj_loader_callback_func);
      loader.set_object_parsed_callback_user_data((void*)(&data_to_pass));
   }

   loader.load();

   // Flag all the created entities as being on this map
   for (auto &result_entity : result_entity_pool)
   {
      result_entity->set(ON_MAP_NAME, map_name);
   }

   return result_entity_pool;
}


} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare



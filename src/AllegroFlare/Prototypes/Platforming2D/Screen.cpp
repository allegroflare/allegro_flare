

#include <AllegroFlare/Prototypes/Platforming2D/Screen.hpp>

#include <AllegroFlare/CameraControlStrategies2D/HorizontalRail.hpp>
#include <AllegroFlare/CameraControlStrategies2D/SmoothSnap.hpp>
#include <AllegroFlare/CameraControlStrategies2D/SmoothSnapWithZoomEffect.hpp>
#include <AllegroFlare/CameraControlStrategies2D/Snap.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Physics/AABB2D.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Doors/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <algorithm>
#include <allegro5/allegro_color.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


Screen::Screen(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::Display* display, AllegroFlare::EventEmitter* event_emitter)
   : AllegroFlare::Screens::Base(AllegroFlare::Prototypes::Platforming2D::Screen::TYPE)
   , bitmap_bin(bitmap_bin)
   , display(display)
   , event_emitter(event_emitter)
   , currently_active_map(nullptr)
   , currently_active_map_name("[currently-active-map-name-unset]")
   , entity_pool({})
   , map_dictionary({})
   , gravity(0.25f)
   , gravity_reversed(false)
   , camera()
   , camera_baseline_zoom({4.8f, 4.5f})
   , player_controlled_entity(nullptr)
   , show_tile_mesh(true)
   , show_collision_tile_mesh(false)
   , gameplay_suspended(false)
   , show_visual_hint_on_suspended_gameplay(false)
   , player_controls()
   , camera_control_strategy(nullptr)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_entity_pool(std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> entity_pool)
{
   this->entity_pool = entity_pool;
}


void Screen::set_camera_baseline_zoom(AllegroFlare::Vec2D camera_baseline_zoom)
{
   this->camera_baseline_zoom = camera_baseline_zoom;
}


void Screen::set_player_controlled_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity)
{
   this->player_controlled_entity = player_controlled_entity;
}


void Screen::set_show_tile_mesh(bool show_tile_mesh)
{
   this->show_tile_mesh = show_tile_mesh;
}


void Screen::set_show_collision_tile_mesh(bool show_collision_tile_mesh)
{
   this->show_collision_tile_mesh = show_collision_tile_mesh;
}


void Screen::set_show_visual_hint_on_suspended_gameplay(bool show_visual_hint_on_suspended_gameplay)
{
   this->show_visual_hint_on_suspended_gameplay = show_visual_hint_on_suspended_gameplay;
}


AllegroFlare::BitmapBin* Screen::get_bitmap_bin() const
{
   return bitmap_bin;
}


std::map<std::string, std::string> Screen::get_map_dictionary() const
{
   return map_dictionary;
}


AllegroFlare::Vec2D Screen::get_camera_baseline_zoom() const
{
   return camera_baseline_zoom;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Screen::get_player_controlled_entity() const
{
   return player_controlled_entity;
}


bool Screen::get_show_tile_mesh() const
{
   return show_tile_mesh;
}


bool Screen::get_show_collision_tile_mesh() const
{
   return show_collision_tile_mesh;
}


bool Screen::get_gameplay_suspended() const
{
   return gameplay_suspended;
}


bool Screen::get_show_visual_hint_on_suspended_gameplay() const
{
   return show_visual_hint_on_suspended_gameplay;
}


void Screen::set_map_dictionary(std::map<std::string, std::string> map_dictionary)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_map_dictionary]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_map_dictionary: error: guard \"(!initialized)\" not met");
   }
   this->map_dictionary = map_dictionary;
   // TODO: allow this to be set after initialization
   return;
}

void Screen::set_display(AllegroFlare::Display* display)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_display]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_display: error: guard \"(!initialized)\" not met");
   }
   this->display = display;
   return;
}

void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_event_emitter]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_event_emitter: error: guard \"(!initialized)\" not met");
   }
   this->event_emitter = event_emitter;
   return;
}

void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_bitmap_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_bitmap_bin: error: guard \"(!initialized)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void Screen::set_currently_active_map(std::string name)
{
   currently_active_map = find_map_by_name(name);
   if (!currently_active_map) throw std::runtime_error("Bruh, no map");
   currently_active_map_name = name;
   return;
}

AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* Screen::find_map_by_name(std::string name)
{
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&entity_pool);
   AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* found_map =
      collection_helper.find_map_by_name(name);
   if (!found_map)
   {
      std::stringstream error_message;
      error_message << "map named \"" << name << "\" does not exist.";
      throw std::runtime_error(error_message.str());

   }

   return found_map;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_activate: error: guard \"initialized\" not met");
   }
   // nothing here
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::on_deactivate: error: guard \"initialized\" not met");
   }
   // nothing here
   return;
}

void Screen::initialize_maps()
{
   if (!((!map_dictionary.empty())))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize_maps]: error: guard \"(!map_dictionary.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize_maps: error: guard \"(!map_dictionary.empty())\" not met");
   }
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory factory(bitmap_bin);

   for (auto &map_dictionary_entry : map_dictionary)
   {
      std::string map_name = std::get<0>(map_dictionary_entry);
      std::string map_filename = std::get<1>(map_dictionary_entry);
      AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D *created_map =
         factory.create_tile_map(map_filename, map_name);

      if (!created_map)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::Screen::initialize_maps",
            "Could not create map \"" + map_filename + "\""
         );
      }
      //else
      //{
         //std::cout << "NOTE: TMJ Tile map file \"" << map_filename << "\" loaded successfully." << std::endl;
      //}

      AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* __created_map =
         static_cast<AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D*>(created_map);

      if (!__created_map->get_tile_mesh())
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::Screen::initialize_maps",
            "Could not create tile mesh on \"" + map_filename + "\""
         );
      }


      if (!__created_map->get_tile_mesh()->get_initialized())
      {
         std::cout << "ERROR: prim mesh not initialized on \"" << map_filename << "\"" << std::endl;
      }
      else
      {
         std::cout << "NOTE: prim mesh initialized on \"" << map_filename << "\" loaded successfully." << std::endl;
      }


      if (!__created_map->get_collision_tile_mesh())
      {
         std::cout << "ERROR: collision tile map not loaded on \"" << map_filename << "\"" << std::endl;
      }
      else
      {
         std::cout << "NOTE: collision tile map loaded on \"" << map_filename << "\" loaded successfully." << std::endl;
      }


      if (!__created_map->get_collision_tile_mesh())
      {
         std::cout << "ERROR: collision tile map not loaded on \"" << map_filename << "\"" << std::endl;
      }
      else
      {
         std::cout << "NOTE: collision tile map loaded on \"" << map_filename << "\" loaded successfully." << std::endl;
      }


      entity_pool.push_back(created_map);
   }

   // NOTE: This code to acitvely set ht emap was previously here, but shouldn't be.  It's left here 
   // for a while as part of depreciation. Hopefully disabling it doesn't cause an issue:
   //set_currently_active_map("map_a");

   return;
}

void Screen::initialize_camera_control()
{
   float assumed_tile_width = 16.0f;
   float assumed_tile_height = 16.0f;
   float room_width = assumed_tile_width * 25; // tile_mesh->get_real_width();
   float room_height = assumed_tile_height * 15; //tile_mesh->get_real_height();

   //AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect *camera_control =
      //new AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect(room_width, room_height);
   AllegroFlare::CameraControlStrategies2D::HorizontalRail *camera_control =
      new AllegroFlare::CameraControlStrategies2D::HorizontalRail; //(room_width, room_height);
   camera_control->set_camera(&camera);
   camera_control->set_entity_to_follow(player_controlled_entity);
   camera_control->initialize();

   camera_control_strategy = camera_control;
   return;
}

void Screen::initialize_player_controls()
{
   player_controls.clear();
   return;
}

void Screen::initialize_camera()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize_camera]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize_camera: error: guard \"currently_active_map\" not met");
   }
   if (!(currently_active_map->get_tile_atlas()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize_camera]: error: guard \"currently_active_map->get_tile_atlas()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize_camera: error: guard \"currently_active_map->get_tile_atlas()\" not met");
   }
   if (!(currently_active_map->get_tile_mesh()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize_camera]: error: guard \"currently_active_map->get_tile_mesh()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize_camera: error: guard \"currently_active_map->get_tile_mesh()\" not met");
   }
   //camera.size = { 1920.0f, 1080.0f };
   camera.size = AllegroFlare::vec2d(1920.0f, 1080.0f);
   camera.align = AllegroFlare::vec2d(0.5, 0.5);

   //float width = tile_mesh->get_real_width();
   //float height = tile_mesh->get_real_height();

   float room_width = currently_active_map->get_tile_mesh()->get_tile_width() * 25; // tile_mesh->get_real_width();
   float room_height = currently_active_map->get_tile_mesh()->get_tile_height() * 15; //tile_mesh->get_real_height();

   // note that Shovel Knight has 4.5x4.5 sized pixels (actually 4.8 x 4.5)
      // this means:
      //     - a virtual resolution of 400x240
      //     = a native display resolution of 1920x1080 (HD)
      //     - 25 tiles x 15 tiles to fill the virtual resolution
      //     - 16x16 pixel tiles
      // see https://www.yachtclubgames.com/blog/breaking-the-nes

   camera.set_zoom(camera_baseline_zoom);
   //AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
   camera.position = {room_width/2, room_height/2};

   return;
}

void Screen::initialize()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[Screen::initialize]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::initialize: error: guard \"al_get_current_display()\" not met");
   }
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   initialize_camera_control();
   initialize_player_controls();
   initialize_camera();
   initialized = true;
   return;
}

void Screen::add_entity_to_pool(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity)
{
   entity_pool.push_back(entity);
   return;
}

void Screen::unset_player_controlled_entity_vertical_velocity()
{
   if (!player_controlled_entity) return;
   player_controlled_entity->get_velocity_ref().position.y = 0;
   return;
}

void Screen::unset_player_controlled_entity_horizontal_velocity()
{
   if (!player_controlled_entity) return;
   player_controlled_entity->get_velocity_ref().position.x = 0;
   return;
}

void Screen::set_player_controlled_entity_jump()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[Screen::set_player_controlled_entity_jump]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::set_player_controlled_entity_jump: error: guard \"player_controlled_entity\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   if (!player_controlled_entity) return;
   if (player_controlled_entity->exists(ADJACENT_TO_FLOOR))
   {
      player_controlled_entity->get_velocity_ref().position.y -= 4.25;
   }
   else if (player_controlled_entity->exists(ADJACENT_TO_LEFT_WALL))
   {
      player_controlled_entity->get_velocity_ref().position.y = -3.5;
      player_controlled_entity->get_velocity_ref().position.x = 3.0;
   }
   else if (player_controlled_entity->exists(ADJACENT_TO_RIGHT_WALL))
   {
      player_controlled_entity->get_velocity_ref().position.y = -3.5;
      player_controlled_entity->get_velocity_ref().position.x = -3.0;
   }
   return;
}

void Screen::player_emit_projectile(float magnitude)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   AllegroFlare::vec2d player_pos = player_controlled_entity->get_place_ref().position;
   //AllegroFlare::vec2d player_center_pos = player_pos;
   //AllegroFlare::vec2d aim_dir = player_controls.get_primary_stick_position(); //.normalized();
   AllegroFlare::vec2d aim_pos = player_controls.get_primary_stick_position(); //.normalized();

   if ((aim_pos.x < 0.00001) && (aim_pos.x > -0.00001))
   if ((aim_pos.y < 0.00001) && (aim_pos.y > -0.00001))
   {
      aim_pos = {1, 0};
   }


   std::string on_map_name = player_controlled_entity->get(ON_MAP_NAME);


   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory factory(bitmap_bin);
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* projectile = factory.create_player_projectile(
      on_map_name,
      player_pos.x,
      player_pos.y,
      8-1,
      8-1,
      aim_pos,
      magnitude
   );
   entity_pool.push_back(projectile);


   // HERE
   return;
}

void Screen::reverse_gravity()
{
   gravity_reversed = !gravity_reversed;
}

void Screen::update_entities()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::update_entities]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::update_entities: error: guard \"initialized\" not met");
   }
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[Screen::update_entities]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::update_entities: error: guard \"currently_active_map\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // apply gravity
   for (auto &entity : get_current_map_entities())
   {
      if (entity->exists(NOT_AFFECTED_BY_GRAVITY)) continue;
      AllegroFlare::Placement2D &velocity = entity->get_velocity_ref();
      velocity.position.y += (gravity_reversed ? -gravity : gravity);
   }

   // update the entities (typically includes movement strategies)
   for (auto &entity : get_current_map_entities())
   {
      entity->update();
   }

   // step each entity
   for (auto &entity : get_current_map_entities())
   {
      AllegroFlare::Placement2D &place = entity->get_place_ref();
      AllegroFlare::Placement2D &velocity = entity->get_velocity_ref();

      // handle case where entity does not interact with world tile mesh
      if (entity->exists(DOES_NOT_COLLIDE_WITH_WORLD))
      {
         place.position.x += velocity.position.x;
         place.position.y += velocity.position.y;
         continue;
      }

      // create a "simulated aabb2d" of the entity and run it through the collision stepper
      AllegroFlare::Physics::AABB2D aabb2d(
         place.position.x - place.size.x * place.align.x,
         place.position.y - place.size.y * place.align.y,
         place.size.x,
         place.size.y,
         velocity.position.x,
         velocity.position.y
      );
      float tile_width = 16.0f;
      float tile_height = 16.0f;
      AllegroFlare::Physics::TileMapCollisionStepper collision_stepper(
         currently_active_map->get_collision_tile_mesh(),
         &aabb2d,
         tile_width,
         tile_height
      );
      collision_stepper.step();

      // supplant our entity's position and velocity values with the "simulated aabb2d"'s values
      place.position.x = aabb2d.get_x() + place.size.x * place.align.x;
      place.position.y = aabb2d.get_y() + place.size.y * place.align.y;
      velocity.position.x = aabb2d.get_velocity_x();
      velocity.position.y = aabb2d.get_velocity_y();

      // add positioning flags
      if (collision_stepper.adjacent_to_bottom_edge(tile_width, tile_height)) entity->set(ADJACENT_TO_FLOOR);
      else entity->remove(ADJACENT_TO_FLOOR);

      if (collision_stepper.adjacent_to_top_edge(tile_width, tile_height)) entity->set(ADJACENT_TO_CEILING);
      else entity->remove(ADJACENT_TO_CEILING);

      if (collision_stepper.adjacent_to_left_edge(tile_width, tile_height)) entity->set(ADJACENT_TO_LEFT_WALL);
      else entity->remove(ADJACENT_TO_LEFT_WALL);

      if (collision_stepper.adjacent_to_right_edge(tile_width, tile_height)) entity->set(ADJACENT_TO_RIGHT_WALL);
      else entity->remove(ADJACENT_TO_RIGHT_WALL);
   }

   // update the collectables
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   if (player_controlled_entity) update_player_collisions_with_collectables();

   // update the player colliding on the goalposts
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   if (player_controlled_entity) update_player_collisions_with_goalposts();

   // update the player colliding on the doors
   //check_player_collisions_with_doors(); // this is now done by pressing 'UP' when over a door

   // delete entities flagged to be deleted
   cleanup_entities_flagged_for_deletion();

   // update camera
   if (camera_control_strategy) camera_control_strategy->update();

   return;
}

void Screen::cleanup_entities_flagged_for_deletion()
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   for (int i=0; i<entity_pool.size(); i++)
   {
      if (entity_pool[i]->exists(PLEASE_DELETE))
      {
         std::cout << "NOTICE: deleting entity." << std::endl;
         delete entity_pool[i];
         entity_pool.erase(entity_pool.begin() + i);
         i--;
      }
   }
   return;
}

void Screen::check_player_collisions_with_doors()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[Screen::check_player_collisions_with_doors]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::check_player_collisions_with_doors: error: guard \"player_controlled_entity\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Screen::check_player_collisions_with_doors]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::check_player_collisions_with_doors: error: guard \"event_emitter\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);

   float player_x = player_controlled_entity->get_place_ref().position.x;
   float player_y = player_controlled_entity->get_place_ref().position.y + 16;

   for (auto &entity : collection_helper.select_doors())
   {
      if (entity->get_place_ref().collide(player_x, player_y, 4, 4, 4, 4))
      {
         AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D *door =
            static_cast<AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D*>(entity);

         std::string game_event_name_to_emit = door->get_game_event_name_to_emit();
         bool this_door_emits_game_event = !game_event_name_to_emit.empty();
         if (this_door_emits_game_event)
         {
            event_emitter->emit_game_event(AllegroFlare::GameEvent(game_event_name_to_emit));
         }
         else // will door travel to another map or place on the current map
         {
            std::string map_target_name = door->get_target_map_name();
            float target_spawn_x = door->get_target_spawn_x();
            float target_spawn_y = door->get_target_spawn_y();

            // find the target map
            AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* target_map =
               find_map_by_name(map_target_name);

            // reposition player in map
            player_controlled_entity->set(ON_MAP_NAME, map_target_name);
            player_controlled_entity->get_place_ref().position.x = target_spawn_x;
            player_controlled_entity->get_place_ref().position.y = target_spawn_y;

            // set current map
            set_currently_active_map(map_target_name);
         }
         
         return;
      }
   }
   return;
}

void Screen::update_player_collisions_with_collectables()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[Screen::update_player_collisions_with_collectables]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::update_player_collisions_with_collectables: error: guard \"player_controlled_entity\" not met");
   }
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);
   float player_x = player_controlled_entity->get_place_ref().position.x;
   float player_y = player_controlled_entity->get_place_ref().position.y + 16;

   for (auto &entity : collection_helper.select_collectable_by_player())
   {
      if (entity->get_place_ref().collide(player_x, player_y, 4, 4, 4, 4))
      {
         entity->set(PLEASE_DELETE);
         // NOTE: typically will do something here as a result of picking up the item
      }
   }
   return;
}

void Screen::update_player_collisions_with_goalposts()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[Screen::update_player_collisions_with_goalposts]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::update_player_collisions_with_goalposts: error: guard \"player_controlled_entity\" not met");
   }
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);

   float player_x = player_controlled_entity->get_place_ref().position.x;
   float player_y = player_controlled_entity->get_place_ref().position.y + 16;

   for (auto &entity : collection_helper.select_goalposts())
   {
      if (entity->get_place_ref().collide(player_x, player_y, 8, 8, 8, 8))
      {
         // TODO: this logic requires injection of the event emitter
         //framework->shutdown_program = true;
      }
   }
   return;
}

void Screen::draw_entities()
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   for (auto &entity : get_current_map_entities())
   {
      if (!entity->exists(INVISIBLE)) entity->draw();
   }
   return;
}

void Screen::update_player_controls_on_player_controlled_entity()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[Screen::update_player_controls_on_player_controlled_entity]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::update_player_controls_on_player_controlled_entity: error: guard \"player_controlled_entity\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // if this block is active, the player cannot control themselves while in the air, only when on the ground:
   //if (player_controlled_entity->exists(ADJACENT_TO_FLOOR))
   //{
      //player_controlled_entity->get_velocity_ref().position.x = 0.0;
   //}

   if (player_controls.get_right_bumper_pressed())
   {
      player_controlled_entity->get_velocity_ref().position.x = 0.0;
   }
   else
   {
      // if this block is active, the player cannot control themselves while in the air, only when on the ground:
      if (player_controlled_entity->exists(ADJACENT_TO_FLOOR))
      {
         player_controlled_entity->get_velocity_ref().position.x = 0.0;
      }

         if (player_controls.get_right_button_pressed())
         {
            player_controlled_entity->get_velocity_ref().position.x = 1.5; //2.0;
         }
         if (player_controls.get_left_button_pressed())
         {
            player_controlled_entity->get_velocity_ref().position.x = -1.5; //-2.0;
         }
   }
   return;
}

void Screen::suspend_gameplay()
{
   if (gameplay_suspended) return;
   gameplay_suspended = true;
   return;
}

void Screen::resume_suspended_gameplay()
{
   if (!gameplay_suspended) return;
   gameplay_suspended = false;
   return;
}

void Screen::toggle_suspend_gameplay()
{
   gameplay_suspended = !gameplay_suspended;
   return;
}

void Screen::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::update: error: guard \"initialized\" not met");
   }
   if (!gameplay_suspended)
   {
      if (player_controlled_entity) update_player_controls_on_player_controlled_entity();
      update_entities();
   }
   return;
}

void Screen::draw()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::draw]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::draw: error: guard \"initialized\" not met");
   }
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[Screen::draw]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::draw: error: guard \"currently_active_map\" not met");
   }
   if (!(get_tile_mesh()))
   {
      std::stringstream error_message;
      error_message << "[Screen::draw]: error: guard \"get_tile_mesh()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::draw: error: guard \"get_tile_mesh()\" not met");
   }
   //ALLEGRO_STATE previous_target_bitmap;

   ALLEGRO_BITMAP *target_bitmap = al_get_target_bitmap();
   camera.setup_dimensional_projection(target_bitmap);

   //ALLEGRO_STATE previous_target_bitmap;
   //al_store_state(&previous_target_bitmap, ALLEGRO_STATE_TARGET_BITMAP);
   //al_set_target_bitmap(target_bitmap);
   camera.start_reverse_transform();
   //camera.start_transform();

   al_set_render_state(ALLEGRO_DEPTH_FUNCTION, ALLEGRO_RENDER_LESS_EQUAL); // less or equal allows 
                                                                           // subsequent renders at the same
                                                                           // z-level to overwrite. This 
                                                                           // mimics the rendering of typical
                                                                           // "traditional" drawing functions
   //draw_entities(); // entities are drawn before the tilemap so there is not collision with the
                      // zbuffer
   if (show_tile_mesh) get_tile_mesh()->render();
   draw_entities();
   if (show_collision_tile_mesh) render_collision_tile_mesh();

   camera.restore_transform();

   // Indicate a hint on suspended gameplay
   if (gameplay_suspended && show_visual_hint_on_suspended_gameplay)
   {
      float surface_width = al_get_bitmap_width(target_bitmap);
      float surface_height = al_get_bitmap_height(target_bitmap); //native_display_resolution_height;
      al_draw_filled_rectangle(100, 100, surface_width-100, surface_height-100, ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.2});
   }

   //al_restore_state(&previous_target_bitmap);

   return;
}

void Screen::toggle_show_collision_tile_mesh()
{
   show_collision_tile_mesh = !show_collision_tile_mesh;
   return;
}

void Screen::toggle_show_tile_mesh()
{
   show_tile_mesh = !show_tile_mesh;
   return;
}

void Screen::primary_update_func(double time_now, double delta_time)
{
   update();
   return;
}

void Screen::primary_render_func()
{
   draw();
   return;
}

void Screen::key_char_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_char_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_char_func: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_char_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_char_func: error: guard \"event\" not met");
   }
   switch (event->keyboard.keycode)
   {
   case ALLEGRO_KEY_1:
      //toggle_show_collision_tile_mesh();
      break;
   case ALLEGRO_KEY_2:
      //toggle_show_tile_mesh();
      break;
   case ALLEGRO_KEY_PAD_PLUS:
      camera.set_zoom(camera.get_zoom() + AllegroFlare::Vec2D({0.1, 0.1}));
      break;
   case ALLEGRO_KEY_PAD_MINUS:
      camera.set_zoom(camera.get_zoom() - AllegroFlare::Vec2D({0.1, 0.1}));
      break;
   default:
      break;
   }
   return;
}

void Screen::key_up_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_up_func: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_up_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_up_func: error: guard \"event\" not met");
   }
   switch (event->keyboard.keycode)
   {
      case ALLEGRO_KEY_LEFT:
         player_controls.set_left_button_pressed(false);
      break;

      case ALLEGRO_KEY_RIGHT:
         player_controls.set_right_button_pressed(false);
      break;
   }
   return;
}

void Screen::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_down_func: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[Screen::key_down_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::key_down_func: error: guard \"event\" not met");
   }
   if (!gameplay_suspended)
   {
      switch (event->keyboard.keycode)
      {
         case ALLEGRO_KEY_LEFT:
            player_controls.set_left_button_pressed(true);
         break;

         case ALLEGRO_KEY_RIGHT:
            player_controls.set_right_button_pressed(true);
         break;

         case ALLEGRO_KEY_UP:
            player_controls.set_up_button_pressed(true);
            check_player_collisions_with_doors();
         break;

         case ALLEGRO_KEY_SPACE:
            set_player_controlled_entity_jump();
         break;
      }
   }

   switch (event->keyboard.keycode) // TODO: Add boolean option to disable this "manual" toggling of pause
   {
      case ALLEGRO_KEY_P:
         toggle_suspend_gameplay();
      break;
   }
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_button_down_func: error: guard \"initialized\" not met");
   }
   //int virtual_controller_button_num = event->user.data1;

   // TODO: validate virtual controller type

   if (!gameplay_suspended)
   {
      // TODO: Investigate if there are some inputs that should be "active" at unpause (like staying crouched, 
      // continuing moving forward if paused mid-jump, etc)
      if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_B)
      {
         player_controls.set_a_button_pressed(true);
         set_player_controlled_entity_jump();
      }
      else if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_X)
      {
         reverse_gravity();
      }
      else if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_Y)
      {
         player_emit_projectile();
      }
      else if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT)
      {
         player_controls.set_right_button_pressed(true);
      }
      else if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT)
      {
         player_controls.set_left_button_pressed(true);
      }
      else if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_UP)
      {
         player_controls.set_up_button_pressed(true);
         check_player_collisions_with_doors();
      }
      else if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT_BUMPER)
      {
         // TODO: block if gameplay is suspended
         player_controls.set_right_bumper_pressed(true);
      }
   }
   return;
}

void Screen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::virtual_control_button_up_func: error: guard \"initialized\" not met");
   }
   //int virtual_controller_button_num = event->user.data1;

   // TODO: validate virtual controller type

   if (!gameplay_suspended)
   {
      // TODO: Investigate if there are some inputs that should be "active" at unpause (like staying crouched, 
      // continuing moving forward if paused mid-jump, etc)
      if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_B)
      {
         player_controls.set_a_button_pressed(false);
      }
      else if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT)
      {
         player_controls.set_right_button_pressed(false);
      }
      else if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT)
      {
         player_controls.set_left_button_pressed(false);
      }
      else if (virtual_controller_button_num == AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT_BUMPER)
      {
         player_controls.set_right_bumper_pressed(false);
      }
   }
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* event)
{
   int stick = event->user.data1;
   int axis = event->user.data2;
   float position = event->user.data3 / 255.0f;

   if (stick == AllegroFlare::VirtualControllers::GenericController::PRIMARY_STICK)
   {
      if (axis == 0)
      {
         AllegroFlare::vec2d vec = player_controls.get_primary_stick_position();
         vec.x = position;
         player_controls.set_primary_stick_position(vec);
      }
      if (axis == 1)
      {
         AllegroFlare::vec2d vec = player_controls.get_primary_stick_position();
         vec.y = position;
         player_controls.set_primary_stick_position(vec);
      }
   }

   if (axis == 0 && position > 0.5) player_controls.set_right_button_pressed(true);
   if (axis == 0 && position < 0.5 && position > -0.5)
   {
      player_controls.set_right_button_pressed(false);
      player_controls.set_left_button_pressed(false);
   }
   if (axis == 0 && position < -0.5) player_controls.set_left_button_pressed(true);

   return;
}

void Screen::user_event_func(ALLEGRO_EVENT* event)
{
   switch(event->type)
   {
      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP:
        //virtual_control_button_up_func(event);
      //break;

      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
        //virtual_control_button_down_func(event);
      //break;

      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE:
        //virtual_control_axis_change_func(event);
      //break;
   }

   return;
}

void Screen::render_collision_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[Screen::render_collision_tile_mesh]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::render_collision_tile_mesh: error: guard \"currently_active_map\" not met");
   }
   AllegroFlare::TileMaps::TileMap<int> *tile_map = currently_active_map->get_collision_tile_mesh();
   float tile_width=16.0f;
   float tile_height=16.0f;

   if (!al_is_primitives_addon_initialized()) throw std::runtime_error("render_tile_map: primitives must be init");

   for (int y=0; y<tile_map->get_num_rows(); y++)
      for (int x=0; x<tile_map->get_num_columns(); x++)
      {
         int tile_type = tile_map->get_tile(x, y);
         switch(tile_type)
         {
            case 0:
              al_draw_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 ALLEGRO_COLOR{0.2, 0.2, 0.21, 0.21}, 1.0);
            break;

            case 1:
              al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 ALLEGRO_COLOR{0.65, 0.62, 0.6, 1.0});
            break;

            default:
              al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 ALLEGRO_COLOR{0.8, 0.32, 0.4, 1.0});
            break;
         }
      }
   return;
}

AllegroFlare::TileMaps::PrimMeshAtlas* Screen::get_tile_atlas()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[Screen::get_tile_atlas]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::get_tile_atlas: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_tile_atlas();
}

AllegroFlare::TileMaps::PrimMesh* Screen::get_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[Screen::get_tile_mesh]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::get_tile_mesh: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_tile_mesh();
}

AllegroFlare::TileMaps::TileMap<int>* Screen::get_collision_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[Screen::get_collision_tile_mesh]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Screen::get_collision_tile_mesh: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_collision_tile_mesh();
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> Screen::get_current_map_entities()
{
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&entity_pool);
   std::string on_map_name = currently_active_map_name;
   return collection_helper.select_on_map(on_map_name);
}


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare



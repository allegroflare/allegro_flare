

#include <AllegroFlare/Prototypes/Platforming2D/Screen.hpp>

#include <AllegroFlare/CameraControlStrategies2D/HorizontalRail.hpp>
#include <AllegroFlare/CameraControlStrategies2D/SmoothSnap.hpp>
#include <AllegroFlare/CameraControlStrategies2D/SmoothSnapWithZoomEffect.hpp>
#include <AllegroFlare/CameraControlStrategies2D/Snap.hpp>
#include <AllegroFlare/Elements/Backgrounds/ParallaxWithZoom.hpp>
#include <AllegroFlare/Elements/ImageLayersRenderer.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Physics/AABB2D.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepperCollisionInfo.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/BossZone.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Doors/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Basic2D.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>
#include <AllegroFlare/Routers/Standard.hpp>
#include <algorithm>
#include <allegro5/allegro_color.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


Screen::Screen(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::EventEmitter* event_emitter)
   : AllegroFlare::Screens::Gameplay()
   , data_folder_path(DEFAULT_DATA_FOLDER_PATH)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , event_emitter(event_emitter)
   , tile_atlas_repository()
   , currently_active_map(nullptr)
   , currently_active_map_name("[currently-active-map-name-unset]")
   , tiled_tint_color_shader({})
   , current_boss_zone(nullptr)
   , in_boss_zone(false)
   , entity_pool({})
   , map_dictionary({})
   , gravity(0.25f)
   , gravity_reversed(false)
   , camera()
   , camera_baseline_zoom(AllegroFlare::Vec2D{4.8f, 4.5f})
   , player_controlled_entity(nullptr)
   , last_activated_save_point(nullptr)
   , show_terrain_tile_mesh(true)
   , show_background_tile_mesh(true)
   , show_foreground_tile_mesh(true)
   , show_collision_tile_map(false)
   , show_visual_hint_on_suspended_gameplay(false)
   , __entity_control_connector__deprecated(nullptr)
   , collision_stepper({})
   , camera_control_strategy(nullptr)
   , create_entities_from_map_callback({})
   , create_entities_from_map_callback_user_data(nullptr)
   , show_debugging_info(false)
   , initialized(false)
   , maps_loaded(false)
{
}


Screen::~Screen()
{
}


void Screen::set_data_folder_path(std::string data_folder_path)
{
   this->data_folder_path = data_folder_path;
}


void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_event_emitter]: error: guard \"get_initialized()\" not met.");
   this->event_emitter = event_emitter;
}


void Screen::set_entity_pool(std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> entity_pool)
{
   this->entity_pool = entity_pool;
}


void Screen::set_gravity(float gravity)
{
   this->gravity = gravity;
}


void Screen::set_camera_baseline_zoom(AllegroFlare::Vec2D camera_baseline_zoom)
{
   this->camera_baseline_zoom = camera_baseline_zoom;
}


void Screen::set_last_activated_save_point(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* last_activated_save_point)
{
   this->last_activated_save_point = last_activated_save_point;
}


void Screen::set_show_terrain_tile_mesh(bool show_terrain_tile_mesh)
{
   this->show_terrain_tile_mesh = show_terrain_tile_mesh;
}


void Screen::set_show_background_tile_mesh(bool show_background_tile_mesh)
{
   this->show_background_tile_mesh = show_background_tile_mesh;
}


void Screen::set_show_foreground_tile_mesh(bool show_foreground_tile_mesh)
{
   this->show_foreground_tile_mesh = show_foreground_tile_mesh;
}


void Screen::set_show_collision_tile_map(bool show_collision_tile_map)
{
   this->show_collision_tile_map = show_collision_tile_map;
}


void Screen::set_show_visual_hint_on_suspended_gameplay(bool show_visual_hint_on_suspended_gameplay)
{
   this->show_visual_hint_on_suspended_gameplay = show_visual_hint_on_suspended_gameplay;
}


void Screen::set___entity_control_connector__deprecated(AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base* __entity_control_connector__deprecated)
{
   this->__entity_control_connector__deprecated = __entity_control_connector__deprecated;
}


void Screen::set_create_entities_from_map_callback(std::function<void( std::string, float, float, float, float, int, std::string, std::string, std::string, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*, void*) > create_entities_from_map_callback)
{
   this->create_entities_from_map_callback = create_entities_from_map_callback;
}


void Screen::set_create_entities_from_map_callback_user_data(void* create_entities_from_map_callback_user_data)
{
   this->create_entities_from_map_callback_user_data = create_entities_from_map_callback_user_data;
}


void Screen::set_show_debugging_info(bool show_debugging_info)
{
   this->show_debugging_info = show_debugging_info;
}


std::string Screen::get_data_folder_path() const
{
   return data_folder_path;
}


AllegroFlare::BitmapBin* Screen::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* Screen::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::EventEmitter* Screen::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* Screen::get_currently_active_map() const
{
   return currently_active_map;
}


std::string Screen::get_currently_active_map_name() const
{
   return currently_active_map_name;
}


AllegroFlare::Prototypes::Platforming2D::Entities::BossZone* Screen::get_current_boss_zone() const
{
   return current_boss_zone;
}


bool Screen::get_in_boss_zone() const
{
   return in_boss_zone;
}


std::map<std::string, AllegroFlare::Prototypes::Platforming2D::MapDictionaryListing> Screen::get_map_dictionary() const
{
   return map_dictionary;
}


float Screen::get_gravity() const
{
   return gravity;
}


AllegroFlare::Vec2D Screen::get_camera_baseline_zoom() const
{
   return camera_baseline_zoom;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Screen::get_player_controlled_entity() const
{
   return player_controlled_entity;
}


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* Screen::get_last_activated_save_point() const
{
   return last_activated_save_point;
}


bool Screen::get_show_terrain_tile_mesh() const
{
   return show_terrain_tile_mesh;
}


bool Screen::get_show_background_tile_mesh() const
{
   return show_background_tile_mesh;
}


bool Screen::get_show_foreground_tile_mesh() const
{
   return show_foreground_tile_mesh;
}


bool Screen::get_show_collision_tile_map() const
{
   return show_collision_tile_map;
}


bool Screen::get_show_visual_hint_on_suspended_gameplay() const
{
   return show_visual_hint_on_suspended_gameplay;
}


AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base* Screen::get___entity_control_connector__deprecated() const
{
   return __entity_control_connector__deprecated;
}


AllegroFlare::CameraControlStrategies2D::Base* Screen::get_camera_control_strategy() const
{
   return camera_control_strategy;
}


std::function<void( std::string, float, float, float, float, int, std::string, std::string, std::string, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>*, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory*, void*) > Screen::get_create_entities_from_map_callback() const
{
   return create_entities_from_map_callback;
}


void* Screen::get_create_entities_from_map_callback_user_data() const
{
   return create_entities_from_map_callback_user_data;
}


bool Screen::get_show_debugging_info() const
{
   return show_debugging_info;
}


bool Screen::get_initialized() const
{
   return initialized;
}


AllegroFlare::TileMaps::TileAtlasRepository &Screen::get_tile_atlas_repository_ref()
{
   return tile_atlas_repository;
}


std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> &Screen::get_entity_pool_ref()
{
   return entity_pool;
}


AllegroFlare::Camera2D &Screen::get_camera_ref()
{
   return camera;
}


AllegroFlare::Physics::TileMapCollisionStepper &Screen::get_collision_stepper_ref()
{
   return collision_stepper;
}


void Screen::clear()
{
   // TODO: Be sure to call AllegroFlare::Prototypes::Platforming2D::Screen::clear in your class's override

   // TODO: Destroy "image_layers" in maps
   // TODO: Destroy "maps"

   AllegroFlare::Logger::info_from(
      "AllegroFlare::Prototypes::Platforming2D::Screen::clear",
      "Deleting all entities in entity_pool."
   );

   for (auto &entity : entity_pool)
   {
      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::Screen::clear",
         "Destroying entity {\"tmj_object_id\": " + entity->get("tmj_object_id") + "}."
      );
      entity->destroy();
      delete entity;
   }
   entity_pool.clear();

   // Clear our caches
   currently_active_map = nullptr;
   currently_active_map_name = "[unset-currently_active_map_name]";
   if (__entity_control_connector__deprecated) delete __entity_control_connector__deprecated;
   __entity_control_connector__deprecated = nullptr;
   player_controlled_entity = nullptr;
   last_activated_save_point = nullptr;
   current_boss_zone = nullptr;
   in_boss_zone = false;

   // Empty the map dictionary
   map_dictionary.clear();
   maps_loaded = false;

   AllegroFlare::Logger::info_from(
      "AllegroFlare::Prototypes::Platforming2D::Screen::clear",
      "Clear process concluded successfully."
   );

   return;
}

void Screen::set_currently_active_map(std::string name)
{
   currently_active_map = find_map_by_name(name);
   if (!currently_active_map) throw std::runtime_error("Bruh, no map");
   currently_active_map_name = name;
   return;
}

void Screen::set_player_controlled_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, bool also_set_as_camera_tracked_object, bool also_setup_a_basic2d___entity_control_connector__deprecated)
{
   if (!((also_set_as_camera_tracked_object ? (bool)camera_control_strategy : true)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::set_player_controlled_entity]: error: guard \"(also_set_as_camera_tracked_object ? (bool)camera_control_strategy : true)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::set_player_controlled_entity]: error: guard \"(also_set_as_camera_tracked_object ? (bool)camera_control_strategy : true)\" not met");
   }
   // Consider that player_controlled_entity could be nullptr
   // Set the player controlled entity
   this->player_controlled_entity = entity;

   // Set this entity as the entity for the camera to track
   if (also_set_as_camera_tracked_object && camera_control_strategy)
   {
      if (camera_control_strategy->is_type(AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect::TYPE))
      {
         auto camera_control_strategy_as = static_cast<
            AllegroFlare::CameraControlStrategies2D::SmoothSnapWithZoomEffect*>(camera_control_strategy);
         camera_control_strategy_as->set_entity_to_follow(player_controlled_entity);
      }
      else if (
            camera_control_strategy->is_type(AllegroFlare::CameraControlStrategies2D::HorizontalRail::TYPE)
         )
      {
         auto camera_control_strategy_as = static_cast<
            AllegroFlare::CameraControlStrategies2D::HorizontalRail*>(camera_control_strategy);
         camera_control_strategy_as->set_entity_to_follow(player_controlled_entity);
      }
      else
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::Screen::set_player_controlled_entity",
            "Cannot set_entity_to_follow on unhandled camera type \"" + camera_control_strategy->get_type() + "\""
         );
      }
   }

   // Setup a control connector (for now, using a Basic2D connector)
   if (also_setup_a_basic2d___entity_control_connector__deprecated)
   {
      if (__entity_control_connector__deprecated) delete __entity_control_connector__deprecated;
      auto control_connector = new AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Basic2D();
      control_connector->set_basic_2d_entity(entity);

      __entity_control_connector__deprecated = control_connector;
   }
   return;
}

void Screen::set_camera_control_strategy(AllegroFlare::CameraControlStrategies2D::Base* camera_control_strategy)
{
   if (!((initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::set_camera_control_strategy]: error: guard \"(initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::set_camera_control_strategy]: error: guard \"(initialized)\" not met");
   }
   // NOTE: Currently, the camera control strategy can only be set after initialization. This is because
   // the initialization will automatically create a camera control strategy to use.  This is just really for
   // convenience to have an automatic camera control strategy. Proabably, there should be
   // a Platforming2DScreenFactory where different stuff can be setup.
   // NOTE: If you are using this function to set a custom camera controller, you should delete any currently
   // present one before calling this function.
   this->camera_control_strategy = camera_control_strategy;
   return;
}

AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* Screen::find_map_by_name(std::string name)
{
   if (!(maps_loaded))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::find_map_by_name]: error: guard \"maps_loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::find_map_by_name]: error: guard \"maps_loaded\" not met");
   }
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
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_activate]: error: guard \"initialized\" not met");
   }
   // nothing here
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_deactivate]: error: guard \"initialized\" not met");
   }
   // nothing here
   return;
}

void Screen::set_map_dictionary(std::map<std::string, AllegroFlare::Prototypes::Platforming2D::MapDictionaryListing> map_dictionary)
{
   this->map_dictionary = map_dictionary;
   maps_loaded = false;
   // TODO: The maps need to be loaded
   return;
}

void Screen::load_maps_in_dictionary()
{
   if (!((!maps_loaded)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::load_maps_in_dictionary]: error: guard \"(!maps_loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::load_maps_in_dictionary]: error: guard \"(!maps_loaded)\" not met");
   }
   if (!((!map_dictionary.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::load_maps_in_dictionary]: error: guard \"(!map_dictionary.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::load_maps_in_dictionary]: error: guard \"(!map_dictionary.empty())\" not met");
   }
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory factory;
   factory.set_bitmap_bin(bitmap_bin);
   factory.set_tile_atlas_repository(&tile_atlas_repository);

   // TODO: Unload the current map if any
   // TODO: Consider clearing the entity pool
   // TODO: Consider tile "room_size" may be altered for the camera. Check out "initialize_camera" to see how
   // tile_width and tile_height are used to calculate the room size.

   for (auto &map_dictionary_entry : map_dictionary)
   {
      std::string map_name = std::get<0>(map_dictionary_entry);
      //std::string map_filename = std::get<1>(map_dictionary_entry);
      AllegroFlare::Prototypes::Platforming2D::MapDictionaryListing map_dictionary_listing = 
      //std::string map_filename =
         std::get<1>(map_dictionary_entry);

      std::string map_filename = map_dictionary_listing.get_tmj_filename();
      std::string map_tile_atlas_bitmap_identifier = map_dictionary_listing.get_tile_atlas_bitmap_identifier();
      std::vector<AllegroFlare::Prototypes::Platforming2D::ParallaxLayerListing> background_layer_listings =
         map_dictionary_listing.get_background_layer_listings();

      AllegroFlare::Logger::info_from(
         "AllegroFlare::Prototypes::Platforming2D::Screen",
         "Loading map named \"" + map_name + "\" from file \"" + map_filename + "\"."
      );

      // Create the tile map, add it to the entity pool
      AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D *created_map =
         factory.create_tile_map(
            map_name,
            map_filename,
            map_tile_atlas_bitmap_identifier,
            background_layer_listings
         );
      entity_pool.push_back(created_map);

      // Parse the tmj file and load entities
      std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> map_loaded_entity_pool =
         factory.create_entities_from_map(
            map_filename,
            map_name,
            create_entities_from_map_callback,
            create_entities_from_map_callback_user_data
         );

      // Add the map-loaded entities to the entity_pool
      entity_pool.insert(entity_pool.end(), map_loaded_entity_pool.begin(), map_loaded_entity_pool.end());
   }

   // Post-process the map
   post_process_loaded_maps();

   // Validate linked doors
   //AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&entity_pool);
   //for (auto &primary_door : collection_helper.select_doors())
   //{
      //int other_door = primary_door->exists(;
      //for (auto &primary_main : collection_helper.select_doors())
      //{
      //}
   //}

   maps_loaded = true;

   return;
}

void Screen::post_process_loaded_maps(std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>* entity_pool)
{
   // TODO: Add a default behavior here in this method

   //AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&entity_pool);
   //for (auto &primary_door : collection_helper.select_doors())
   //{
      //int other_door = primary_door->exists(;
      //for (auto &primary_main : collection_helper.select_doors())
      //{
      //}
   //}
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
   //camera_control->set_entity_to_follow(player_controlled_entity);
   camera_control->initialize();

   camera_control_strategy = camera_control;
   return;
}

void Screen::initialize_camera()
{
   //camera.size = { 1920.0f, 1080.0f };
   camera.size = AllegroFlare::vec2d(1920.0f, 1080.0f);
   camera.align = AllegroFlare::vec2d(0.5, 0.5);

   //float width = tile_mesh->get_real_width();
   //float height = tile_mesh->get_real_height();

   int tile_width = 16; // TODO: Note that this tile_width could change based on the map, for now, we're going
                        // to set a standard of 16x16 as the tile size. Note that this might need to be changed
                        // when the currently_active_map is changed
   int tile_height = 16; // TODO: Note that this tile_width could change based on the map, for now, we're going
                        // to set a standard of 16x16 as the tile size. Note that this might need to be changed
                        // when the currently_active_map is changed

   //float room_width = currently_active_map->get_tile_mesh()->get_tile_width() * 25; // tile_mesh->get_real_width();
   //float room_height = currently_active_map->get_tile_mesh()->get_tile_height() * 15; //tile_mesh->get_real_height();

   float room_width = tile_width * 25;
   float room_height = tile_height * 15;

   // note that Shovel Knight has 4.5x4.5 sized pixels (actually 4.8 x 4.5)
      // this means:
      //     - a virtual resolution of 400x240
      //     = a native display resolution of 1920x1080 (HD)
      //     - 25 tiles x 15 tiles to fill the virtual resolution
      //     - 16x16 pixel tiles
      // see https://www.yachtclubgames.com/blog/breaking-the-nes

   camera.set_zoom(camera_baseline_zoom);
   //AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
   camera.position = AllegroFlare::Vec2D{room_width/2, room_height/2};

   return;
}

void Screen::initialize()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   // TODO: Consider adding event_emitter in guards
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);
   initialize_camera_control();
   initialize_camera();

   // Initialize the collision stepper
   collision_stepper.set_tile_width(16.0f);
   collision_stepper.set_tile_height(16.0f);
   collision_stepper.set_reposition_offset(
         AllegroFlare::Physics::TileMapCollisionStepper::DEFAULT_REPOSITION_OFFSET
      );

   // Setup the tile_atlas_repository
   tile_atlas_repository.set_data_path(data_folder_path);
   tile_atlas_repository.initialize();

   // Initialize the TiledTintColor shader
   tiled_tint_color_shader.initialize();


   initialized = true;
   return;
}

void Screen::add_entity_to_pool(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity)
{
   entity_pool.push_back(entity);
   return;
}

void Screen::player_emit_projectile(float magnitude)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::player_emit_projectile]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::player_emit_projectile]: error: guard \"player_controlled_entity\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   AllegroFlare::vec2d player_pos = player_controlled_entity->get_placement_ref().position;
   //AllegroFlare::vec2d player_center_pos = player_pos;
   //AllegroFlare::vec2d aim_dir = player_controls.get_primary_stick_position(); //.normalized();
   AllegroFlare::vec2d aim_pos = AllegroFlare::Vec2D{ 1.0, 0.0 }; //player_controls.get_primary_stick_position(); //.normalized();
   //AllegroFlare::vec2d aim_pos = { 1.0, 0.0 }; //player_controls.get_primary_stick_position(); //.normalized();

   if ((aim_pos.x < 0.00001) && (aim_pos.x > -0.00001))
   if ((aim_pos.y < 0.00001) && (aim_pos.y > -0.00001))
   {
      aim_pos = AllegroFlare::Vec2D{1, 0};
   }


   std::string on_map_name = player_controlled_entity->get(ON_MAP_NAME);


   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory factory(bitmap_bin);
   factory.set_init_entities_drawing_debug(true);
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


   return;
}

void Screen::reverse_gravity()
{
   gravity_reversed = !gravity_reversed;
}

void Screen::on_entity_environment_collision_step(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo>* collision_step_results)
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_entity_environment_collision_step]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_entity_environment_collision_step]: error: guard \"entity\" not met");
   }
   if (!(collision_step_results))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_entity_environment_collision_step]: error: guard \"collision_step_results\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_entity_environment_collision_step]: error: guard \"collision_step_results\" not met");
   }
   return;
}

void Screen::update_entities()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::update_entities]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::update_entities]: error: guard \"initialized\" not met");
   }
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::update_entities]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::update_entities]: error: guard \"currently_active_map\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   // Apply gravity
   for (auto &entity : get_current_map_entities())
   {
      if (entity->exists(NOT_AFFECTED_BY_GRAVITY)) continue;
      AllegroFlare::Placement2D &velocity = entity->get_velocity_ref();
      velocity.position.y += (gravity_reversed ? -gravity : gravity);
   }

   // Update the player_controlled_entity first and in isolation.
   if (player_controlled_entity) player_controlled_entity->update();

   // Update the entities (typically includes movement strategies, velocity updates based on state, etc)
   // NOTE: This stage does not include the player_controlled_character, which is udpated before the rest
   // of the entities
   for (auto &entity : get_current_map_entities())
   {
      if (entity == player_controlled_entity) continue;

      // If the entity is tracking the player_controlled_entity, update the tracking position on the entity.
      if (entity->exists(TRACKS_PLAYER_CHARACTER_XY))
      {
         if (!player_controlled_entity) // There is no player_controlled_entity to track
         {
            entity->remove("player_character_x");
            entity->remove("player_character_y");
            AllegroFlare::Logger::warn_from_once(
               "AllegroFlare::Prototypes::Platforming2D::Screen::update_entities",
               "Entity is tagged with TRACKS_PLAYER_CHARACTER_XY tag, but on refreshing the value, there is no "
                  "player_controlled_entity"
            );
         }
         else
         {
            entity->set("player_character_x", player_controlled_entity->get_placement_ref().position.x);
            entity->set("player_character_y", player_controlled_entity->get_placement_ref().position.y);
         }
      }
      entity->update();
   }

   // Update the entities against the collision tile mesh by doing collision stepping one-by-one on each entity
   AllegroFlare::Vec2D previous_place_position;
   AllegroFlare::Vec2D previous_velocity_position;
   AllegroFlare::Vec2D now_place_position;
   AllegroFlare::Vec2D now_velocity_position;

   // Set the collision stepper to use the "currently_active_map"
   collision_stepper.set_collision_tile_map(currently_active_map->get_collision_tile_map());

   // Loop through each entity that is in the current map
   for (auto &entity : get_current_map_entities())
   {
      //
      // Calculate the consequential collision values in this step
      //

      AllegroFlare::Placement2D &place = entity->get_placement_ref();
      AllegroFlare::Placement2D &velocity = entity->get_velocity_ref();

      // Handle the case where entity does not interact with world tile mesh
      // TODO: Consider scenario where does not collide, but entity still receives info about block collisions
      if (entity->exists(DOES_NOT_COLLIDE_WITH_WORLD))
      {
         // TODO: Consider updating using the whole (position += velocity) and not just x and y
         place.position.x += velocity.position.x;
         place.position.y += velocity.position.y;
         continue;
      }

      // Store the before-collision info
      previous_place_position = place.position;
      previous_velocity_position = velocity.position;

      // Create a "simulated aabb2d" of the entity and run it through the collision stepper
      float tile_width = 16.0f;
      float tile_height = 16.0f;

      AllegroFlare::Physics::AABB2D aabb2d(
         place.position.x - place.size.x * place.align.x,
         place.position.y - place.size.y * place.align.y,
         place.size.x,
         place.size.y,
         velocity.position.x,
         velocity.position.y
      );

      // Use the aabb2d for this entity
      collision_stepper.set_aabb2d(&aabb2d);

      // Perform the collision step and return the collision info
      std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo> collision_step_results =
         collision_stepper.step();

      // Collect inferences about ajacency to walls
      bool is_currently_adjacent_to_floor = collision_stepper.adjacent_to_bottom_edge(tile_width, tile_height);
      bool is_currently_adjacent_to_ceiling = collision_stepper.adjacent_to_top_edge(tile_width, tile_height);
      bool is_currently_adjacent_to_left_wall = collision_stepper.adjacent_to_left_edge(tile_width, tile_height);
      bool is_currently_adjacent_to_right_wall = collision_stepper.adjacent_to_right_edge(tile_width, tile_height);

      // Build the result positioning info related to this collision
      now_place_position.x = aabb2d.get_x() + place.size.x * place.align.x;
      now_place_position.y = aabb2d.get_y() + place.size.y * place.align.y;
      now_velocity_position.x = aabb2d.get_velocity_x();
      now_velocity_position.y = aabb2d.get_velocity_y();

      //
      // Assign the result calculations to the entity
      //

      // Set our actual entity's position and velocity values to the ones used by the "simulated aabb2d"
      place.position = now_place_position;
      velocity.position = now_velocity_position;

      // Call the collision update function on the entity
      entity->on_collision_update(
         previous_place_position,
         previous_velocity_position,
         now_place_position,
         now_velocity_position,
         &collision_step_results,
         is_currently_adjacent_to_ceiling, // TODO: Confirm these
         is_currently_adjacent_to_right_wall, // TODO: Confirm these
         is_currently_adjacent_to_floor,
         is_currently_adjacent_to_left_wall // TODO: Confirm these
      );

      // Call the screens' collision callback function on the entity
      // TODO: Consider performance implications of this callback (is it excessive, should it be called only on
      // entities that are flagged for this callback?)
      // TODO: Consider adding more arguments to this callback
      on_entity_environment_collision_step(
         entity,
         &collision_step_results
      );

      // debugging:
      bool cout_collision_debugging = false;
      if (cout_collision_debugging)
      {
         for (auto &collision_step_result : collision_step_results)
         {
            if (
                  collision_step_result.get_stopped_by_this_collision()
                  && collision_step_result.collided_block_edge_is_left_edge()
               )
            {
               std::string ORG = "\033[1;33m";
               std::string NEU = "\033[0m";

               if (now_place_position.x == previous_place_position.x)
               {
                  ORG = "";
                  NEU = "";
               }

               std::cout.precision(std::numeric_limits<float>::max_digits10);
               //std::cout.std::showpoint

               std::cout << "collided against: ["
                         << std::fixed << std::showpoint
                         << collision_step_result.get_collided_tile_coordinate().get_x() << ", "
                         << collision_step_result.get_collided_tile_coordinate().get_y() << "]" << std::endl
                         << "  - result (position_before): " << ORG << "[" << previous_place_position.x << ", "
                                                              << previous_place_position.y << "]" << NEU << std::endl
                         << "            (position_after): " << ORG << "[" << now_place_position.x << ", "
                                                              << now_place_position.y << "]" << NEU << std::endl
                         << "           (velocity_before): [" << previous_velocity_position.x << ", "
                                                              << previous_velocity_position.y << "]" << std::endl
                         << "            (velocity_after): [" << now_velocity_position.x << ", "
                                                              << now_velocity_position.y << "]" << std::endl
                         << std::endl << std::flush;
            }
         }
      }
   }

   // Evaluate entity collisions. This applies for player and non-player.
   update_entity_collisions_with_damage_zones();

   // Evaluate player collisions on collectables
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   if (player_controlled_entity) update_player_collisions_with_collectables();

   // Evaluate player collisions on the goalposts
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   if (player_controlled_entity) update_player_collisions_with_goalposts();

   // Evaluate player collisions on save_points
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   if (player_controlled_entity) update_player_collisions_with_save_points();

   // Evaluate player collisions on interactable by player
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   if (player_controlled_entity) update_player_collisions_with_interactables();

   // Evaluate player collisions on boss_zones
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   if (player_controlled_entity) update_player_collisions_with_boss_zones();

   // Evaluate player collisions on entities tagged with COLLIDES_WITH_PLAYER
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   if (player_controlled_entity) update_player_collisions_with_COLLIDES_WITH_PLAYER();

   // Evaluate damage zones on player
   //if (player_controlled_entity) update_player_collisions_with_damage_zones();

   // Delete entities flagged to be deleted
   cleanup_entities_flagged_for_deletion();

   // Update the camera
   if (!camera_control_strategy && player_controlled_entity)
   {
      camera.position.x = player_controlled_entity->x;
      camera.position.y = player_controlled_entity->y;
   }
   if (camera_control_strategy) camera_control_strategy->update();

   // Check for player death
   if (player_controlled_entity) check_and_respond_if_player_death();

   return;
}

void Screen::check_and_respond_if_player_death()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::check_and_respond_if_player_death]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::check_and_respond_if_player_death]: error: guard \"player_controlled_entity\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   if (player_controlled_entity->exists(AllegroFlare::Prototypes::Platforming2D::EntityFlagNames::DEAD))
   {
      event_emitter->emit_game_event(AllegroFlare::GameEvent("player_has_died"));
   }

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

void Screen::position_entity_bottom_most_edge(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, std::string map_name, float x, float y, float y_offset)
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::position_entity_bottom_most_edge]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::position_entity_bottom_most_edge]: error: guard \"entity\" not met");
   }
   // TODO: Test this
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   entity->set(ON_MAP_NAME, map_name);
   entity->x = x;
   entity->get_placement_ref().set_bottommost_coordinate(y-y_offset);
   return;
}

void Screen::on_enter_door(AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D* door)
{
   if (!(door))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_door]: error: guard \"door\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_door]: error: guard \"door\" not met");
   }
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_door]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_door]: error: guard \"player_controlled_entity\" not met");
   }
   if (door->get_is_locked())
   {
      // TODO: Consider emitting an event, message, or sounde effect to indicate the door is locked
      std::cout << "AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_door: "
                "info: door is locked." << std::endl;
   }
   else
   {
      reposition_player_controlled_entity_to_door_destination(door);
   }
   return;
}

void Screen::reposition_player_controlled_entity_to_door_destination(AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D* door)
{
   if (!(door))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::reposition_player_controlled_entity_to_door_destination]: error: guard \"door\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::reposition_player_controlled_entity_to_door_destination]: error: guard \"door\" not met");
   }
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::reposition_player_controlled_entity_to_door_destination]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::reposition_player_controlled_entity_to_door_destination]: error: guard \"player_controlled_entity\" not met");
   }
   std::string map_target_name = door->get_target_map_name();
   float target_spawn_x = door->get_target_spawn_x();
   float target_spawn_y = door->get_target_spawn_y();

   // find the target map
   // TODO: Is this step necessary?
   AllegroFlare::Prototypes::Platforming2D::Entities::TileMaps::Basic2D* target_map =
      find_map_by_name(map_target_name);

   // reposition player in map
   position_entity_bottom_most_edge(
         player_controlled_entity,
         map_target_name,
         target_spawn_x,
         target_spawn_y
      );

   // set current map
   set_currently_active_map(map_target_name);
   return;
}

void Screen::attempt_to_enter_currently_collided_with_door()
{
   // TODO: See how this correlates with suspended_key_state
   check_player_collisions_with_doors();
   return;
}

void Screen::check_player_collisions_with_doors()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::check_player_collisions_with_doors]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::check_player_collisions_with_doors]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::check_player_collisions_with_doors]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::check_player_collisions_with_doors]: error: guard \"event_emitter\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);
   AllegroFlare::Placement2D &player_placement = player_controlled_entity->get_placement_ref();

   //float player_x = player_controlled_entity->get_place_ref().position.x;
   //float player_y = player_controlled_entity->get_place_ref().position.y + 16;

   for (auto &entity : collection_helper.select_doors())
   {
      if (entity->get_placement_ref().collide(player_placement)) //player_x, player_y, 4, 4, 4, 4))
      {
         AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D *door =
            static_cast<AllegroFlare::Prototypes::Platforming2D::Entities::Doors::Basic2D*>(entity);

         if (door->get_is_locked())
         {
            // Cannot open this door, it's locked
            // Call the callback
            on_enter_door(door);
         }
         else
         {
            // TODO: Consider removing an emitted event as a door option. This should be included in the callback
            // if anything
            std::string game_event_name_to_emit = door->get_game_event_name_to_emit();
            bool this_door_emits_game_event = !game_event_name_to_emit.empty();
            if (this_door_emits_game_event)
            {
               event_emitter->emit_game_event(AllegroFlare::GameEvent(game_event_name_to_emit));
            }
            else
            {
               // Will door travel to another map
               on_enter_door(door);
            }
         }
         
         return;
      }
   }
   return;
}

void Screen::on_player_controlled_entity_collision_with_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_player_controlled_entity_collision_with_entity]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_player_controlled_entity_collision_with_entity]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_player_controlled_entity_collision_with_entity]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_player_controlled_entity_collision_with_entity]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::on_enter_player_controlled_entity_collision_with_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_player_controlled_entity_collision_with_entity]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_player_controlled_entity_collision_with_entity]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_player_controlled_entity_collision_with_entity]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_player_controlled_entity_collision_with_entity]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::on_exit_player_controlled_entity_collision_with_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_exit_player_controlled_entity_collision_with_entity]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_exit_player_controlled_entity_collision_with_entity]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_exit_player_controlled_entity_collision_with_entity]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_exit_player_controlled_entity_collision_with_entity]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::on_hold_player_controlled_entity_collision_with_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, float duration)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_collision_with_entity]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_collision_with_entity]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_collision_with_entity]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_collision_with_entity]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::on_hold_player_controlled_entity_non_collision_with_entity(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, float duration)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_non_collision_with_entity]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_non_collision_with_entity]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_non_collision_with_entity]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_non_collision_with_entity]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::on_player_controlled_entity_collision_with_interactable(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_player_controlled_entity_collision_with_interactable]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_player_controlled_entity_collision_with_interactable]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_player_controlled_entity_collision_with_interactable]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_player_controlled_entity_collision_with_interactable]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::on_enter_player_controlled_entity_collision_with_interactable(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_player_controlled_entity_collision_with_interactable]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_player_controlled_entity_collision_with_interactable]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_player_controlled_entity_collision_with_interactable]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_enter_player_controlled_entity_collision_with_interactable]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::on_exit_player_controlled_entity_collision_with_interactable(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_exit_player_controlled_entity_collision_with_interactable]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_exit_player_controlled_entity_collision_with_interactable]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_exit_player_controlled_entity_collision_with_interactable]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_exit_player_controlled_entity_collision_with_interactable]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::on_hold_player_controlled_entity_collision_with_interactable(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, float duration)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_collision_with_interactable]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_collision_with_interactable]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_collision_with_interactable]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_collision_with_interactable]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::on_hold_player_controlled_entity_non_collision_with_interactable(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* entity, float duration)
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_non_collision_with_interactable]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_non_collision_with_interactable]: error: guard \"player_controlled_entity\" not met");
   }
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_non_collision_with_interactable]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::on_hold_player_controlled_entity_non_collision_with_interactable]: error: guard \"entity\" not met");
   }
   return;
}

void Screen::update_player_collisions_with_COLLIDES_WITH_PLAYER()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_COLLIDES_WITH_PLAYER]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_COLLIDES_WITH_PLAYER]: error: guard \"player_controlled_entity\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);

   float player_x = player_controlled_entity->x;
   float player_y = player_controlled_entity->y;
   AllegroFlare::Placement2D &player_placement = player_controlled_entity->get_placement_ref();

   // NOTE: This technique only accounts for *one* player controled entity. If the player controlled entity is
   // swapped with another entity, or, if there are multiple player_controlled_entities, this technique will require
   // review and possibly revision.

   for (auto &entity : collection_helper.select_collides_with_player())
   {
      // TODO: Be alert that multiple collisions could cause multiple callbacks and some potentially undefined
      // result state
      //if (entity->get_place_ref().collide(&pla->get_placement_ref())); //player_x, player_y, 0, 0, 0, 0))
      if (entity->get_placement_ref().collide(player_placement)) //player_x, player_y, 0, 0, 0, 0))
      {
         entity->on_collides_with_player(player_controlled_entity);
         on_player_controlled_entity_collision_with_entity(player_controlled_entity, entity);

         if (!entity->exists(CURRENTLY_COLLIDING_WITH_PLAYER))
         {
            // Set colliding with player
            entity->set(CURRENTLY_COLLIDING_WITH_PLAYER, al_get_time());

            // On-enter collision
            entity->on_enter_collision_with_player(player_controlled_entity);
            on_enter_player_controlled_entity_collision_with_entity(player_controlled_entity, entity);
         }
         else
         {
            float duration = al_get_time() - entity->get_as_float(CURRENTLY_COLLIDING_WITH_PLAYER);

            // On-holding collision with player
            entity->on_hold_collision_with_player(player_controlled_entity, duration);
            on_hold_player_controlled_entity_collision_with_entity(player_controlled_entity, entity, duration);
         }
      }
      else // Non-collision
      {
         //entity->on_collides_with_player(player_controlled_entity);
         //on_player_controlled_entity_collision_with_entity(player_controlled_entity, entity);

         if (entity->exists(CURRENTLY_COLLIDING_WITH_PLAYER))
         {
            // Set colliding with player
            entity->remove(CURRENTLY_COLLIDING_WITH_PLAYER); //, al_get_time());

            // On-exit collision
            entity->on_exit_collision_with_player(player_controlled_entity);
            on_exit_player_controlled_entity_collision_with_entity(player_controlled_entity, entity);
         }
         else
         {
            // On-holding non collision with player

            //float duration = al_get_time() - entity->get_as_float(CURRENTLY_COLLIDING_WITH_PLAYER);

            // TODO: Find a way to store non-collision duration, which there currently isn't
            float duration = 0.0f;

            // On-holding non-collision with player
            entity->on_hold_non_collision_with_player(player_controlled_entity, duration);
            on_hold_player_controlled_entity_non_collision_with_entity(player_controlled_entity, entity, duration);
         }
      }
   }



   return;
}

void Screen::spawn_player_emitted_damage_zone(std::string map_name, float x, float y, float width, float height)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory factory(bitmap_bin);
   factory.set_init_entities_drawing_debug(true);
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* damage_zone =
         factory.create_player_emitted_damage_zone(
            map_name,
            x, //player_pos.x,
            y, //player_pos.y,
            width, //8-1,
            height //8-1
         );
   entity_pool.push_back(damage_zone);

   //std::string on_map_name = player_controlled_entity->get(ON_MAP_NAME);

   //AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory factory(bitmap_bin);
   //factory.set_init_entities_drawing_debug(true);

   return;
}

void Screen::update_player_collisions_with_collectables()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_collectables]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_collectables]: error: guard \"player_controlled_entity\" not met");
   }
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);
   AllegroFlare::Placement2D &player_placement = player_controlled_entity->get_placement_ref();
      //if (entity->get_place_ref().collide(player_placement))
   //float player_x = player_controlled_entity->get_place_ref().position.x;
   //float player_y = player_controlled_entity->get_place_ref().position.y + 16; // TODO: Replace this with
                                                                               // player center position

   for (auto &entity : collection_helper.select_collectable_by_player())
   {
      if (entity->get_placement_ref().collide(player_placement))
      //if (entity->get_place_ref().collide(player_x, player_y, 4, 4, 4, 4))
      {
         entity->set(PLEASE_DELETE);
         // NOTE: typically will do something here as a result of picking up the item
      }
   }
   return;
}

void Screen::update_entity_collisions_with_damage_zones()
{
   // TODO: Consider adding some default behavior for this method. Note that at the time of this writing, a
   // PlayerDamageZone is in JourneyOfTheCat (and is scoped in AllegroFlare). This class should probably be moved
   // into AllegroFlare and handled in an expected way. Also, consider that a damage zone might damage enemies,
   // a player, both, have some kind of black/white list. This method may not be exclusive to PlayerDamageZone

   // NOTE: Previous usage looked like:
   //using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   //std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   //AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);
   //float player_x = player_controlled_entity->get_place_ref().position.x;
   //float player_y = player_controlled_entity->get_place_ref().position.y + 16; // TODO: Replace this with
                                                                               // player center position

   //for (auto &entity : collection_helper.select_collectable_by_player())
   //{
      //if (entity->get_place_ref().collide(player_x, player_y, 4, 4, 4, 4))
      //{
         //entity->set(PLEASE_DELETE);
         //// NOTE: typically will do something here as a result of picking up the item
      //}
   //}
   return;
}

void Screen::update_player_collisions_with_save_points()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_save_points]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_save_points]: error: guard \"player_controlled_entity\" not met");
   }
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);
   AllegroFlare::Placement2D &player_placement = player_controlled_entity->get_placement_ref();
      //if (entity->get_place_ref().collide(player_placement))
   //float player_x = player_controlled_entity->get_place_ref().position.x;
   //float player_y = player_controlled_entity->get_place_ref().position.y + 16; // TODO: Replace this with
                                                                               // player center position
   //AllegroFlare::Placement2D &player_placement = player_controlled_entity->get_place_ref();

   for (auto &entity : collection_helper.select_save_points())
   {
      if (entity->get_placement_ref().collide(player_placement))
      //if (entity->get_place_ref().collide(player_x, player_y, 4, 4, 4, 4))
      {
         last_activated_save_point = entity;
         //entity->set(PLEASE_DELETE);
         // NOTE: typically will do something here as a result of picking up the item
      }
   }
   return;
}

void Screen::update_player_collisions_with_interactables()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_interactables]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_interactables]: error: guard \"player_controlled_entity\" not met");
   }
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);
   AllegroFlare::Placement2D &player_placement = player_controlled_entity->get_placement_ref();

   for (auto &entity : collection_helper.select_interactable_by_player())
   {
      if (entity->get_placement_ref().collide(player_placement)) //player_x, player_y, 0, 0, 0, 0))
      {
         //entity->on_collides_with_player(player_controlled_entity);
         on_player_controlled_entity_collision_with_interactable(player_controlled_entity, entity);

         if (!entity->exists(INTERACTABLE_CURRENTLY_COLLIDING_WITH_PLAYER))
         {
            // Set colliding with player
            entity->set(INTERACTABLE_CURRENTLY_COLLIDING_WITH_PLAYER, al_get_time());

            // On-enter collision
            //entity->on_enter_collision_with_player(player_controlled_entity);
            on_enter_player_controlled_entity_collision_with_interactable(player_controlled_entity, entity);
         }
         else
         {
            float duration = al_get_time() - entity->get_as_float(INTERACTABLE_CURRENTLY_COLLIDING_WITH_PLAYER);

            // On-holding collision with player
            //entity->on_hold_collision_with_player(player_controlled_entity, duration);
            on_hold_player_controlled_entity_collision_with_interactable(player_controlled_entity, entity, duration);
         }
      }
      else // Non-collision
      {
         //entity->on_collides_with_player(player_controlled_entity);
         //on_player_controlled_entity_collision_with_interactable(player_controlled_entity, entity);

         if (entity->exists(INTERACTABLE_CURRENTLY_COLLIDING_WITH_PLAYER))
         {
            // Set colliding with player
            entity->remove(INTERACTABLE_CURRENTLY_COLLIDING_WITH_PLAYER); //, al_get_time());

            // On-exit collision
            //entity->on_exit_collision_with_player(player_controlled_entity);
            on_exit_player_controlled_entity_collision_with_interactable(player_controlled_entity, entity);
         }
         else
         {
            // On-holding non collision with player

            //float duration = al_get_time() - entity->get_as_float(CURRENTLY_COLLIDING_WITH_PLAYER);

            // TODO: Find a way to store non-collision duration, which there currently isn't
            float duration = 0.0f;

            // On-holding non-collision with player
            //entity->on_hold_non_collision_with_player(player_controlled_entity, duration);
            on_hold_player_controlled_entity_non_collision_with_interactable(
                  player_controlled_entity,
                  entity,
                  duration
               );
         }
      }
   }
   return;
}

void Screen::on_enter_boss_zone(AllegroFlare::Prototypes::Platforming2D::Entities::BossZone* boss_zone)
{
   return;
}

void Screen::on_exit_boss_zone(AllegroFlare::Prototypes::Platforming2D::Entities::BossZone* boss_zone)
{
   return;
}

void Screen::update_player_collisions_with_boss_zones()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_boss_zones]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_boss_zones]: error: guard \"player_controlled_entity\" not met");
   }
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);
   //float player_x = player_controlled_entity->get_place_ref().position.x;
   //float player_y = player_controlled_entity->get_place_ref().position.y; // TODO: Replace this with
                                                                          // player center position

   AllegroFlare::Placement2D &player_placement = player_controlled_entity->get_placement_ref();
   //for (auto &entity : collection_helper.select_boss_zones())
   //{
      // TODO: Determine what a good default action would be here, consider "entering" and "exiting" the zone
      // as well

      //if (entity->get_place_ref().collide(player_x, player_y, 4, 4, 4, 4))
      //{
         //last_activated_save_point = entity;
         // NOTE: typically will do something here as a result of picking up the item
      //}
   //}

   AllegroFlare::Prototypes::Platforming2D::Entities::BossZone* first_collided_boss_zone = nullptr;

   for (auto &entity : collection_helper.select_boss_zones())
   {
      if (entity->get_placement_ref().collide(player_placement)) // Consider an alternative to this collision
      //if (entity->get_place_ref().collide(player_x, player_y)) // Consider an alternative to this collision
      {
         first_collided_boss_zone =
               static_cast<AllegroFlare::Prototypes::Platforming2D::Entities::BossZone*>(entity);
         break;
      }
   }

   if (first_collided_boss_zone != current_boss_zone) // There was a change to the boss_zone
   {
      // TODO: Consider *exiting* current_boss_zone (if it is not a nullptr)

      if (current_boss_zone != nullptr) on_exit_boss_zone(current_boss_zone);
      current_boss_zone = first_collided_boss_zone;

      if (current_boss_zone == nullptr)
      {
         in_boss_zone = false;
         //on_enter_boss_zone();
         // Exited a boss mode
      }
      else // (current_boss_zone != nullptr)
      {
         on_enter_boss_zone(current_boss_zone);
         in_boss_zone = true;
         // Entered a boss mode
      }
   }


   return;
}

void Screen::update_player_collisions_with_goalposts()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_goalposts]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::update_player_collisions_with_goalposts]: error: guard \"player_controlled_entity\" not met");
   }
   // TODO: allow this function to run without being coupled with a "player_controlled_entity"
   std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&_entities);

   AllegroFlare::Placement2D &player_placement = player_controlled_entity->get_placement_ref();
   // TODO: Change this collision to the player_controlled_entity's center, OR, make it configurable
   //float player_x = player_controlled_entity->get_place_ref().position.x;
   //float player_y = player_controlled_entity->get_place_ref().position.y + 16; // TODO: Replace this with
                                                                               // player center position

   for (auto &entity : collection_helper.select_goalposts())
   {
      if (entity->get_placement_ref().collide(player_placement))
      //if (entity->get_place_ref().collide(player_x, player_y, 8, 8, 8, 8))
      {
         // TODO: Consider what default behavior would be good here
      }
   }
   return;
}

void Screen::draw_entities_sorted_by_render_order()
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   //std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> _entities = get_current_map_entities();

   // Build list sorted by render order
   std::multimap<std::pair<int, float>, AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*>
      entities_in_render_order;

   for (auto &entity : get_current_map_entities())
   {
      if (entity->exists(INVISIBLE)) continue;

      std::pair<int, float> key = std::make_pair(entity->get_render_order_group(), entity->get_render_order_z());
      entities_in_render_order.insert(std::make_pair(key, entity));
   }

   // Draw the entities in render order
   for (auto &entity : entities_in_render_order) entity.second->draw();

   return;
}

void Screen::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::update]: error: guard \"initialized\" not met");
   }
   if (!get_gameplay_suspended())
   {
      //if (player_controlled_entity)
      //{
         //update_player_controls_on_player_controlled_entity();
      //}
      if (player_controlled_entity && __entity_control_connector__deprecated)
      {
         __entity_control_connector__deprecated->update_player_controls_on_player_controlled_entity();
      }
      update_entities();
   }
   return;
}

void Screen::draw_hud()
{
   return;
}

void Screen::draw__before_background_tile_mesh_render_func()
{
   // shader = currently_active_map->get_shader_for_background_tile_mesh();
   // shader->set_darkness(0.2);
   return;
}

void Screen::draw__before_terrain_tile_mesh_render_func()
{
   // shader = currently_active_map->get_shader_for_background_tile_mesh();
   // shader->set_darkness(0.2);
   return;
}

void Screen::draw__before_foreground_tile_mesh_render_func()
{
   // shader = currently_active_map->get_shader_for_background_tile_mesh();
   // shader->set_darkness(0.2);
   return;
}

void Screen::draw()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::draw]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::draw]: error: guard \"initialized\" not met");
   }
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::draw]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::draw]: error: guard \"currently_active_map\" not met");
   }
   if (!(get_terrain_tile_mesh()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::draw]: error: guard \"get_terrain_tile_mesh()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::draw]: error: guard \"get_terrain_tile_mesh()\" not met");
   }
   ALLEGRO_BITMAP *target_bitmap = al_get_target_bitmap();
   camera.setup_dimensional_projection(target_bitmap);




   // Clear to the background color of the map
   // TODO: See if this is redundant and/or if clearing already occours in the framework and should be disabled
   al_clear_to_color(currently_active_map->get_background_color());


   al_set_render_state(ALLEGRO_DEPTH_FUNCTION, ALLEGRO_RENDER_LESS_EQUAL); // less or equal allows 
                                                                           // subsequent renders at the same
                                                                           // z-level to overwrite. This 
                                                                           // mimics the rendering of typical
                                                                           // "traditional" graphics drawing


   // Draw the background (parallax)
   // Note that this background is drawn before the camera sets the projection to render the rest of the scene, as
   // such, this background rendering uses the camera different from the rest of the rendering below.
   AllegroFlare::Elements::Backgrounds::ParallaxWithZoom parallax_with_zoom_background;
   parallax_with_zoom_background.set_layers(currently_active_map->get_background_layers());
   parallax_with_zoom_background.set_camera(&camera);
   parallax_with_zoom_background.render();




   // Setup the camera in order
   camera.start_reverse_transform();


   // TODO: Render image_layers
   AllegroFlare::Elements::ImageLayersRenderer image_layers_renderer;
   image_layers_renderer.set_image_layers(&currently_active_map->get_image_layers_ref());
   image_layers_renderer.set_camera(&camera);
   image_layers_renderer.set_tiled_tint_color_shader(&tiled_tint_color_shader);
   image_layers_renderer.render();



   if (show_background_tile_mesh && background_tile_mesh_exists())
   {
      draw__before_background_tile_mesh_render_func();
      if (currently_active_map->get_shader_for_background_tile_mesh())
      {
         currently_active_map->get_shader_for_background_tile_mesh()->activate();
      }
      get_background_tile_mesh()->render();
      if (currently_active_map->get_shader_for_background_tile_mesh())
      {
         currently_active_map->get_shader_for_background_tile_mesh()->deactivate();
      }
   }


   // Draw the terrain_tile_mesh
   if (show_terrain_tile_mesh)
   {
      draw__before_terrain_tile_mesh_render_func();
      if (currently_active_map->get_shader_for_terrain_tile_mesh())
      {
         currently_active_map->get_shader_for_terrain_tile_mesh()->activate();
      }
      get_terrain_tile_mesh()->render();
      if (currently_active_map->get_shader_for_terrain_tile_mesh())
      {
         currently_active_map->get_shader_for_terrain_tile_mesh()->deactivate();
      }
   }


   // Draw entities
   // TODO: Figure out how to include tile mesh with entities, including "draw_order_z" and "draw_order_group"
   draw_entities_sorted_by_render_order();


   // Draw the foreground_tile_mesh
   if (show_foreground_tile_mesh && foreground_tile_mesh_exists())
   {
      draw__before_foreground_tile_mesh_render_func();
      if (currently_active_map->get_shader_for_foreground_tile_mesh())
      {
         currently_active_map->get_shader_for_foreground_tile_mesh()->activate();
      }
      get_foreground_tile_mesh()->render();
      if (currently_active_map->get_shader_for_foreground_tile_mesh())
      {
         currently_active_map->get_shader_for_foreground_tile_mesh()->deactivate();
      }
   }


   // Show the collision_tile_map
   if (show_collision_tile_map) render_collision_tile_map();


   // Restore the camera
   camera.restore_transform();


   // Indicate a suspended gameplay hint
   if (get_gameplay_suspended() && show_visual_hint_on_suspended_gameplay)
   {
      float surface_width = al_get_bitmap_width(target_bitmap);
      float surface_height = al_get_bitmap_height(target_bitmap); //native_display_resolution_height;
      al_draw_filled_rectangle(100, 100, surface_width-100, surface_height-100, ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.2});
   }


   return;
}

void Screen::draw_debugging()
{
   //bool draw_debugging_info = true;
   if (show_debugging_info)
   {
      ALLEGRO_FONT *font = obtain_debug_font();

      float lh = 40; // "lh" is line height
      float l=0;
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "physics");
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "  reposition_offset: %f", 
            collision_stepper.get_reposition_offset()
         );
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "player_character");
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "  position_x: %f", 
            player_controlled_entity->get_placement_ref().position.x
         );
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "  position_y: %f", 
            player_controlled_entity->get_placement_ref().position.y
         );
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "  bottom_most_edge: %f", 
            player_controlled_entity->get_placement_ref().get_bottommost_coordinate()
         );
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "  velocity_x: %f", 
            player_controlled_entity->get_velocity_ref().position.x
         );
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "  velocity_y: %f", 
         player_controlled_entity->get_velocity_ref().position.y
         );
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "  flags:");
      for (auto &attribute : player_controlled_entity->Attributes::get_copy())
      {
         al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, 20, 30 + lh*l++, ALLEGRO_ALIGN_LEFT, "    - %s", 
               attribute.first.c_str()
            );
      }
   }

   return;
}

void Screen::toggle_show_collision_tile_map()
{
   show_collision_tile_map = !show_collision_tile_map;
   return;
}

void Screen::toggle_show_terrain_tile_mesh()
{
   show_terrain_tile_mesh = !show_terrain_tile_mesh;
   return;
}

void Screen::primary_update_func(double time_now, double delta_time)
{
   AllegroFlare::Screens::Gameplay::primary_update_func(time_now, delta_time);
   // TODO: Consider if there is a more elegant way to prevent logic from being performed than inferring against
   // currently_active_map. Consider a "unloaded" state or flag possibly.
   // TODO: Test this logic
   if (!currently_active_map)
   {
      AllegroFlare::Logger::warn_from_once(
         "AllegroFlare::Prototypes::Platforming2D::Screen::primary_update_func",
         "There is no currently_active_map. Skipping update methods."
      );
   }
   else
   {
      update();
   }
   return;
}

void Screen::primary_render_func()
{
   // TODO: Consider if there is a more elegant way to prevent logic from being performed than inferring against
   // currently_active_map. Consider a "unloaded" state or flag possibly.
   // TODO: Test this logic
   if (!currently_active_map)
   {
      AllegroFlare::Logger::warn_from_once(
         "AllegroFlare::Prototypes::Platforming2D::Screen::primary_render_func",
         "There is no currently_active_map. Skipping drawing methods."
      );
   }
   else
   {
      draw();
      draw_hud();
      draw_debugging();
   }
   return;
}

void Screen::key_char_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::key_char_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::key_char_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::key_char_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::key_char_func]: error: guard \"event\" not met");
   }
   AllegroFlare::Screens::Gameplay::key_char_func(event);

   switch (event->keyboard.keycode)
   {
   case ALLEGRO_KEY_1:
      toggle_show_collision_tile_map();
      break;
   case ALLEGRO_KEY_2:
      //toggle_show_tile_mesh();
      break;
   case ALLEGRO_KEY_PAD_PLUS:
      camera.set_zoom(camera.get_zoom() + AllegroFlare::Vec2D(0.1, 0.1));
      break;
   case ALLEGRO_KEY_PAD_MINUS:
      camera.set_zoom(camera.get_zoom() - AllegroFlare::Vec2D(0.1, 0.1));
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
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::key_up_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::key_up_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::key_up_func]: error: guard \"event\" not met");
   }
   AllegroFlare::Screens::Gameplay::key_up_func(event);

   if (__entity_control_connector__deprecated) __entity_control_connector__deprecated->key_up_func(event);

   switch (event->keyboard.keycode)
   {
      //case ALLEGRO_KEY_LEFT:
         ////player_control_velocity.y = 0.0;
         //player_controls.set_left_button_pressed(false);
      //break;

      //case ALLEGRO_KEY_RIGHT:
         ////player_control_velocity.y = 0.0;
         //player_controls.set_right_button_pressed(false);
      //break;
   }
   return;
}

void Screen::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::key_down_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::key_down_func]: error: guard \"event\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::key_down_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::key_down_func]: error: guard \"event_emitter\" not met");
   }
   AllegroFlare::Screens::Gameplay::key_down_func(event);

   if (!get_gameplay_suspended())
   {
      if (__entity_control_connector__deprecated) __entity_control_connector__deprecated->key_down_func(event);

      switch (event->keyboard.keycode)
      {
         //case ALLEGRO_KEY_LEFT:
            ////player_control_velocity.x = 0.0;
            //player_controls.set_left_button_pressed(true);
         //break;

         //case ALLEGRO_KEY_RIGHT:
            ////player_control_velocity.x = 1.0;
           //player_controls.set_right_button_pressed(true);
         //break;

         case ALLEGRO_KEY_UP:
            //player_control_velocity.y = -1.0;
            //player_controls.set_up_button_pressed(true);
            //check_player_collisions_with_doors(); // TODO: See how this correlates with suspended_key_state
         break;

         case ALLEGRO_KEY_DOWN:
            //player_control_velocity.y = 1.0;
         break;

         case ALLEGRO_KEY_SPACE:
            //set_player_controlled_entity_jump();
         break;

         case ALLEGRO_KEY_X:
            reverse_gravity();
         break;

         case ALLEGRO_KEY_Y:
            player_emit_projectile();
            //reverse_gravity();
         break;

         case ALLEGRO_KEY_ESCAPE:
            // TODO: Consider moving route events to separate file (so this class does not need to include the)
            // entire router.
            //attempt_to_pause_game();
            //event_emitter->emit_router_event(AllegroFlare::Routers::Standard::EVENT_PAUSE_GAME);
         break;
      }
   }

   //switch (event->keyboard.keycode) // TODO: Add boolean option to disable this "manual" toggling of pause
   //{
      //case ALLEGRO_KEY_P:
         //toggle_suspend_gameplay();
      //break;
   //}
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

void Screen::render_collision_tile_map()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::render_collision_tile_map]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::render_collision_tile_map]: error: guard \"currently_active_map\" not met");
   }
   AllegroFlare::TileMaps::TileMap<int> *tile_map = currently_active_map->get_collision_tile_map();
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
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::get_tile_atlas]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::get_tile_atlas]: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_tile_atlas();
}

AllegroFlare::TileMaps::TileMesh* Screen::get_terrain_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::get_terrain_tile_mesh]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::get_terrain_tile_mesh]: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_terrain_tile_mesh();
}

AllegroFlare::TileMaps::TileMesh* Screen::get_background_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::get_background_tile_mesh]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::get_background_tile_mesh]: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_background_tile_mesh();
}

bool Screen::background_tile_mesh_exists()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::background_tile_mesh_exists]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::background_tile_mesh_exists]: error: guard \"currently_active_map\" not met");
   }
   return (currently_active_map->get_background_tile_mesh() != nullptr);
}

AllegroFlare::TileMaps::TileMesh* Screen::get_foreground_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::get_foreground_tile_mesh]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::get_foreground_tile_mesh]: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_foreground_tile_mesh();
}

bool Screen::foreground_tile_mesh_exists()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::foreground_tile_mesh_exists]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::foreground_tile_mesh_exists]: error: guard \"currently_active_map\" not met");
   }
   return (currently_active_map->get_foreground_tile_mesh() != nullptr);
}

AllegroFlare::TileMaps::TileMap<int>* Screen::get_collision_tile_map()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::get_collision_tile_map]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::get_collision_tile_map]: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_collision_tile_map();
}

std::vector<AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D*> Screen::get_current_map_entities()
{
   AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&entity_pool);
   std::string on_map_name = currently_active_map_name;
   return collection_helper.select_on_map(on_map_name);
}

ALLEGRO_FONT* Screen::obtain_debug_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::Platforming2D::Screen::obtain_debug_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Screen::obtain_debug_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Medium.ttf -32");
}


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare



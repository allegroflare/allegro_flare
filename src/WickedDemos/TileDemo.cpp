

#include <WickedDemos/TileDemo.hpp>

#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <Tileo/TMJMeshLoader.hpp>
#include <Wicked/CameraControlStrategies2D/HorizontalRail.hpp>
#include <Wicked/CameraControlStrategies2D/SmoothSnap.hpp>
#include <Wicked/CameraControlStrategies2D/Snap.hpp>
#include <Wicked/Entities/Basic2DFactory.hpp>
#include <Wicked/Entities/CollectionHelper.hpp>
#include <Wicked/Entities/Doors/Basic2D.hpp>
#include <Wicked/EntityFlagNames.hpp>
#include <Wicked/Physics/AABB2D.hpp>
#include <Wicked/Physics/TileMapCollisionStepper.hpp>
#include <algorithm>
#include <allegro5/allegro_color.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace WickedDemos
{


TileDemo::TileDemo(AllegroFlare::Frameworks::Full* framework, AllegroFlare::Display* display, AllegroFlare::EventEmitter* event_emitter)
   : AllegroFlare::Screens::Base("TileDemo")
   , framework(framework)
   , display(display)
   , event_emitter(event_emitter)
   , native_display_resolution_width(1920)
   , native_display_resolution_height(1080)
   , initialized(false)
   , currently_active_map(nullptr)
   , currently_active_map_name("[currently-active-map-name-unset]")
   , entities({})
   , gravity(0.25f)
   , gravity_reversed(false)
   , camera(0, 0, 1920, 1080)
   , hud_projection(0, 0, 0, 0)
   , player_controlled_entity(nullptr)
   , show_tile_mesh(true)
   , show_collision_tile_mesh(false)
   , player_controls()
   , XXvirtual_controls_processor()
   , showing_player_reticle(false)
   , player_reticle_vector()
   , bow()
   , camera_control_strategy(nullptr)
   , player_collected_items(0)
{
}


TileDemo::~TileDemo()
{
}


void TileDemo::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void TileDemo::set_entities(std::vector<Wicked::Entities::Basic2D*> entities)
{
   this->entities = entities;
}


void TileDemo::set_player_controlled_entity(Wicked::Entities::Basic2D* player_controlled_entity)
{
   this->player_controlled_entity = player_controlled_entity;
}


void TileDemo::set_show_tile_mesh(bool show_tile_mesh)
{
   this->show_tile_mesh = show_tile_mesh;
}


void TileDemo::set_show_collision_tile_mesh(bool show_collision_tile_mesh)
{
   this->show_collision_tile_mesh = show_collision_tile_mesh;
}


void TileDemo::set_showing_player_reticle(bool showing_player_reticle)
{
   this->showing_player_reticle = showing_player_reticle;
}


void TileDemo::set_player_reticle_vector(AllegroFlare::vec2d player_reticle_vector)
{
   this->player_reticle_vector = player_reticle_vector;
}


Wicked::Entities::Basic2D* TileDemo::get_player_controlled_entity() const
{
   return player_controlled_entity;
}


bool TileDemo::get_show_tile_mesh() const
{
   return show_tile_mesh;
}


bool TileDemo::get_show_collision_tile_mesh() const
{
   return show_collision_tile_mesh;
}


bool TileDemo::get_showing_player_reticle() const
{
   return showing_player_reticle;
}


AllegroFlare::vec2d TileDemo::get_player_reticle_vector() const
{
   return player_reticle_vector;
}


std::vector<Wicked::Entities::Basic2D*> &TileDemo::get_entities_ref()
{
   return entities;
}


void TileDemo::set_currently_active_map(std::string name)
{
   currently_active_map = find_map_by_name(name);
   if (!currently_active_map) throw std::runtime_error("Bruh, no map");
   currently_active_map_name = name;
   return;
}

WickedDemos::TileMaps::Basic2D* TileDemo::find_map_by_name(std::string name)
{
   Wicked::Entities::CollectionHelper collection_helper(&entities);
   WickedDemos::TileMaps::Basic2D *found_map = collection_helper.find_map_by_name(name);
   if (!found_map)
   {
      std::stringstream error_message;
      error_message << "map named \"" << name << "\" does not exist.";
      throw std::runtime_error(error_message.str());

   }

   return found_map;
}

void TileDemo::initialize_display_projection()
{
   //setup_orthographic_projection_on_backbuffer();
   setup_projection();
   return;
}

void TileDemo::initialize_maps()
{
   // load up a world
   Wicked::Entities::Basic2DFactory factory(&framework->get_bitmap_bin_ref());
   //Wicked::Entities::Basic2D *created_map = nullptr;
   Wicked::Entities::Basic2D *created_map = nullptr;

   std::map<std::string, std::string> map_dictionary_entries = {
      { "map_a", "/Users/markoates/Repos/allegro_flare/bin/data/maps/map1-0x.tmj" },
      { "map_b", "/Users/markoates/Repos/allegro_flare/bin/data/maps/map1b-0x.tmj" },
   };

   for (auto &map_dictionary_entry : map_dictionary_entries)
   {
      std::string map_name = std::get<0>(map_dictionary_entry);
      std::string map_filename = std::get<1>(map_dictionary_entry);

      created_map = factory.create_tile_map(map_filename, map_name);

      if (!created_map)
      {
         std::cout << "ERROR: Could not create map \"" << map_filename << "\"" << std::endl;
      }
      else
      {
         std::cout << "NOTE: TMJ Tile map file \"" << map_filename << "\" loaded successfully." << std::endl;
      }

      WickedDemos::TileMaps::Basic2D* __created_map =
         static_cast<WickedDemos::TileMaps::Basic2D*>(created_map); // = nullptr;

      if (!__created_map->get_tile_mesh())
      {
         std::cout << "ERROR: could not create tile mesh on \"" << map_filename << "\"" << std::endl;
      }
      else
      {
         std::cout << "NOTE: TMJ Tile loaded tile mesh \"" << map_filename << "\" loaded successfully." << std::endl;
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


      entities.push_back(created_map);
   }

   set_currently_active_map("map_a");

   return;
}

void TileDemo::initialize_hud()
{
   hud_projection.scale = {4.5, 4.5}; // note that Shovel Knight has 4.5x4.5 sized pixels (actually 4.8 x 4.5)
                                      // this means:
                                      //     - a virtual resolution of 400x240
                                      //     = a native display resolution of 1920x1080 (HD)
                                      //     - 25 tiles x 15 tiles to fill the virtual resolution
                                      //     - 16x16 pixel tiles
                                      // see https://www.yachtclubgames.com/blog/breaking-the-nes
   return;
}

void TileDemo::setup_projection()
{
   // The goal here is to setup a projection transform that behaves as if normal 2D pixels were drawn for z=0
   // (i.e. as with the normal orthographic transform set up by Allegro), but allows some perspective effects for
   // rotating widgets around the X and Y axes.

   //float w = al_get_display_width(al_get_current_display()), h = al_get_display_height(al_get_current_display());
   float w = 1920, h = 1080;
   float fov_angle = 90.0;
   float fov = tan(fov_angle * ALLEGRO_PI / 180.0 / 2.0);

   // That is the z near plane where we need to draw everything before the perspective transform so that it ends up
   // as 1:1 at pixel-coordingates.
   float z_near = w / 2 * fov;

   // If we really drew at depth of z_near, everything closer to the camera would be z-clipped.
   // This would be a problem for rotations around the x and y axis.
   // Therefore, to avoid z-clipping, we need to move everything further away from the camera before the perspective
   // transform is applied.
   // This is achieved by an additional view matrix which is composed with the perspective transform so that the view
   // transformation happens first.
   const float Z_DIST_FACTOR = 1.1; // larger number makes a deeper distance effect

   ALLEGRO_TRANSFORM perspective;
   al_identity_transform(&perspective);
   // FIXME: Does factor 2 for "far" make sense?
   al_perspective_transform(&perspective, -w / 2, -h / 2, z_near, w / 2, h / 2, z_near * Z_DIST_FACTOR * 2);

   ALLEGRO_TRANSFORM view;
   al_identity_transform(&view);
   // We make up for the perspective correction due to z-translation by scaling everything.
   al_scale_transform(&view, Z_DIST_FACTOR, Z_DIST_FACTOR);
   // Move away from the camera (and center).
   al_translate_transform_3d(&view, -w / 2 * Z_DIST_FACTOR, -h / 2 * Z_DIST_FACTOR, -z_near * Z_DIST_FACTOR);

   al_compose_transform(&view, &perspective);
   al_use_projection_transform(&view);
   return;
}

void TileDemo::initialize_camera_control()
{
   float assumed_tile_width = 16.0f;
   float assumed_tile_height = 16.0f;
   float room_width = assumed_tile_width * 25; // tile_mesh->get_real_width();
   float room_height = assumed_tile_height * 15; //tile_mesh->get_real_height();

   Wicked::CameraControlStrategies2D::SmoothSnap *camera_control =
      new Wicked::CameraControlStrategies2D::SmoothSnap(room_width, room_height);
   //Wicked::CameraControlStrategies2D::HorizontalRail *camera_control =
      //new Wicked::CameraControlStrategies2D::HorizontalRail; //(room_width, room_height);
   camera_control->set_camera(&camera);
   camera_control->set_entity_to_follow(player_controlled_entity);
   camera_control->initialize();
   camera_control_strategy = camera_control;
   return;
}

void TileDemo::initialize_player_controls()
{
   //virtual_controls_processor.set_event_emitter(event_emitter);
   //virtual_controls_processor.initialize();
   player_controls.clear();
   return;
}

void TileDemo::initialize()
{
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::initialize]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::initialize]: error: guard \"framework\" not met");
   }
   initialize_display_projection();
   initialize_maps();
   initialize_entities();
   initialize_hud();
   initialize_camera_control();
   initialize_player_controls();

   initialized = true;

   return;
}

void TileDemo::setup_orthographic_projection_on_backbuffer()
{
   // set the orthographic display projection
   // the display coordinate values used throughout the program will map to these values from here on
   // (unless the projection is modified)

   ALLEGRO_DISPLAY *al_display = display->al_display;
   float fov = tan(90 * ALLEGRO_PI / 180 / 2); 

   float left = 0;
   float top = 0;
   float right = native_display_resolution_width;
   float bottom = native_display_resolution_height;
   ALLEGRO_BITMAP *display_bitmap = al_get_backbuffer(al_display);
   ALLEGRO_TRANSFORM trans;
   al_identity_transform(&trans);
   al_orthographic_transform(
   //al_perspective_transform(
         &trans,
         left,
         top,
         -1.0f,//-100, //right/2/fov, //-100.0,
         right,
         bottom,
         1.0f //100 //2000 //100.0
      );

   ALLEGRO_STATE previous_target_bitmap_state;
   al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);

   al_set_target_bitmap(display_bitmap);
   al_use_projection_transform(&trans);

   al_restore_state(&previous_target_bitmap_state);
   return;
}

void TileDemo::setup_camera()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::setup_camera]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::setup_camera]: error: guard \"currently_active_map\" not met");
   }
   if (!(currently_active_map->get_tile_atlas()))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::setup_camera]: error: guard \"currently_active_map->get_tile_atlas()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::setup_camera]: error: guard \"currently_active_map->get_tile_atlas()\" not met");
   }
   if (!(currently_active_map->get_tile_mesh()))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::setup_camera]: error: guard \"currently_active_map->get_tile_mesh()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::setup_camera]: error: guard \"currently_active_map->get_tile_mesh()\" not met");
   }
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

   camera.scale = AllegroFlare::vec2d(1.0 / 4.8, 1.0 / 4.5);
   camera.position = {room_width/2, room_height/2};

   return;
}

void TileDemo::initialize_entities()
{
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::initialize_entities]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::initialize_entities]: error: guard \"framework\" not met");
   }
   Wicked::Entities::Basic2DFactory factory(&framework->get_bitmap_bin_ref());
   //Wicked::Entities::Basic2D* created_entity = factory.create_from_bitmap_filename(
   //   "map_a", "golden_dragon.png", "top_left");
   //created_entity->get_place_ref().size.x *= 0.5;
   //created_entity->get_place_ref().size.y *= 0.5;
   //created_entity->get_place_ref().position.x = 400/2;
   //created_entity->get_place_ref().position.y = 240/2;
   Wicked::Entities::Basic2D* created_entity = factory.create_for_aabb2d("map_a", 16-1, 32-1);
   created_entity->get_place_ref().position.x = 400/2;
   created_entity->get_place_ref().position.y = 240/2;

   set_player_controlled_entity(created_entity);
   get_current_map_entities_ref().push_back(created_entity);


   // add an "enemy"
   //Wicked::Entities::Basic2D* enemy = factory.create_enemy_move_left(400/8*7, 240/2);
   //entities.push_back(enemy);
   //Wicked::Entities::Basic2D* enemy = factory.create_tracking_enemy(
      //"map_a", player_controlled_entity, 400/8*6, 240/3*1, 16.0-1.0f, 16.0-1.0f);
   //get_current_map_entities_ref().push_back(enemy);


   for (unsigned i=0; i<6; i++)
   {
      Wicked::Entities::Basic2D* enemy = factory.create_flapping_enemy(
         "map_a",
         400/8*6,
         240/3*1,
         16.0-1.0f,
         16.0-1.0f,
         80.0f, // target elevation
         4.0f, // flap strength
         0.1f // recovery rate
      );
      get_current_map_entities_ref().push_back(enemy);
   }



   // add a collectable
   //Wicked::Entities::Basic2D* collectable = factory.create_collectable(400/8*6, 240/3*1);
   //entities.push_back(collectable);

   Wicked::Entities::Basic2D* collectable2 = factory.create_collectable("map_a", 5*16, 20*16);
   get_current_map_entities_ref().push_back(collectable2);

   //entities.push_back(factory.create_collectable(18*16, 13*16));
   get_current_map_entities_ref().push_back(factory.create_collectable("map_a", 45*16, 2*16));


   // create the goalpost
   //entities.push_back(factory.create_door(46*16, 26*16));

   // create the door
   get_current_map_entities_ref().push_back(
      factory.create_door("map_b", 4.5*16, 7*16, "map_a", 46*16, 26*16)
   );
   get_current_map_entities_ref().push_back(
      factory.create_door("map_a", 46*16, 26*16, "map_b", 4.5*16, 7*16)
   );


   return;
}

void TileDemo::unset_player_controlled_entity_vertical_velocity()
{
   if (!player_controlled_entity) return;
   player_controlled_entity->get_velocity_ref().position.y = 0;
   return;
}

void TileDemo::unset_player_controlled_entity_horizontal_velocity()
{
   if (!player_controlled_entity) return;
   player_controlled_entity->get_velocity_ref().position.x = 0;
   return;
}

void TileDemo::set_player_controlled_entity_jump()
{
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

void TileDemo::player_emit_projectile(float magnitude)
{
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


   Wicked::Entities::Basic2DFactory factory(&framework->get_bitmap_bin_ref());
   Wicked::Entities::Basic2D* projectile = factory.create_player_projectile(
      on_map_name,
      player_pos.x,
      player_pos.y,
      8-1,
      8-1,
      aim_pos,
      magnitude
   );
   get_current_map_entities_ref().push_back(projectile);


   // HERE
   return;
}

void TileDemo::reverse_gravity()
{
   gravity_reversed = !gravity_reversed;
}

void TileDemo::update_entities()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::update_entities]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::update_entities]: error: guard \"initialized\" not met");
   }
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::update_entities]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::update_entities]: error: guard \"currently_active_map\" not met");
   }
   // apply gravity
   for (auto &entity : get_current_map_entities())
   {
      if (entity->exists(NOT_AFFECTED_BY_GRAVITY)) continue;
      AllegroFlare::Placement2D &velocity = entity->get_velocity_ref();
      velocity.position.y += (gravity_reversed ? -gravity : gravity);
   }


   //std::cout << "XXXXXXXXXXX" << std::endl;
   // update the entities (typically includes movement strategies), may need to be done before applying gravity
   for (auto &entity : get_current_map_entities())
   {
      entity->update();
   }

   // weapons
   bow.update();
   //std::cout << "YYYYYYYYY" << std::endl;

   // step
   for (auto &entity : get_current_map_entities())
   {
      //continue;
      if (entity->exists(DOES_NOT_COLLIDE_WITH_WORLD))
      {
         AllegroFlare::Placement2D &place = entity->get_place_ref();
         AllegroFlare::Placement2D &velocity = entity->get_velocity_ref();
         place.position.x += velocity.position.x;
         place.position.y += velocity.position.y;
         continue;
      }

      //std::cout << "11111111111" << std::endl;

      AllegroFlare::Placement2D &place = entity->get_place_ref();
      AllegroFlare::Placement2D &velocity = entity->get_velocity_ref();
      Wicked::Physics::AABB2D aabb2d(
         place.position.x - place.size.x * place.align.x,
         place.position.y - place.size.y * place.align.y,
         place.size.x,
         place.size.y,
         velocity.position.x,
         velocity.position.y
      );
      float tile_width = 16.0f;
      float tile_height = 16.0f;
      Wicked::Physics::TileMapCollisionStepper collision_stepper(
         currently_active_map->get_collision_tile_mesh(),
         &aabb2d,
         tile_width,
         tile_height
      );

      //std::cout << "2222222222222" << std::endl;
      collision_stepper.step();
      //std::cout << "3333333333" << std::endl;

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

   //std::cout << "ZZZZZZZZZZ" << std::endl;

   // update the collectables
   update_player_collisions_with_collectables();
   //std::cout << "-------------" << std::endl;

   // update the player colliding on the goalposts
   update_player_collisions_with_goalposts();

   //std::cout << "!!!!!!!!!!!!!!" << std::endl;
   // update the player colliding on the doors
   //check_player_collisions_with_doors(); // this is now done by pressing 'UP' when over a door

   // delete entities flagged to be deleted
   delete_entities_flagged_for_deletion();

      //std::cout << "RRRRRRRRRRRRRR" << std::endl;

   // update camera
   if (camera_control_strategy) camera_control_strategy->update();

   return;
}

void TileDemo::delete_entities_flagged_for_deletion()
{
   for (int i=0; i<(int)get_current_map_entities_ref().size(); i++)
   {
      if (get_current_map_entities_ref()[i]->exists(PLEASE_DELETE))
      {
         std::cout << "NOTICE: deleting entity." << std::endl;
         delete get_current_map_entities_ref()[i];
         get_current_map_entities_ref().erase(get_current_map_entities_ref().begin() + i);
         i--;
      }
   }
   return;
}

void TileDemo::check_player_collisions_with_doors()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::check_player_collisions_with_doors]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::check_player_collisions_with_doors]: error: guard \"player_controlled_entity\" not met");
   }
   std::vector<Wicked::Entities::Basic2D*> _entities = get_current_map_entities();

   Wicked::Entities::CollectionHelper collection_helper(&_entities);
   float player_x = player_controlled_entity->get_place_ref().position.x;
   float player_y = player_controlled_entity->get_place_ref().position.y + 16;

   for (auto &entity : collection_helper.select_doors())
   {
      if (entity->get_place_ref().collide(player_x, player_y, 4, 4, 4, 4))
      {
         Wicked::Entities::Doors::Basic2D *door = static_cast<Wicked::Entities::Doors::Basic2D*>(entity);
         std::string map_target_name = door->get_target_map_name(); // do nothing with this for now
         float target_spawn_x = door->get_target_spawn_x();
         float target_spawn_y = door->get_target_spawn_y();

         // find the target map
         WickedDemos::TileMaps::Basic2D* target_map = find_map_by_name(map_target_name);

         // reposition player in map
         player_controlled_entity->set(ON_MAP_NAME, map_target_name);
         player_controlled_entity->get_place_ref().position.x = target_spawn_x;
         player_controlled_entity->get_place_ref().position.y = target_spawn_y;

         // set current map
         set_currently_active_map(map_target_name);
         
         return;
      }
   }
   return;
}

void TileDemo::update_player_collisions_with_collectables()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::update_player_collisions_with_collectables]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::update_player_collisions_with_collectables]: error: guard \"player_controlled_entity\" not met");
   }
   std::vector<Wicked::Entities::Basic2D*> _entities = get_current_map_entities();
   Wicked::Entities::CollectionHelper collection_helper(&_entities);
   float player_x = player_controlled_entity->get_place_ref().position.x;
   float player_y = player_controlled_entity->get_place_ref().position.y + 16;

   for (auto &entity : collection_helper.select_collectable_by_player())
   {
      if (entity->get_place_ref().collide(player_x, player_y, 4, 4, 4, 4))
      {
         entity->set(PLEASE_DELETE);
         player_increment_collected_items();
      }
   }
   return;
}

void TileDemo::update_player_collisions_with_goalposts()
{
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::update_player_collisions_with_goalposts]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::update_player_collisions_with_goalposts]: error: guard \"framework\" not met");
   }
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::update_player_collisions_with_goalposts]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::update_player_collisions_with_goalposts]: error: guard \"player_controlled_entity\" not met");
   }
   std::vector<Wicked::Entities::Basic2D*> _entities = get_current_map_entities();
   Wicked::Entities::CollectionHelper collection_helper(&_entities);
   float player_x = player_controlled_entity->get_place_ref().position.x;
   float player_y = player_controlled_entity->get_place_ref().position.y + 16;

   for (auto &entity : collection_helper.select_goalposts())
   {
      if (entity->get_place_ref().collide(player_x, player_y, 8, 8, 8, 8))
      {
         framework->shutdown_program = true;
      }
   }
   return;
}

void TileDemo::player_increment_collected_items()
{
   player_collected_items++;
   return;
}

void TileDemo::draw_entities()
{
   for (auto &entity : get_current_map_entities())
   {
      if (!entity->exists(INVISIBLE)) entity->draw();
   }
   return;
}

void TileDemo::draw_hud()
{
   float draw_strength = bow.get_strength_value_styled();
   float width = 20;
   float height = 3;

   ALLEGRO_COLOR back = ALLEGRO_COLOR{0, 0, 0, 1};
   ALLEGRO_COLOR front = (bow.at_max()) ? ALLEGRO_COLOR{0, 1.0, 0.6, 1} : ALLEGRO_COLOR{0, 0.6, 1.0, 1};
   al_draw_filled_rectangle(0, 0, width, height, back);
   al_draw_filled_rectangle(1, 1, 1+(width-2) * draw_strength, height-1, front);
   // currently empty
   return;
}

void TileDemo::run(std::vector<std::string> args)
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   framework.get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps");

   WickedDemos::TileDemo tile_demo(
      &framework,
      framework.get_primary_display(),
      &framework.get_event_emitter_ref()
   );
   tile_demo.initialize();

   framework.register_screen("tile_demo", &tile_demo);
   framework.activate_screen("tile_demo");

   framework.run_loop();

   return;
}

void TileDemo::update_player_controls_on_player_controlled_entity()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::update_player_controls_on_player_controlled_entity]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::update_player_controls_on_player_controlled_entity]: error: guard \"player_controlled_entity\" not met");
   }
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

void TileDemo::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::update]: error: guard \"initialized\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::update]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::update]: error: guard \"framework\" not met");
   }
   //return;
   update_player_controls_on_player_controlled_entity();
   //return;
   update_entities();
   return;
}

void TileDemo::draw_dimensional_grid(float x, float y, float z)
{
   float spacing = 16 * 4.8;
   for (int zz=-10; zz<10; zz++)
      for (int xx=-10; xx<10; xx++)
         for (int yy=-10; yy<10; yy++)
         {
            ALLEGRO_STATE previous_target_bitmap_state;
            al_store_state(&previous_target_bitmap_state, ALLEGRO_STATE_TRANSFORM);
            //al_set_target_bitmap(display_bitmap);
            //al_use_projection_transform(&trans);

            ALLEGRO_TRANSFORM trans;

            al_copy_transform(&trans, al_get_current_transform());

            //al_identity_transform(&trans);
            al_translate_transform_3d(&trans, x+xx*spacing, y+yy*spacing, z+zz*spacing);
            al_use_transform(&trans);
            al_draw_filled_rectangle(-0.5, -0.5, 0.5, 0.5, ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5});
            //al_start_transform(&trans);

            al_restore_state(&previous_target_bitmap_state);
         }

   return;
}

void TileDemo::draw()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::draw]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::draw]: error: guard \"initialized\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::draw]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::draw]: error: guard \"framework\" not met");
   }
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::draw]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::draw]: error: guard \"currently_active_map\" not met");
   }
   if (!(get_tile_mesh()))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::draw]: error: guard \"get_tile_mesh()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::draw]: error: guard \"get_tile_mesh()\" not met");
   }
   //al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
   //al_set_render_state(ALLEGRO_DEPTH_TEST, true);
   //al_clear_depth_buffer(1000);
   //al_clear_to_color(ALLEGRO_COLOR{0.16, 0.16, 0.16, 1.0f});
   al_clear_to_color(ALLEGRO_COLOR{0.02, 0.016, 0.136, 1.0f});
   //al_clear_to_color(al_color_name("aliceblue"));
   al_set_render_state(ALLEGRO_DEPTH_TEST, true);
   al_clear_depth_buffer(2000);

   camera.start_reverse_transform();

   draw_entities(); // < TODO: fix work-around where drawing entities *before* the mesh so the z buffer is not
                    // filled with the mesh first, thereby not rendering the entities
   if (show_tile_mesh)
   {
      ALLEGRO_TRANSFORM trans;
      ALLEGRO_STATE state;
      al_store_state(&state, ALLEGRO_STATE_TRANSFORM);
      al_copy_transform(&trans, al_get_current_transform());
      al_translate_transform_3d(&trans, 0, 0, -1000);
      al_use_transform(&trans);
      get_tile_mesh()->render();
      al_restore_state(&state);
   }

   float o = 0.5;
   al_set_render_state(ALLEGRO_DEPTH_TEST, true);
   al_draw_filled_rectangle(0, 0, 1920, 1080, ALLEGRO_COLOR{0.02f*o, 0.016f*o, 0.136f*o, 1.0f*o});
   al_clear_depth_buffer(2000);

   if (show_tile_mesh) get_tile_mesh()->render();
   if (show_collision_tile_mesh) render_collision_tile_mesh();
   //draw_entities();
   if (showing_player_reticle) draw_player_reticle();

   //draw_dimensional_grid((25*16*4.8)*1.5, (15*16*4.5)*1.5, 0);

   camera.restore_transform();

   hud_projection.start_transform();
   draw_hud();
   hud_projection.restore_transform();

   return;
}

void TileDemo::draw_player_reticle()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::draw_player_reticle]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::draw_player_reticle]: error: guard \"player_controlled_entity\" not met");
   }
   float radius = 48;
   AllegroFlare::vec2d player_pos = player_controlled_entity->get_place_ref().position;
   AllegroFlare::vec2d player_center_pos = player_pos;

   AllegroFlare::vec2d aim_pos = player_controls.get_primary_stick_position(); //.normalized();

   al_draw_filled_circle(player_center_pos.x, player_center_pos.y, 48, ALLEGRO_COLOR{0.0, 0.0, 0.0, 0.1});
   ALLEGRO_COLOR reticle_color = ALLEGRO_COLOR{0.02, 0.016, 0.136, 1.0f};

   al_draw_circle(
      player_center_pos.x + aim_pos.x * radius,
      player_center_pos.y + aim_pos.y * radius,
      8,
      reticle_color,
      1.0f
   );

   return;
}

void TileDemo::toggle_show_collision_tile_mesh()
{
   show_collision_tile_mesh = !show_collision_tile_mesh;
   return;
}

void TileDemo::toggle_show_tile_mesh()
{
   show_tile_mesh = !show_tile_mesh;
   return;
}

void TileDemo::primary_timer_func()
{
   //al_draw_filled_rectangle(0, 0, 200, 300, ALLEGRO_COLOR{0, 1, 1, 1});
   update();
   draw();
   //al_flip_display();
   return;
}

void TileDemo::__primary_timer_func()
{
   update();
   draw();
   return;
}

void TileDemo::key_char_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::key_char_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::key_char_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::key_char_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::key_char_func]: error: guard \"event\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::key_char_func]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::key_char_func]: error: guard \"framework\" not met");
   }
   switch (event->keyboard.keycode)
   {
   case ALLEGRO_KEY_1:
      toggle_show_collision_tile_mesh();
      break;
   case ALLEGRO_KEY_2:
      toggle_show_tile_mesh();
      break;
   default:
      break;
   }
   return;
}

void TileDemo::_joy_button_down_func(ALLEGRO_EVENT* event)
{
   //virtual_controls_processor.handle_raw_joystick_button_down_event(event);
   return;
}

void TileDemo::_joy_button_up_func(ALLEGRO_EVENT* event)
{
   //virtual_controls_processor.handle_raw_joystick_button_up_event(event);
   return;
}

void TileDemo::_joy_axis_func(ALLEGRO_EVENT* event)
{
   //virtual_controls_processor.handle_raw_joystick_axis_change_event(event);
   return;
}

void TileDemo::_key_up_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::_key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::_key_up_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::_key_up_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::_key_up_func]: error: guard \"event\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::_key_up_func]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::_key_up_func]: error: guard \"framework\" not met");
   }
   //virtual_controls_processor.handle_raw_keyboard_key_up_event(event);
   return;
}

void TileDemo::_key_down_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::_key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::_key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::_key_down_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::_key_down_func]: error: guard \"event\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::_key_down_func]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::_key_down_func]: error: guard \"framework\" not met");
   }
   if (event->keyboard.keycode == ALLEGRO_KEY_ESCAPE) { framework->shutdown_program = true; return; }

   //virtual_controls_processor.handle_raw_keyboard_key_down_event(event);
   return;
}

void TileDemo::key_up_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::key_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::key_up_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::key_up_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::key_up_func]: error: guard \"event\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::key_up_func]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::key_up_func]: error: guard \"framework\" not met");
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

void TileDemo::key_down_func(ALLEGRO_EVENT* event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::key_down_func]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::key_down_func]: error: guard \"event\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::key_down_func]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::key_down_func]: error: guard \"framework\" not met");
   }
   switch (event->keyboard.keycode)
   {
      case ALLEGRO_KEY_LEFT:
         player_controls.set_left_button_pressed(true);
      break;

      case ALLEGRO_KEY_RIGHT:
         player_controls.set_right_button_pressed(true);
      break;

      case ALLEGRO_KEY_SPACE:
         set_player_controlled_entity_jump();
      break;
   }
   return;
}

void TileDemo::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   // TODO: Validate controller type

   //std::cout << "AAAAAAAAAA" << std::endl;

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
      player_controls.set_right_bumper_pressed(true);
      set_showing_player_reticle(true);
      bow.start_draw();
   }
   return;
}

void TileDemo::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::virtual_control_button_up_func]: error: guard \"initialized\" not met");
   }
   // TODO: Validate controller type

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
      if (bow.at_max()) player_emit_projectile(15.0f);
      bow.stop_draw();
      player_controls.set_right_bumper_pressed(false);
      set_showing_player_reticle(false);
   }
   return;
}

void TileDemo::virtual_control_axis_change_func(ALLEGRO_EVENT* event)
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

void TileDemo::user_event_func(ALLEGRO_EVENT* event)
{
   switch(event->type)
   {
      // NOTE: This is now handled in Frameworks::Full

      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP:
        //virtual_control_button_up_func(event);
      //break;

      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN:
        //virtual_control_button_down_func(event);
      //break;

      // TODO: look into conflicts for this event
      //case ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE:
        //virtual_control_axis_change_func(event);
      //break;
   }

   return;
}

void TileDemo::render_collision_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::render_collision_tile_mesh]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::render_collision_tile_mesh]: error: guard \"currently_active_map\" not met");
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

AllegroFlare::TileMaps::PrimMeshAtlas* TileDemo::get_tile_atlas()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::get_tile_atlas]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::get_tile_atlas]: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_tile_atlas();
}

AllegroFlare::TileMaps::PrimMesh* TileDemo::get_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::get_tile_mesh]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::get_tile_mesh]: error: guard \"currently_active_map\" not met");
   }
   //if (!currently_active_map) throw std::runtime_error("AAAAA");
   return currently_active_map->get_tile_mesh();
}

AllegroFlare::TileMaps::TileMap<int>* TileDemo::get_collision_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::get_collision_tile_mesh]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::get_collision_tile_mesh]: error: guard \"currently_active_map\" not met");
   }
   return currently_active_map->get_collision_tile_mesh();
}

std::vector<Wicked::Entities::Basic2D*>& TileDemo::get_current_map_entities_ref()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::get_current_map_entities_ref]: error: guard \"currently_active_map\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::get_current_map_entities_ref]: error: guard \"currently_active_map\" not met");
   }
   return entities;
   //return currently_active_map->get_entities_ref();
}

std::vector<Wicked::Entities::Basic2D*> TileDemo::get_current_map_entities()
{
   if (!(player_controlled_entity))
   {
      std::stringstream error_message;
      error_message << "[WickedDemos::TileDemo::get_current_map_entities]: error: guard \"player_controlled_entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[WickedDemos::TileDemo::get_current_map_entities]: error: guard \"player_controlled_entity\" not met");
   }
   Wicked::Entities::CollectionHelper collection_helper(&get_current_map_entities_ref());
   //std::string on_map_name = player_controlled_entity->get(ON_MAP_NAME);
   std::string on_map_name = currently_active_map_name; //player_controlled_entity->get(ON_MAP_NAME);
   return collection_helper.select_on_map(on_map_name);
}


} // namespace WickedDemos



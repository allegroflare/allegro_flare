

#include <WickedDemos/TileDemo2.hpp>

#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/TileMaps/Basic2D.hpp>
#include <AllegroFlare/TileMaps/PrimMesh.hpp>
#include <AllegroFlare/TileMaps/TileMap.hpp>
#include <Tileo/TMJMeshLoader.hpp>
#include <Tileo/TileAtlasBuilder.hpp>
#include <Wicked/CameraControlStrategies2D/HorizontalRail.hpp>
#include <Wicked/CameraControlStrategies2D/SmoothSnap.hpp>
#include <Wicked/CameraControlStrategies2D/Snap.hpp>
#include <Wicked/Entities/Basic2DFactory.hpp>
#include <Wicked/Entities/CollectionHelper.hpp>
#include <cmath>
#include <sstream>
#include <stdexcept>


namespace WickedDemos
{


TileDemo2::TileDemo2(AllegroFlare::Frameworks::Full* framework, AllegroFlare::Display* display, AllegroFlare::EventEmitter* event_emitter)
   : AllegroFlare::Screens::Base("TileDemo2")
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
   , show_tile_mesh(true)
   , show_collision_tile_mesh(false)
   , player_controls()
   , virtual_controls_processor()
   , showing_player_reticle(false)
   , player_reticle_vector()
   , bow()
   , camera_control_strategy(nullptr)
   , player_collected_items(0)
{
}


TileDemo2::~TileDemo2()
{
}


void TileDemo2::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   this->event_emitter = event_emitter;
}


void TileDemo2::set_entities(std::vector<Wicked::Entities::Basic2D*> entities)
{
   this->entities = entities;
}


void TileDemo2::set_show_tile_mesh(bool show_tile_mesh)
{
   this->show_tile_mesh = show_tile_mesh;
}


void TileDemo2::set_show_collision_tile_mesh(bool show_collision_tile_mesh)
{
   this->show_collision_tile_mesh = show_collision_tile_mesh;
}


void TileDemo2::set_showing_player_reticle(bool showing_player_reticle)
{
   this->showing_player_reticle = showing_player_reticle;
}


void TileDemo2::set_player_reticle_vector(AllegroFlare::vec2d player_reticle_vector)
{
   this->player_reticle_vector = player_reticle_vector;
}


bool TileDemo2::get_show_tile_mesh() const
{
   return show_tile_mesh;
}


bool TileDemo2::get_show_collision_tile_mesh() const
{
   return show_collision_tile_mesh;
}


bool TileDemo2::get_showing_player_reticle() const
{
   return showing_player_reticle;
}


AllegroFlare::vec2d TileDemo2::get_player_reticle_vector() const
{
   return player_reticle_vector;
}


std::vector<Wicked::Entities::Basic2D*> &TileDemo2::get_entities_ref()
{
   return entities;
}


void TileDemo2::set_currently_active_map(std::string name)
{
   currently_active_map = find_map_by_name(name);
   if (!currently_active_map) throw std::runtime_error("Bruh, no map");
   currently_active_map_name = name;
   return;
}

AllegroFlare::TileMaps::Basic2D* TileDemo2::find_map_by_name(std::string name)
{
   Wicked::Entities::CollectionHelper collection_helper(&entities);
   AllegroFlare::TileMaps::Basic2D *found_map = collection_helper.find_map_by_name(name);
   if (!found_map)
   {
      std::stringstream error_message;
      error_message << "map named \"" << name << "\" does not exist.";
      throw std::runtime_error(error_message.str());
   }

   return found_map;
}

void TileDemo2::initialize_maps()
{
   // load up a world
   Wicked::Entities::Basic2DFactory factory(&framework->get_bitmap_bin_ref());
   //Wicked::Entities::Basic2D *created_map = nullptr;
   Wicked::Entities::Basic2D *created_map = nullptr;

   std::map<std::string, std::string> map_dictionary_entries = {
      { "map_a", "/Users/markoates/Repos/Wicked/bin/programs/data/maps/map1-0x.tmj" },
      { "map_b", "/Users/markoates/Repos/Wicked/bin/programs/data/maps/map1b-0x.tmj" },
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

      AllegroFlare::TileMaps::Basic2D* __created_map =
         static_cast<AllegroFlare::TileMaps::Basic2D*>(created_map); // = nullptr;

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
   return;
}

void TileDemo2::initialize_hud()
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

void TileDemo2::initialize_display_projection()
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

void TileDemo2::initialize_camera_control()
{
   float assumed_tile_width = 16.0f;
   float assumed_tile_height = 16.0f;
   float room_width = assumed_tile_width * 25; // tile_mesh->get_real_width();
   float room_height = assumed_tile_height * 15; //tile_mesh->get_real_height();

   //Wicked::CameraControlStrategies2D::SmoothSnap *camera_control =
      //new Wicked::CameraControlStrategies2D::SmoothSnap(room_width, room_height);
   Wicked::CameraControlStrategies2D::HorizontalRail *camera_control =
      new Wicked::CameraControlStrategies2D::HorizontalRail; //(room_width, room_height);
   camera_control->set_camera(&camera);
   //camera_control->set_entity_to_follow(player_controlled_entity);
   camera_control->initialize();
   camera_control_strategy = camera_control;
   return;
}

void TileDemo2::initialize()
{
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "initialize" << ": error: " << "guard \"framework\" not met";
      throw std::runtime_error(error_message.str());
   }
   initialize_display_projection();
   //initialize_maps();
   //initialize_entities();
   //initialize_hud();
   //initialize_camera_control();

   set_currently_active_map("map_x");

   initialized = true;

   return;
}

void TileDemo2::setup_orthographic_projection_on_backbuffer()
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

void TileDemo2::setup_camera()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "setup_camera" << ": error: " << "guard \"currently_active_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(currently_active_map->get_tile_atlas()))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "setup_camera" << ": error: " << "guard \"currently_active_map->get_tile_atlas()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(currently_active_map->get_tile_mesh()))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "setup_camera" << ": error: " << "guard \"currently_active_map->get_tile_mesh()\" not met";
      throw std::runtime_error(error_message.str());
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

void TileDemo2::run(std::vector<std::string> args)
{
   AllegroFlare::Frameworks::Full framework;
   //framework.disable_fullscreen();
   framework.initialize();

   framework.get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/Wicked/bin/programs/data/bitmaps");

   WickedDemos::TileDemo2 tile_demo(
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

void TileDemo2::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "update" << ": error: " << "guard \"framework\" not met";
      throw std::runtime_error(error_message.str());
   }
   //return;
   //update_player_controls_on_player_controlled_entity();
   //return;
   //update_entities();
   return;
}

void TileDemo2::draw_dimentional_grid(float x, float y, float z)
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

void TileDemo2::primary_timer_func()
{
   al_draw_filled_rectangle(0, 0, 200, 300, ALLEGRO_COLOR{0, 1, 1, 1});

   //render_collision_tile_mesh();
   draw_dimentional_grid();

   return;
}

void TileDemo2::render_collision_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "render_collision_tile_mesh" << ": error: " << "guard \"currently_active_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::TileMaps::TileMap<int> *tile_map = currently_active_map->get_collision_tile_mesh();
   float tile_width=16.0f;
   float tile_height=16.0f;

   if (!tile_map) throw std::runtime_error("FAAAAAAAAAA");

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

AllegroFlare::TileMaps::PrimMeshAtlas* TileDemo2::get_tile_atlas()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "get_tile_atlas" << ": error: " << "guard \"currently_active_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   return currently_active_map->get_tile_atlas();
}

AllegroFlare::TileMaps::PrimMesh* TileDemo2::get_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "get_tile_mesh" << ": error: " << "guard \"currently_active_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   //if (!currently_active_map) throw std::runtime_error("AAAAA");
   return currently_active_map->get_tile_mesh();
}

AllegroFlare::TileMaps::TileMap<int>* TileDemo2::get_collision_tile_mesh()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "get_collision_tile_mesh" << ": error: " << "guard \"currently_active_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   return currently_active_map->get_collision_tile_mesh();
}

std::vector<Wicked::Entities::Basic2D*>& TileDemo2::get_current_map_entities_ref()
{
   if (!(currently_active_map))
   {
      std::stringstream error_message;
      error_message << "TileDemo2" << "::" << "get_current_map_entities_ref" << ": error: " << "guard \"currently_active_map\" not met";
      throw std::runtime_error(error_message.str());
   }
   return entities;
   //return currently_active_map->get_entities_ref();
}

std::vector<Wicked::Entities::Basic2D*> TileDemo2::get_current_map_entities()
{
   Wicked::Entities::CollectionHelper collection_helper(&get_current_map_entities_ref());
   //std::string on_map_name = player_controlled_entity->get(ON_MAP_NAME);
   std::string on_map_name = currently_active_map_name; //player_controlled_entity->get(ON_MAP_NAME);
   return collection_helper.select_on_map(on_map_name);
}


} // namespace WickedDemos



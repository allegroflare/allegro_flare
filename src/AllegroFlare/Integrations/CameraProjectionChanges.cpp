

#include <AllegroFlare/Integrations/CameraProjectionChanges.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Integrations
{


CameraProjectionChanges::CameraProjectionChanges()
   : AllegroFlare::Screens::Base("Prototypes::Platforming2D::Screen")
   , framework()
   , platforming_2d_screen()
   , tile_drive_screen()
   , initialized(false)
{
}


CameraProjectionChanges::~CameraProjectionChanges()
{
}


void CameraProjectionChanges::callback(ALLEGRO_EVENT* event, void* user_data)
{
   if (!(event))
   {
      std::stringstream error_message;
      error_message << "[CameraProjectionChanges::callback]: error: guard \"event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CameraProjectionChanges::callback: error: guard \"event\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[CameraProjectionChanges::callback]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CameraProjectionChanges::callback: error: guard \"user_data\" not met");
   }
   if (event->type != ALLEGRO_EVENT_KEY_DOWN) return;
   AllegroFlare::Frameworks::Full &framework = *static_cast<AllegroFlare::Frameworks::Full*>(user_data);

   switch (event->keyboard.keycode)
   {
      case ALLEGRO_KEY_1:
         framework.activate_screen("tile_drive_screen");
      break;

      case ALLEGRO_KEY_2:
         framework.activate_screen("platforming_2d_screen");
      break;
   }
   return;
}

void CameraProjectionChanges::initialize()
{
   // TODO: improve this:
   #if defined(_WIN32) || defined(_WIN64)
   #define TEST_FIXTURES_PATH "/msys64/home/Mark/Repos/allegro_flare/bin/data/"
   #else
   #define TEST_FIXTURES_PATH "/Users/markoates/Repos/allegro_flare/bin/data/"
   #endif

   framework.disable_fullscreen();
   framework.initialize();
   // TODO: Improve the usage of a previously defined TEST_FIXTURES_PATH here:
   framework.get_bitmap_bin_ref().set_full_path(TEST_FIXTURES_PATH "bitmaps");
   framework.get_font_bin_ref().set_full_path(TEST_FIXTURES_PATH "fonts");
   framework.get_sample_bin_ref().set_full_path(TEST_FIXTURES_PATH "samples");

   initialize_platforming_2d();
   initialize_tile_drive();

   framework.register_screen("platforming_2d_screen", &platforming_2d_screen);
   framework.register_screen("tile_drive_screen", &tile_drive_screen);
   framework.register_screen("camera_projection_changes_screen", this);


   framework.register_event_callback(callback, &framework);

   initialized = true;

   return;
}

void CameraProjectionChanges::run()
{
   framework.activate_screen("platforming_2d_screen");
   //framework.activate_screen("tile_drive_screen");

   framework.run_loop();
   return;
}

void CameraProjectionChanges::initialize_tile_drive()
{
   using AllegroFlare::Prototypes::TileDrive::TerrainMeshDictionaryRecord;

   tile_drive_screen.set_bitmap_bin(&framework.get_bitmap_bin_ref());
   tile_drive_screen.set_font_bin(&framework.get_font_bin_ref());
   tile_drive_screen.set_sample_bin(&framework.get_sample_bin_ref());
   tile_drive_screen.set_event_emitter(&framework.get_event_emitter_ref());
   // TODO: Improve the usage of a previously defined TEST_FIXTURES_PATH here:
   tile_drive_screen.set_maps_folder(TEST_FIXTURES_PATH "maps/");
   tile_drive_screen.set_terrain_mesh_dictionary({
      { "og-tunnel-mesh", TerrainMeshDictionaryRecord(
         "tunnel_mesh-02.tmj",
         "uv-with-decorations-0x.png",
         50,
         50,
         nullptr)
      },
   });
   tile_drive_screen.set_current_map_identifier("og-tunnel-mesh");
   tile_drive_screen.set_collision_stepper_step_result_callback(
      AllegroFlare::Prototypes::TileDrive::TileDrive::development_play_around_with_collision_steper_callback,
      nullptr
   );
   tile_drive_screen.initialize();
   return;
}

void CameraProjectionChanges::initialize_platforming_2d()
{
   platforming_2d_screen.set_bitmap_bin(&framework.get_bitmap_bin_ref());
   //platforming_2d_screen.set_display(framework.get_primary_display());
   platforming_2d_screen.set_event_emitter(&framework.get_event_emitter_ref());
   // TODO: Improve the usage of a previously defined TEST_FIXTURES_PATH here:
   platforming_2d_screen.set_map_dictionary({
      { "map_a", { TEST_FIXTURES_PATH "maps/map1-0x.tmj", "tiles_dungeon_v1.1.png" } },
      { "map_b", { TEST_FIXTURES_PATH "maps/map1b-0x.tmj", "tiles_dungeon_v1.1.png" } },
   });
   platforming_2d_screen.load_maps_in_dictionary();
   platforming_2d_screen.set_currently_active_map("map_a");


   // create some entities

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory factory(&framework.get_bitmap_bin_ref());
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* created_entity =
      factory.create_for_aabb2d("map_a", 16-1, 32-1);
   created_entity->get_place_ref().position.x = 400/2;
   created_entity->get_place_ref().position.y = 240/2;

   platforming_2d_screen.set_player_controlled_entity(created_entity, false, false);
   platforming_2d_screen.add_entity_to_pool(created_entity);

   for (unsigned i=0; i<6; i++)
   {
      AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* enemy = factory.create_flapping_enemy(
         "map_a",
         400/8*6,
         240/3*1,
         16.0-1.0f,
         16.0-1.0f,
         80.0f, // target elevation
         4.0f, // flap strength
         0.1f // recovery rate
      );
      platforming_2d_screen.add_entity_to_pool(enemy);
   }

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* collectable2 =
      factory.create_collectable("map_a", 5*16, 20*16);
   platforming_2d_screen.add_entity_to_pool(collectable2);

   platforming_2d_screen.add_entity_to_pool(factory.create_collectable("map_a", 45*16, 2*16));

   // create the door
   platforming_2d_screen.add_entity_to_pool(
      factory.create_door("map_b", 4.5*16, 7*16, "map_a", 46*16, 26*16)
   );
   platforming_2d_screen.add_entity_to_pool(
      factory.create_door("map_a", 46*16, 26*16, "map_b", 4.5*16, 7*16)
   );


   platforming_2d_screen.set_data_folder_path(TEST_FIXTURES_PATH);

   platforming_2d_screen.initialize();

   return;
}


} // namespace Integrations
} // namespace AllegroFlare



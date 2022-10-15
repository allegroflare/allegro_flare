

#include <AllegroFlare/Integrations/CameraProjectionChanges.hpp>




namespace AllegroFlare
{
namespace Integrations
{


CameraProjectionChanges::CameraProjectionChanges()
   : framework()
   , platforming_2d_screen()
   , tile_drive_screen()
{
}


CameraProjectionChanges::~CameraProjectionChanges()
{
}


void CameraProjectionChanges::initialize()
{
   framework.disable_fullscreen();
   framework.initialize();
   framework.get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps");

   initialize_platforming_2d();
   initialize_tile_drive();

   framework.register_screen("platforming_2d_screen", &platforming_2d_screen);
   framework.register_screen("tile_drive_screen", &tile_drive_screen);

   return;
}

void CameraProjectionChanges::initialize_tile_drive()
{
   tile_drive_screen.set_bitmap_bin(&framework.get_bitmap_bin_ref());
   tile_drive_screen.set_font_bin(&framework.get_font_bin_ref());
   tile_drive_screen.set_sample_bin(&framework.get_sample_bin_ref());
   tile_drive_screen.set_event_emitter(&framework.get_event_emitter_ref());
   tile_drive_screen.set_maps_folder("/Users/markoates/Repos/allegro_flare/bin/data/maps/");
   tile_drive_screen.set_terrain_mesh_dictionary({
      { "og-tunnel-mesh", { "tunnel_mesh-02.tmj", nullptr } },
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
   platforming_2d_screen.set_display(framework.get_primary_display());
   platforming_2d_screen.set_event_emitter(&framework.get_event_emitter_ref());
   platforming_2d_screen.set_map_dictionary({
      { "map_a", "/Users/markoates/Repos/allegro_flare/bin/data/maps/map1-0x.tmj" },
      { "map_b", "/Users/markoates/Repos/allegro_flare/bin/data/maps/map1b-0x.tmj" },
   });
   platforming_2d_screen.initialize_maps();
   platforming_2d_screen.set_currently_active_map("map_a");
   return;
}


} // namespace Integrations
} // namespace AllegroFlare



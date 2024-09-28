
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/TileDrive/Screen.hpp>

#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <AllegroFlare/Frameworks/Full.hpp>


TEST(AllegroFlare_Prototypes_TileDrive_ScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::TileDrive::Screen screen;
}


TEST(AllegroFlare_Prototypes_TileDrive_ScreenTest, DISABLED__initialize__does_not_blow_up)
   // TODO: finish this test
{
   al_init();
   al_install_keyboard();
   al_install_joystick();
   al_install_audio();
   al_init_acodec_addon();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   al_reserve_samples(8);

   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::BitmapBin bitmap_bin;
   AllegroFlare::FontBin font_bin;
   AllegroFlare::SampleBin sample_bin;

   sample_bin.set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/samples/");
   bitmap_bin.set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/");
   font_bin.set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/fonts/");

   AllegroFlare::Prototypes::TileDrive::Screen screen;
   screen.set_bitmap_bin(&bitmap_bin);
   screen.set_font_bin(&font_bin);
   screen.set_sample_bin(&sample_bin);
   screen.set_event_emitter(&event_emitter);
   screen.initialize();

   al_destroy_display(display);

   al_uninstall_audio();
   al_uninstall_system();
}


TEST(AllegroFlare_Prototypes_TileDrive_ScreenTest,
   //INTERACTIVE__will_run_in_AllegroFlare_Frameworks_Full_context)
   DISABLED__INTERACTIVE__will_run_in_AllegroFlare_Frameworks_Full_context)
{
   // TODO: Make this a TIMED_INTERACTIVE test
   using AllegroFlare::Prototypes::TileDrive::TerrainMeshDictionaryRecord;

   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   framework.get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps");
   framework.get_font_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/fonts");
   framework.get_sample_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/samples");

   AllegroFlare::Prototypes::TileDrive::Screen tile_drive_screen;
   tile_drive_screen.set_bitmap_bin(&framework.get_bitmap_bin_ref());
   tile_drive_screen.set_font_bin(&framework.get_font_bin_ref());
   tile_drive_screen.set_sample_bin(&framework.get_sample_bin_ref());
   tile_drive_screen.set_event_emitter(&framework.get_event_emitter_ref());
   tile_drive_screen.set_maps_folder("/Users/markoates/Repos/allegro_flare/bin/data/maps/");
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
      nullptr // might typically be the caller, an event_emitter, or something similar to be consumed by the callback
   );

   tile_drive_screen.initialize();

   framework.register_screen("tile_drive_screen", &tile_drive_screen);
   framework.activate_screen("tile_drive_screen");

   framework.run_loop();
}



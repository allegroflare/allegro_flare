#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


#if defined(_WIN32) || defined(_WIN64)
#define TEST_FIXTURES_PATH "/msys64/home/Mark/Repos/allegro_flare/bin/data/"
#else
#define TEST_FIXTURES_PATH "/Users/markoates/Repos/allegro_flare/bin/data/"
#endif


class AllegroFlare_Prototypes_TileDrive_TileDriveTest : public ::testing::Test {};
class AllegroFlare_Prototypes_TileDrive_TileDriveTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/TileDrive/TileDrive.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <AllegroFlare/EventEmitter.hpp>
#include <allegro5/allegro_acodec.h>


TEST_F(AllegroFlare_Prototypes_TileDrive_TileDriveTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::TileDrive::TileDrive tile_drive;
}


TEST_F(AllegroFlare_Prototypes_TileDrive_TileDriveTestWithAllegroRenderingFixture,
   CAPTURE__basic_update_and_render_will_work_as_expected)
{
   using AllegroFlare::Prototypes::TileDrive::TerrainMeshDictionaryRecord;

   al_install_audio();
   al_reserve_samples(8);
   al_init_acodec_addon();
   AllegroFlare::SampleBin sample_bin;
   sample_bin.set_full_path(TEST_FIXTURES_PATH "samples/");
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::Prototypes::TileDrive::TileDrive tile_drive(
      &event_emitter,
      &get_bitmap_bin_ref(),
      &get_font_bin_ref(),
      &sample_bin
   );
   tile_drive.set_maps_folder(TEST_FIXTURES_PATH "maps/");
   tile_drive.set_terrain_mesh_dictionary({
      { "og-tunnel-mesh", TerrainMeshDictionaryRecord(
         "tunnel_mesh-02.tmj",
         "uv-with-decorations-0x.png",
         50,
         50,
         nullptr)
      },
   });
   tile_drive.set_current_map_identifier("og-tunnel-mesh");
   tile_drive.initialize();

   // start the level
   tile_drive.reset();

   clear();

   tile_drive.update();
   tile_drive.render();

   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_Prototypes_TileDrive_TileDriveTestWithAllegroRenderingFixture,
   INTERACTIVE__will_work_as_expected)
   //DISABLED__INTERACTIVE__will_work_as_expected)
{
   // TODO: Make this a timed interactive
   using AllegroFlare::Prototypes::TileDrive::TerrainMeshDictionaryRecord;

   // setup system
   al_install_keyboard();
   al_install_joystick();
   al_install_audio();
   al_reserve_samples(8);
   al_init_acodec_addon();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   //al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   bool abort = false;
   ALLEGRO_EVENT event;

   // setup environment
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   AllegroFlare::SampleBin sample_bin;
   sample_bin.set_full_path(TEST_FIXTURES_PATH "samples/");
   //sample_bin.initialize();

   // initialize test subject
   
   AllegroFlare::Prototypes::TileDrive::TileDrive tile_drive;
   tile_drive.set_bitmap_bin(&get_bitmap_bin_ref());
   tile_drive.set_font_bin(&get_font_bin_ref());
   tile_drive.set_event_emitter(&event_emitter);
   tile_drive.set_sample_bin(&sample_bin);
   tile_drive.set_maps_folder(TEST_FIXTURES_PATH "maps/");
   tile_drive.get_parallax_background_ref().set_layers({
      {0, 0, 1.0 / (3.1415 / 2), get_bitmap_bin_ref().auto_get("backgrounds/Sky3.png")},
      {0, 0, 1.0 / (3.1415 / 2), get_bitmap_bin_ref().auto_get("backgrounds/Cloud3a.png")},
      {0, 0, 1.0 / (3.1415 / 2), get_bitmap_bin_ref().auto_get("backgrounds/Cloud3b.png")},
   });
   tile_drive.set_terrain_mesh_dictionary({
      { "og-tunnel-mesh", TerrainMeshDictionaryRecord(
         "tunnel_mesh-02.tmj",
         "uv-with-decorations-0x.png",
         50,
         50,
         nullptr)
      },
   });
   tile_drive.set_current_map_identifier("og-tunnel-mesh");
   tile_drive.initialize();
   tile_drive.set_collision_stepper_step_result_callback(
      AllegroFlare::Prototypes::TileDrive::TileDrive::development_play_around_with_collision_steper_callback
   );

   //tile_drive.set_event_emitter(&event_emitter);

   // start the level
   tile_drive.reset();

   // run the interactive test
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_DOWN:
         {
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;

               case ALLEGRO_KEY_UP:
                  tile_drive.driver_press_accelerator();
               break;

               case ALLEGRO_KEY_DOWN:
                  tile_drive.driver_press_break();
               break;

               case ALLEGRO_KEY_RIGHT:
                  tile_drive.driver_turn_right();
               break;

               case ALLEGRO_KEY_LEFT:
                  tile_drive.driver_turn_left();
               break;

               case ALLEGRO_KEY_R:
                  tile_drive.reset();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_KEY_UP:
         {
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP:
                  tile_drive.driver_unpress_accelerator();
               break;

               case ALLEGRO_KEY_DOWN:
                  tile_drive.driver_unpress_break();
               break;

               case ALLEGRO_KEY_RIGHT:
                  tile_drive.driver_turn_none();
               break;

               case ALLEGRO_KEY_LEFT:
                  tile_drive.driver_turn_none();
               break;
            }
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            tile_drive.update();

            clear();
            tile_drive.render();
            al_flip_display();
         break;
      }

      //if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) abort = true;
   }
   
   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.
   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();
}



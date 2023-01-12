
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/Screen.hpp>

#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_ScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Screen platforming2d;
}


TEST(AllegroFlare_Prototypes_Platforming2D_ScreenTest,
   //INTERACTIVE__in_an_AllegroFlare_Frameworks_Full_context__will_run_as_expected)
   DISABLED__INTERACTIVE__in_an_AllegroFlare_Frameworks_Full_context__will_run_as_expected)
{
   AllegroFlare::Frameworks::Full framework;
   framework.set_deployment_environment("test");
   framework.disable_auto_created_config_warning();
   framework.disable_fullscreen();
   framework.initialize();

   std::string data_folder_path = framework.get_data_folder_path();


   //framework.get_bitmap_bin_ref().set_full_path(framework.get_data_folder_path() + "bitmaps/");

   AllegroFlare::Prototypes::Platforming2D::Screen platforming_2d;
   platforming_2d.set_bitmap_bin(&framework.get_bitmap_bin_ref());
   platforming_2d.set_display(framework.get_primary_display());
   platforming_2d.set_event_emitter(&framework.get_event_emitter_ref());
   platforming_2d.set_map_dictionary({
      //{ "map_a", data_folder_path + "maps/map1-0x.tmj" },
      //{ "map_b", data_folder_path + "maps/map1b-0x.tmj" },
      { "map_a", data_folder_path + "maps/map1-0x.tmj" },
      { "map_b", data_folder_path + "maps/map1b-0x.tmj" },
   });
   platforming_2d.initialize_maps();
   platforming_2d.set_currently_active_map("map_a");

   // create some entities




   // create an animation book (to create an frame_animated type from the factory)
   // TODO: introduce this concept to the test
   AllegroFlare::FrameAnimation::Book animation_book(
      data_folder_path + "bitmaps/sprites_grid-x.png",
      data_folder_path + "bitmaps/sprites_grid-x.json",
      1
   );
   animation_book.initialize();






      AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory factory(
         &framework.get_bitmap_bin_ref(),
         &animation_book
      );
      factory.set_init_entities_drawing_debug(true);

      AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* created_entity =
         factory.create_for_aabb2d("map_a", 16-1, 32-1);
      created_entity->get_place_ref().position.x = 400/2;
      created_entity->get_place_ref().position.y = 240/2;

      platforming_2d.add_entity_to_pool(created_entity);

      AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D* created_animated_entity =
         factory.create_frame_animated("map_a", 400/2, 240/2, 12, 8, "blob", "bottom_centered_edge");
      created_animated_entity->get_place_ref().scale = { 1.5f, 1.5f };


      platforming_2d.add_entity_to_pool(created_animated_entity);


      platforming_2d.set_player_controlled_entity(created_entity);


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
         platforming_2d.add_entity_to_pool(enemy);
      }

      AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* collectable2 =
         factory.create_collectable("map_a", 5*16, 20*16);
      platforming_2d.add_entity_to_pool(collectable2);

      platforming_2d.add_entity_to_pool(factory.create_collectable("map_a", 45*16, 2*16));

      // create the door
      platforming_2d.add_entity_to_pool(
         factory.create_door("map_b", 4.5*16, 7*16, "map_a", 46*16, 26*16)
      );
      platforming_2d.add_entity_to_pool(
         factory.create_door("map_a", 46*16, 26*16, "map_b", 4.5*16, 7*16)
      );


   platforming_2d.initialize();


   framework.register_screen("platforming_2d", &platforming_2d);
   framework.activate_screen("platforming_2d");

   framework.run_loop();
}



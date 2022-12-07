
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/Screen.hpp>

#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_ScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Screen platforming2d;
}


TEST(AllegroFlare_Prototypes_Platforming2D_ScreenTest,
   //INTERACTIVE__will_run_in_AllegroFlare_Frameworks_Full_context)
   DISABLED__INTERACTIVE__will_run_in_AllegroFlare_Frameworks_Full_context)
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   framework.get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps");

   AllegroFlare::Prototypes::Platforming2D::Screen platforming_2d;
   platforming_2d.set_bitmap_bin(&framework.get_bitmap_bin_ref());
   platforming_2d.set_display(framework.get_primary_display());
   platforming_2d.set_event_emitter(&framework.get_event_emitter_ref());
   platforming_2d.set_map_dictionary({
      { "map_a", "/Users/markoates/Repos/allegro_flare/bin/data/maps/map1-0x.tmj" },
      { "map_b", "/Users/markoates/Repos/allegro_flare/bin/data/maps/map1b-0x.tmj" },
   });
   platforming_2d.initialize_maps();
   platforming_2d.set_currently_active_map("map_a");

   // create some entities




      AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory factory(&framework.get_bitmap_bin_ref());
      AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* created_entity = factory.create_for_aabb2d("map_a", 16-1, 32-1);
      created_entity->get_place_ref().position.x = 400/2;
      created_entity->get_place_ref().position.y = 240/2;

      platforming_2d.set_player_controlled_entity(created_entity);
      platforming_2d.add_entity_to_pool(created_entity);

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

      AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* collectable2 = factory.create_collectable("map_a", 5*16, 20*16);
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



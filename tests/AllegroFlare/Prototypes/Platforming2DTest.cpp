
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D.hpp>


TEST(AllegroFlare_Prototypes_Platforming2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D platforming2d;
}


TEST(AllegroFlare_Prototypes_Platforming2DTest,
   INTERACTIVE__will_run_in_AllegroFlare_Frameworks_Full_context)
{
   AllegroFlare::Frameworks::Full framework;
   framework.disable_fullscreen();
   framework.initialize();

   framework.get_bitmap_bin_ref().set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps");

   AllegroFlare::Prototypes::Platforming2D platforming_2d(
      &framework,
      framework.get_primary_display(),
      &framework.get_event_emitter_ref()
   );
   platforming_2d.initialize();

   framework.register_screen("platforming_2d", &platforming_2d);
   framework.activate_screen("platforming_2d");

   framework.run_loop();
}



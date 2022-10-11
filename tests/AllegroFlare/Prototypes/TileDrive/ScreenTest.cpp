
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/TileDrive/Screen.hpp>

#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


TEST(AllegroFlare_Prototypes_TileDrive_ScreenTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::TileDrive::Screen screen;
}


TEST(AllegroFlare_Prototypes_TileDrive_ScreenTest, DISABLED__initialize__does_not_blow_up)
   // TODO: finish this test
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   al_reserve_samples(8);

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

   al_uninstall_audio();
   al_uninstall_system();
}



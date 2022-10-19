

#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Screen.hpp>


int main(int argc, char **argv)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();

   AllegroFlare::BitmapBin &bitmap_bin = framework.get_bitmap_bin_ref();
   AllegroFlare::FontBin &font_bin = framework.get_font_bin_ref();
   AllegroFlare::SampleBin &sample_bin = framework.get_sample_bin_ref();
   AllegroFlare::EventEmitter &event_emitter = framework.get_event_emitter_ref();
   AllegroFlare::AudioController &audio_controller = framework.get_audio_controller_ref();
   bitmap_bin.set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/bitmaps");
   font_bin.set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/fonts");
   sample_bin.set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/samples");

   audio_controller.set_and_load_sound_effect_elements({
         { "menu-click-01.wav", { "menu-click-01.wav", false, "restart" } },
         });

   AllegroFlare::Prototypes::FixedRoom2D::Screen example(&bitmap_bin, &font_bin, &event_emitter);
   example.initialize();
   example.load_gametest_configuration();
   example.enter_start_room();

   framework.register_screen("example", &example);

   framework.activate_screen("example");

   framework.run_loop();

   framework.shutdown();
   return 0;
}



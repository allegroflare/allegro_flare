
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/MindDive/Hypersync.hpp>

#include <allegro5/allegro_acodec.h>
#include <AllegroFlare/TimerFormatter.hpp>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/Placement2D.hpp>


TEST(AllegroFlare_Prototypes_MindDive_HypersyncTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::Hypersync hypersync;
}


TEST(AllegroFlare_Prototypes_MindDive_HypersyncTest, DISABLED__initialize__does_not_blow_up)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();
   AllegroFlare::Prototypes::MindDive::Hypersync hypersync;

   hypersync.initialize();

   hypersync.destruct();
   al_uninstall_audio();
   al_uninstall_system();
}


TEST(AllegroFlare_Prototypes_MindDive_HypersyncTest, DISABLED__start__will_play_the_audio_stream)
{
   // NOTE: these tests need to be disabled because audio stream for some reason seem to conflict/leak
   // between test cases, even after being shutdown
   al_init();
   al_init_acodec_addon();
   al_install_audio();
   al_init_acodec_addon();
   AllegroFlare::Prototypes::MindDive::Hypersync hypersync;
   hypersync.initialize();

   hypersync.start();

   hypersync.destruct();
   al_uninstall_audio();
   al_uninstall_system();
}


TEST(AllegroFlare_Prototypes_MindDive_HypersyncTest,
   DISABLED__INTERACTIVE__start__will_synchronize_the_audio_stream_with_the_timer)
{
   al_init();
   al_init_acodec_addon();
   al_install_audio();
   al_init_acodec_addon();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   al_install_keyboard();
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   al_init_font_addon();
   ALLEGRO_FONT *al_font = al_create_builtin_font();

   ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0f);
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   AllegroFlare::Prototypes::MindDive::Hypersync hypersync;
   hypersync.initialize();
   //hypersync.start();

   ALLEGRO_EVENT event;
   bool abort_program = false;
   al_start_timer(timer);
   //int clicks_to_end = 60*6;
   //hypersync.start();
   while (!abort_program)
   {
      al_wait_for_event(event_queue, &event);
      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
            switch(event.keyboard.keycode)
            {
               case ALLEGRO_KEY_S:
                  hypersync.start();
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort_program = true;
               break;
            }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{1, 1, 1, 1});
            { // draw timer
               std::string timer_format = AllegroFlare::TimerFormatter(hypersync.get_timer_milliseconds()).format();
               AllegroFlare::Placement2D place;
               place.scale = { 8, 8 };
               place.position = { 1920/2, 1080/3 };
               place.start_transform();
               al_draw_text(al_font, ALLEGRO_COLOR{0, 0, 0, 1}, 0, 0, ALLEGRO_ALIGN_CENTER, timer_format.c_str());
               place.restore_transform();
            }
            { // draw beat clock
               AllegroFlare::Placement2D place;
               place.scale = { 8, 8 };
               place.position = { 1920/2, 1080/3*2 };
               place.start_transform();
               std::string beat_clock_str = hypersync.build_beat_clock_str();
               al_draw_text(al_font, ALLEGRO_COLOR{0, 0, 0, 1}, 0, 0, ALLEGRO_ALIGN_CENTER, beat_clock_str.c_str());
               place.restore_transform();
            }
            al_flip_display();
            //clicks_to_end--;
            //if (clicks_to_end < 0) abort_program = true;
         break;
      }
   }

   hypersync.destruct();

   al_destroy_display(display);
   al_unregister_event_source(event_queue, al_get_timer_event_source(timer));
   al_destroy_timer(timer);

   al_destroy_font(al_font);
   al_shutdown_font_addon();
   al_uninstall_keyboard();

   al_destroy_event_queue(event_queue);
   al_uninstall_audio();
   al_uninstall_system();
}



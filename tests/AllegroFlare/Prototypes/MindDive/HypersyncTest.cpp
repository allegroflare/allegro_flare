
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/MindDive/Hypersync.hpp>

#include <allegro5/allegro_acodec.h>
#include <AllegroFlare/TimerFormatter.hpp>


TEST(AllegroFlare_Prototypes_MindDive_HypersyncTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::Hypersync hypersync;
}


TEST(AllegroFlare_Prototypes_MindDive_HypersyncTest, DISABLED__initialize__does_not_blow_up)
{
   al_init();
   al_install_audio();
   al_init_acodec_addon();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::Prototypes::MindDive::Hypersync hypersync(event_queue);

   hypersync.initialize();

   hypersync.destruct();
   al_destroy_event_queue(event_queue);
   al_uninstall_audio();
   al_uninstall_system();
}


TEST(AllegroFlare_Prototypes_MindDive_HypersyncTest, start__will_play_the_audio_stream)
{
   al_init();
   al_init_acodec_addon();
   al_install_audio();
   al_init_acodec_addon();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::Prototypes::MindDive::Hypersync hypersync(event_queue);
   hypersync.initialize();

   hypersync.start();

   hypersync.destruct();
   al_destroy_event_queue(event_queue);
   al_uninstall_audio();
   al_uninstall_system();
}


TEST(AllegroFlare_Prototypes_MindDive_HypersyncTest, start__will_synchronize_the_audio_stream_with_the_timer)
{
   al_init();
   al_init_acodec_addon();
   al_install_audio();
   al_init_acodec_addon();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60.0f);
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   al_register_event_source(event_queue, al_get_timer_event_source(timer));

   AllegroFlare::Prototypes::MindDive::Hypersync hypersync(event_queue);
   hypersync.initialize();

   ALLEGRO_EVENT event;
   bool abort_program = false;
   al_start_timer(timer);
   int clicks_to_end = 60;
   hypersync.start();
   while (!abort_program)
   {
      al_wait_for_event(event_queue, &event);
      switch(event.type)
      {
         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{1, 1, 1, 1});
            al_flip_display();
            clicks_to_end--;
            if (clicks_to_end < 0) abort_program = true;
         break;
      }
   }

   hypersync.destruct();

   al_destroy_display(display);
   al_unregister_event_source(event_queue, al_get_timer_event_source(timer));
   al_destroy_timer(timer);

   al_destroy_event_queue(event_queue);
   al_uninstall_audio();
   al_uninstall_system();
}



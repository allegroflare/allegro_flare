
#include <gtest/gtest.h>

#include <AllegroFlare/SyncOracle.hpp>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <cmath>


TEST(AllegroFlare_SyncOracleTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SyncOracle sync_oracle;
}


TEST(AllegroFlare_SyncOracleTest, initialize__will_not_blow_up)
{
   al_init();
   al_init_font_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_EVENT_QUEUE *primary_event_queue = al_create_event_queue();

   AllegroFlare::SyncOracle sync_oracle;
   sync_oracle.set_primary_event_queue(primary_event_queue);
   sync_oracle.set_display(display);
   sync_oracle.initialize();
   sync_oracle.shutdown();

   al_destroy_event_queue(primary_event_queue);
   al_shutdown_font_addon();
   al_uninstall_system();
}


TEST(AllegroFlare_SyncOracleTest, draw_metric__will_draw_the_samples)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   std::vector<double> samples;
   samples.resize(64*4, 0.0);
   int i=0;
   for (auto &sample : samples)
   {
      sample = std::sin(i) * 0.25;
      i++;
   }

   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
   AllegroFlare::SyncOracle::draw_metric(&samples, ALLEGRO_COLOR{1, 1, 1, 1}, 100, 100, 500, -1, 1, samples.size(), 4);
   al_flip_display();
   //al_rest(1);

   al_destroy_display(display);
   al_shutdown_font_addon();
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST(AllegroFlare_SyncOracleTest, INTERACTIVE__will_work_as_expected)
{
   // Init allegro
   al_init();
   al_install_keyboard();
   al_init_primitives_addon();
   al_init_font_addon();

   // Setup our allegro system
   ALLEGRO_EVENT_QUEUE *primary_event_queue = al_create_event_queue();
   al_register_event_source(primary_event_queue, al_get_keyboard_event_source());
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   ALLEGRO_FONT *font = al_create_builtin_font();
   
   // Setup our sync system
   AllegroFlare::SyncOracle sync_oracle;
   sync_oracle.set_display(display);
   sync_oracle.set_target_fps(60);
   sync_oracle.set_primary_event_queue(primary_event_queue);
   sync_oracle.activate_hyper_timer();
   sync_oracle.activate_auto_nudge();
   sync_oracle.initialize();

   // Do our stuff here
   bool quit = false;
   ALLEGRO_EVENT this_event, next_event;
   while (!quit)
   {
      bool draw = false;
      al_wait_for_event(primary_event_queue, &this_event);

      sync_oracle.start_update_measure(); //---

      switch (this_event.type)
      {
         case ALLEGRO_EVENT_TIMER: {
            if (sync_oracle.is_primary_timer_event(&this_event))
            {
               sync_oracle.capture_primary_timer_event_time(this_event.any.timestamp);
               draw = true;
            }
         } break;

         case ALLEGRO_EVENT_KEY_DOWN: {
            switch (this_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_UP: {
                  sync_oracle.nudge_primary_timer_forward();
               } break;

               case ALLEGRO_KEY_DOWN: {
                  sync_oracle.nudge_primary_timer_backward();
               } break;

               case ALLEGRO_KEY_H: {
                  sync_oracle.toggle_hyper_timer();
               } break;

               case ALLEGRO_KEY_A: {
                  sync_oracle.toggle_auto_nudge();
               } break;

               case ALLEGRO_KEY_ESCAPE: {
                  quit = true;
               } break;
         
            }
         } break;
      }
      sync_oracle.end_update_measure(); //---

      if (draw)
      {
         // Draw here
         sync_oracle.start_draw_measure(); { // ---
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            sync_oracle.draw_graph();
         } sync_oracle.end_draw_measure(); // ---

         // Flip here
         sync_oracle.start_flip_measure(); // ---
         al_flip_display();
         sync_oracle.end_flip_measure(); // ---
      }
   }

   // Shutdown our sync system
   sync_oracle.shutdown();

   // Shut allegro down
   al_destroy_font(font);
   al_destroy_display(display);
   al_destroy_event_queue(primary_event_queue);
   al_shutdown_font_addon();
   al_uninstall_keyboard();
   al_uninstall_system();
}




#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/MindDive/Hypersync.hpp>

#include <allegro5/allegro_acodec.h>


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
   al_rest(2.0);

   hypersync.destruct();
   al_destroy_event_queue(event_queue);
   al_uninstall_audio();
   al_uninstall_system();
}




#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Screens_RollingCreditsTest : public ::testing::Test
{};

class AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};

#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>

#include <AllegroFlare/Screens/RollingCredits.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/EventNames.hpp>


TEST_F(AllegroFlare_Screens_RollingCreditsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::RollingCredits rolling_credits;
}


TEST_F(AllegroFlare_Screens_RollingCreditsTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::RollingCredits rolling_credits;
   std::string expected_error_message =
      "RollingCredits::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(rolling_credits.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Screens::RollingCredits rolling_credits;
   rolling_credits.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture,
   update__on_the_event_that_the_the_y_offset_moves_past_the_end__will_set__scroll_is_past_end__to_true)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture,
   update__on_the_event_that_the_the_y_offset_moves_past_the_end__will_emit_an_event_with_the_expected_name)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture,
   DISABLED__INTERACTIVE__will_work_as_expected)
{
   // setup system
   al_install_keyboard();
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

   // initialize test subject
   AllegroFlare::Elements::RollingCredits::SectionFactory section_factory;
   AllegroFlare::Screens::RollingCredits rolling_credits_screen;
   rolling_credits_screen.set_font_bin(&get_font_bin_ref());
   rolling_credits_screen.set_event_emitter(&event_emitter);
   rolling_credits_screen.set_sections({
      section_factory.create_header("Production"),
      section_factory.create_column_with_labels({
         { "Producer", "Robyn Kendall" },
         { "Production Design", "Tayyibah Samuels" },
         { "Music", "Ryker Odling" },
         { "Sound Design", "Aiza Rivera" },
         { "Lead Programming", "Annaliese Bauer" },
         { "Motion Design", "Ellenor Cote" },
         { "Element Design", "Katy Swanson" },
         { "Marketing Manager", "Melina Kelly" },
         { "Set Design", "Abby Burton" },
      }),
      section_factory.create_header("Programming"),
      section_factory.create_column_with_labels({
         { "Programmer", "Ducky Donaldson" },
         { "Programming", "Carla Cow" },
         { "Motion Programmer", "Colt Cat" },
         { "Scene Programmers", "John Calf" },
      }),
   });
   rolling_credits_screen.initialize();
   rolling_credits_screen.on_activate();

   // run the interactive test
   al_start_timer(primary_timer);
   while(!abort)
   {
      al_wait_for_event(event_queue, &event);

      switch(event.type)
      {
         case ALLEGRO_EVENT_KEY_CHAR:
         {
            //int button_num = 0;
            //if (event.keyboard.keycode == ALLEGRO_KEY_UP) button_num = AllegroFlare::VirtualControls::get_BUTTON_UP();
            //if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) button_num = AllegroFlare::VirtualControls::get_BUTTON_DOWN();
            //if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) button_num = AllegroFlare::VirtualControls::get_BUTTON_A();
            //if (button_num != 0) game_over_screen.virtual_control_button_down_func(0, button_num, event.keyboard.repeat);
            abort = true;
         }
         break;

         case ALLEGRO_EVENT_TIMER:
            al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
            rolling_credits_screen.primary_timer_func();
            al_flip_display();
         break;

         case ALLEGRO_FLARE_EVENT_GAME_EVENT:
            abort = true;
         break;
      }

      if (event.type == ALLEGRO_EVENT_KEY_CHAR && event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) abort = true;
   }
   
   // teardown
   // TODO: Audit if this teardown is complete. It may require other calls to destroy resources.
   al_destroy_event_queue(event_queue);
   al_destroy_timer(primary_timer);
   al_uninstall_keyboard();

   // TODO *destroy credits sections
}




#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
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


TEST_F(AllegroFlare_Screens_RollingCreditsTest, FOCUS__render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Screens::RollingCredits rolling_credits;
   //std::string expected_error_message =
      //"RollingCredits::render: error: guard \"al_is_system_installed()\" not met";
   //EXPECT_THROW_WITH_MESSAGE(rolling_credits.render(), std::runtime_error, expected_error_message);
   EXPECT_THROW_GUARD_ERROR(
      rolling_credits.render(),
      "AllegroFlare::Screens::RollingCredits::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Screens::RollingCredits rolling_credits;
   rolling_credits.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture,
   update__when_the_y_offset_is_greater_than_the_height__will_set__scroll_is_past_end__to_true)
{
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   AllegroFlare::Screens::RollingCredits rolling_credits;
   rolling_credits.set_font_bin(&get_font_bin_ref());
   rolling_credits.set_event_emitter(&event_emitter);
   rolling_credits.initialize();
   float a_y_offset_greater_than_the_height = rolling_credits.get_cached_calculated_height() + 1.0f;
   rolling_credits.set_y_offset(a_y_offset_greater_than_the_height);

   rolling_credits.update();

   EXPECT_EQ(true, rolling_credits.get_scroll_is_past_end());
}


TEST_F(AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture,
   update__when_the_y_offset_is_greater_than_the_height__when_a_game_event_name_to_emit_after_completing_is_present__\
will_emit_a_game_event_with_the_expected_name)
{
   std::string MY_GAME_EVENT_TO_EMIT = "my_game_event_to_emit";
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   AllegroFlare::Screens::RollingCredits rolling_credits;
   rolling_credits.set_font_bin(&get_font_bin_ref());
   rolling_credits.set_event_emitter(&event_emitter);
   rolling_credits.clear_route_event_to_emit_after_completing();
   rolling_credits.set_game_event_name_to_emit_after_completing(MY_GAME_EVENT_TO_EMIT);
   rolling_credits.initialize();
   float a_y_offset_greater_than_the_height = rolling_credits.get_cached_calculated_height() + 1.0f;
   rolling_credits.set_y_offset(a_y_offset_greater_than_the_height);

   rolling_credits.update();

   ALLEGRO_EVENT event;
   ASSERT_EQ(true, al_get_next_event(event_queue, &event));
   EXPECT_EQ(ALLEGRO_FLARE_EVENT_GAME_EVENT, event.type);
   ASSERT_NE(nullptr, (void *)(event.user.data1));
   AllegroFlare::GameEvent *data1 = static_cast<AllegroFlare::GameEvent *>((void*)event.user.data1);
   AllegroFlare::GameEvent expected_game_event(MY_GAME_EVENT_TO_EMIT);
   EXPECT_EQ(expected_game_event.get_type(), (*data1).get_type());

   al_destroy_event_queue(event_queue);
}


TEST_F(AllegroFlare_Screens_RollingCreditsTestWithAllegroRenderingFixture,
   update__when_the_y_offset_is_greater_than_the_height__when_a_route_event_to_emit_after_completing_is_present\
will_emit_a_route_event_with_the_expected_value)
{
   uint32_t MY_ROUTE_EVENT_TO_EMIT = 12345;
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());

   AllegroFlare::Screens::RollingCredits rolling_credits;
   rolling_credits.set_font_bin(&get_font_bin_ref());
   rolling_credits.set_event_emitter(&event_emitter);
   rolling_credits.clear_game_event_name_to_emit_after_completing();
   rolling_credits.set_route_event_to_emit_after_completing(MY_ROUTE_EVENT_TO_EMIT);
   rolling_credits.initialize();
   float a_y_offset_greater_than_the_height = rolling_credits.get_cached_calculated_height() + 1.0f;
   rolling_credits.set_y_offset(a_y_offset_greater_than_the_height);

   rolling_credits.update();

   ALLEGRO_EVENT event;
   ASSERT_EQ(true, al_get_next_event(event_queue, &event));
   EXPECT_EQ(ALLEGRO_FLARE_EVENT_ROUTER, event.type);
   EXPECT_EQ(MY_ROUTE_EVENT_TO_EMIT, event.user.data1);

   al_destroy_event_queue(event_queue);
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
            //if (event.keyboard.keycode == ALLEGRO_KEY_UP) button_num = AllegroFlare::VirtualController::get_BUTTON_UP();
            //if (event.keyboard.keycode == ALLEGRO_KEY_DOWN) button_num = AllegroFlare::VirtualController::get_BUTTON_DOWN();
            //if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) button_num = AllegroFlare::VirtualController::get_BUTTON_A();
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



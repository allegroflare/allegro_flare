
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventNames.hpp>

#include <AllegroFlare/GameEvent.hpp>


class AllegroFlare_Screens_StoryboardTest : public ::testing::Test
{};

class AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Screens/Storyboard.hpp>


TEST_F(AllegroFlare_Screens_StoryboardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Storyboard storyboard;
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture, primary_timer_func__will_not_blow_up)
{
   AllegroFlare::Screens::Storyboard storyboard(&get_font_bin_ref());
   storyboard.initialize();
   storyboard.primary_timer_func();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   primary_timer_func__will_draw_the_current_page_text_to_the_screen)
{
   std::vector<std::string> pages = { "Hello Storyboard!" };
   AllegroFlare::Screens::Storyboard storyboard(&get_font_bin_ref(), nullptr);
   storyboard.get_storyboard_element_ref().set_pages(pages);
   storyboard.initialize();

   storyboard.primary_timer_func();
   al_flip_display();

   sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   key_down_func__will_advance_to_the_next_page)
{
   AllegroFlare::EventEmitter event_emitter;
   std::vector<std::string> pages = {
      "This is page 1.",
      "The second page looks like this.",
      "A final page is this one, indeed.",
   };
   AllegroFlare::Screens::Storyboard storyboard(&get_font_bin_ref(), &event_emitter); //, pages);
   storyboard.get_storyboard_element_ref().set_pages(pages);
   storyboard.initialize();

   storyboard.primary_timer_func();
   al_flip_display();

   EXPECT_EQ(0, storyboard.get_storyboard_element_ref().get_current_page_num()); // TODO: this line should be a separate test
   for (int i=0; i<(pages.size()-1); i++)
   {
      storyboard.key_down_func();
      int expected_page_num = i+1;
      EXPECT_EQ(expected_page_num, storyboard.get_storyboard_element_ref().get_current_page_num());
   }

   SUCCEED();
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   key_down_func__without_an_event_emitter__will_throw_an_error)
{
   AllegroFlare::Screens::Storyboard storyboard;
   storyboard.initialize();
   std::string expected_error_message =
      "Storyboard::key_down_func: error: guard \"event_emitter\" not met";
   EXPECT_THROW_WITH_MESSAGE(storyboard.key_down_func(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   key_down_func__when_at_the_final_page__will_emit_a_game_event_with_the_expected_values_if_the_param_is_set)
{
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   ALLEGRO_EVENT event;
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   std::vector<std::string> pages = { "This is page 1.", "Here is the last page." };

   AllegroFlare::Screens::Storyboard storyboard(
         &get_font_bin_ref(),
         &event_emitter
      );
   storyboard.get_storyboard_element_ref().set_pages(pages);
   storyboard.initialize();

   // first page should not trigger an event
   storyboard.key_down_func();
   ASSERT_EQ(false, al_get_next_event(event_queue, &event));

   // now at the last page, this should trigger an event
   storyboard.key_down_func();
   ASSERT_EQ(true, al_get_next_event(event_queue, &event));

   // the generated event should have the expected values
   EXPECT_EQ(ALLEGRO_FLARE_EVENT_GAME_EVENT, event.type);
   ASSERT_NE(nullptr, (void *)(event.user.data1));
   AllegroFlare::GameEvent *data1 = static_cast<AllegroFlare::GameEvent *>((void*)event.user.data1);
   AllegroFlare::GameEvent expected_game_event("storyboard_finished");
   EXPECT_EQ(expected_game_event.get_name(), (*data1).get_name());

   // shutdown
   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
}




#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>

#include <AllegroFlare/EventNames.hpp>

#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>


class AllegroFlare_Screens_StoryboardTest : public ::testing::Test
{};

class AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};

class AllegroFlare_Screens_StoryboardTestWithAllegroFlareFrameworksFullFixture :
   public AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture
{
   virtual void SetUp() override
   {
      get_framework_ref().disable_using_display_backbuffer_as_primary_render_surface(); // TODO: See if this line
                                                                                        // can be removed
      AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::SetUp();
   }
};


#include <AllegroFlare/Screens/Storyboard.hpp>


class StoryboardPageTestClass : public AllegroFlare::Elements::StoryboardPages::Base
{
public:
   ALLEGRO_FONT *font;
   std::string text;
   float opacity;
   StoryboardPageTestClass(ALLEGRO_FONT *font, std::string text) : font(font), text(text), opacity(1) {};
   virtual void render() override
   {
      ALLEGRO_COLOR color = ALLEGRO_COLOR{opacity, opacity, opacity, opacity};
      al_draw_text(font, color, 1920/2, 1080/2, ALLEGRO_ALIGN_CENTER, text.c_str());
   }
   virtual void update() override
   {
      // nothing to do really
      //opacity += 0.05;
      //if (opacity > 1.0) opacity = 0.0f;
   }
};


TEST_F(AllegroFlare_Screens_StoryboardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Screens::Storyboard storyboard;
}


TEST_F(AllegroFlare_Screens_StoryboardTest, has_the_expected_type)
{
   AllegroFlare::Screens::Storyboard storyboard;
   EXPECT_EQ("Storyboard", storyboard.get_type());
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture, primary_timer_func__will_not_blow_up)
{
   AllegroFlare::Screens::Storyboard storyboard(&get_font_bin_ref());
   storyboard.initialize();
   storyboard.primary_timer_func();
   SUCCEED();
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   DISABLED__primary_timer_func__will_update_the_storyboard_element)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   DISABLED__primary_timer_func__with_auto_advance_on__and_the_storyboard_element_can_go_to_the_next_page__will_advance)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   DISABLED__primary_timer_func__will_render_the_storyboard_element)
{
   // TODO
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   CAPTURE__primary_timer_func__will_draw_the_current_page_text_to_the_screen)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   ALLEGRO_FONT *font = font_bin["Inter-Medium.ttf -60"];
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = {
      new StoryboardPageTestClass(font, "Hello Storyboard!")
   };
   AllegroFlare::Screens::Storyboard storyboard(&get_font_bin_ref(), nullptr);
   storyboard.get_storyboard_element_ref().set_pages(pages);
   storyboard.initialize();

   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   storyboard.primary_timer_func();
   al_flip_display();

   //sleep_for(1)

   SUCCEED();
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   virtual_control_button_down_func__without_an_event_emitter__will_throw_an_error)
{
   AllegroFlare::Screens::Storyboard storyboard;
   storyboard.initialize();
   std::string expected_error_message =
      "Storyboard::virtual_control_button_down_func: error: guard \"event_emitter\" not met";
   EXPECT_THROW_WITH_MESSAGE(storyboard.virtual_control_button_down_func(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   DISABLED__virtual_control_button_down_func__with_the_expected_virtual_buttons__will_advance_the_storybard)
   // TODO
{
   AllegroFlare::EventEmitter event_emitter;
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::VirtualControllers::GenericController virtual_controller;
   ALLEGRO_FONT *font = font_bin["Inter-Medium.ttf -40"];
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = {
      new StoryboardPageTestClass(font, "This is Page 1!"),
      new StoryboardPageTestClass(font, "This is the second page!"),
      new StoryboardPageTestClass(font, "The final page is here."),
   };
   AllegroFlare::Screens::Storyboard storyboard(&get_font_bin_ref(), &event_emitter);
   storyboard.get_storyboard_element_ref().set_pages(pages);
   storyboard.initialize();

   int tries_to_bail = 50;
   int expected_advances_needed = 6;
   while (!storyboard.get_storyboard_element_ref().get_finished())
   {
      storyboard.virtual_control_button_down_func(
            nullptr,
            &virtual_controller,
            AllegroFlare::VirtualControllers::GenericController::BUTTON_A
      );
      tries_to_bail--;
      if (tries_to_bail < 0) FAIL();
   }

   SUCCEED();
}


TEST_F(AllegroFlare_Screens_StoryboardTestWithAllegroRenderingFixture,
   DISABLED__advance__when_at_the_final_page_that_is_finished__will_emit_a_game_event_with_the_expected_property_value)
{
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   AllegroFlare::EventEmitter event_emitter;
   event_emitter.initialize();
   ALLEGRO_EVENT event;
   al_register_event_source(event_queue, &event_emitter.get_event_source_ref());
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   ALLEGRO_FONT *font = font_bin["Inter-Medium.ttf -40"];
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = {
      new StoryboardPageTestClass(font, "This is page 1."),
      new StoryboardPageTestClass(font, "Here is the last page!"),
   };

   AllegroFlare::Screens::Storyboard storyboard(
         &get_font_bin_ref(),
         &event_emitter
      );
   storyboard.get_storyboard_element_ref().set_pages(pages);
   storyboard.initialize();

   // first page should not trigger an event
   storyboard.virtual_control_button_down_func(
         nullptr,
         nullptr,
         AllegroFlare::VirtualControllers::GenericController::BUTTON_A
   );

   //storyboard.virtual_control_button_down_func();
   ASSERT_EQ(false, al_get_next_event(event_queue, &event));

   // now at the last page, this should trigger an event
   storyboard.virtual_control_button_down_func(
         nullptr,
         nullptr,
         AllegroFlare::VirtualControllers::GenericController::BUTTON_A
   );
   //storyboard.virtual_control_button_down_func();
   ASSERT_EQ(true, al_get_next_event(event_queue, &event));

   // the generated event should have the expected values
   EXPECT_EQ(ALLEGRO_FLARE_EVENT_GAME_EVENT, event.type);
   ASSERT_NE(nullptr, (void *)(event.user.data1));
   AllegroFlare::GameEvent *data1 = static_cast<AllegroFlare::GameEvent *>((void*)event.user.data1);
   AllegroFlare::GameEvent expected_game_event("storyboard_finished");
   EXPECT_EQ(expected_game_event.get_type(), (*data1).get_type());

   // shutdown
   al_unregister_event_source(event_queue, &event_emitter.get_event_source_ref());
   al_destroy_event_queue(event_queue);
}



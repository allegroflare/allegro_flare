
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_StoryboardPlayerTest : public ::testing::Test
{};

class AllegroFlare_Elements_StoryboardPlayerTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/StoryboardPlayer.hpp>


class StoryboardPageTestClassA : public AllegroFlare::Elements::StoryboardPages::Base
{
public:
   int render_count = 0;
   int update_count = 0;
   StoryboardPageTestClassA() {};
   virtual void render() override { render_count++; }
   virtual void update() override { update_count++; }
};


class StoryboardPageTestClassB : public AllegroFlare::Elements::StoryboardPages::Base
{
public:
   ALLEGRO_FONT *font;
   std::string text;
   float opacity;
   StoryboardPageTestClassB(ALLEGRO_FONT *font, std::string text) : font(font), text(text), opacity(1) {};
   virtual void render() override
   {
      ALLEGRO_COLOR color = ALLEGRO_COLOR{opacity, opacity, opacity, opacity};
      al_draw_text(font, color, 1920/2, 1080/2, ALLEGRO_ALIGN_CENTER, text.c_str());
   }
   virtual void update() override
   {
      opacity += 0.05;
      if (opacity > 1.0) opacity = 0.0f;
   }
};


class StoryboardPageTestClassC : public AllegroFlare::Elements::StoryboardPages::Base
{
public:
   StoryboardPageTestClassC() { set_finished(false); };
   virtual void advance() override { set_finished(true); }
};


TEST_F(AllegroFlare_Elements_StoryboardPlayerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPlayer storyboard_player;
}


TEST_F(AllegroFlare_Elements_StoryboardPlayerTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::StoryboardPlayer storyboard_player;
   std::string expected_error_message =
      "StoryboardPlayer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(storyboard_player.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_StoryboardPlayerTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::StoryboardPlayer storyboard_player;
   storyboard_player.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardPlayerTestWithAllegroRenderingFixture,
   render__will_call_render_on_the_current_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::StoryboardPlayer storyboard_player(&font_bin, pages);

   storyboard_player.render();
   ASSERT_EQ(1, test_page->render_count);

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardPlayerTestWithAllegroRenderingFixture,
   update__will_call_update_on_the_current_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::StoryboardPlayer storyboard_player(&font_bin, pages);

   storyboard_player.update();
   ASSERT_EQ(1, test_page->update_count);

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardPlayerTestWithAllegroRenderingFixture,
   VISUAL__render__will_render_the_current_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   ALLEGRO_FONT *font = font_bin["Inter-Medium.ttf -60"];
   StoryboardPageTestClassB *test_page = new StoryboardPageTestClassB(font, "This is the test page text.");
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::StoryboardPlayer storyboard_player(&font_bin, pages);

   for (int passes=0; passes<=20; passes++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      storyboard_player.update();
      storyboard_player.render();
      al_flip_display();
   }

   delete test_page;
}



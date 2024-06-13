
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_StoryboardTest : public ::testing::Test
{};

class AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Storyboard.hpp>


class StoryboardPageTestClassA : public AllegroFlare::Elements::StoryboardPages::Base
{
public:
   int start_count = 0;
   int render_count = 0;
   int update_count = 0;
   StoryboardPageTestClassA() { };
   virtual void start() override { start_count++; }
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
   int advance_count = 0;
   StoryboardPageTestClassC() { set_finished(false); };
   virtual void update() override { set_finished(true); }
   virtual void advance() override { advance_count++; }
};


class StoryboardPageTestClassD : public AllegroFlare::Elements::StoryboardPages::Base
{
public:
   StoryboardPageTestClassD() { set_finished(false); };
   virtual void advance() override { set_finished(true); }
};


TEST_F(AllegroFlare_Elements_StoryboardTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Storyboard storyboard_player;
}


TEST_F(AllegroFlare_Elements_StoryboardTest, finished__is_initialized_to_false)
{
   AllegroFlare::Elements::Storyboard storyboard_player;
   EXPECT_EQ(false, storyboard_player.get_finished());
}


TEST_F(AllegroFlare_Elements_StoryboardTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Storyboard storyboard_player;
   EXPECT_THROW_GUARD_ERROR(
      storyboard_player.render(),
      "AllegroFlare::Elements::Storyboard::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::Storyboard storyboard_player;
   storyboard_player.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   render__will_call_render_on_the_current_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   storyboard_player.render();
   ASSERT_EQ(1, test_page->render_count);

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   update__will_call_update_on_the_current_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   storyboard_player.update();
   ASSERT_EQ(1, test_page->update_count);

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   update__when_a_page_becomes_finished__will_allow_advancing_to_the_next_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassC *test_page_1 = new StoryboardPageTestClassC;
   StoryboardPageTestClassC *test_page_2 = new StoryboardPageTestClassC;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page_1, test_page_2 };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   ASSERT_EQ(false, storyboard_player.get_can_advance_to_next_page());
   storyboard_player.update();
   ASSERT_EQ(true, storyboard_player.get_can_advance_to_next_page());

   delete test_page_1;
   delete test_page_2;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   permit_advancing_page__will_allow_advancing_to_the_next_page_and_return_true)
   // TODO
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   EXPECT_EQ(false, storyboard_player.get_can_advance_to_next_page());
   EXPECT_EQ(true, storyboard_player.permit_advancing_page());
   EXPECT_EQ(true, storyboard_player.get_can_advance_to_next_page());

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   permit_advancing_page__if_the_storyboard_is_finished__will_not_permit_advancing_to_the_next_page_and_return_false)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   storyboard_player.permit_advancing_page();
   storyboard_player.advance(); // storyboard should now be finished

   ASSERT_EQ(true, storyboard_player.get_finished());
   EXPECT_EQ(false, storyboard_player.get_can_advance_to_next_page());

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance__if_the_current_page_is_not_finished__will_call_advance_on_the_current_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassC *test_page = new StoryboardPageTestClassC;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   storyboard_player.advance();
   ASSERT_EQ(1, test_page->advance_count);

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance__if_the_current_page_becomes_finished__will_permit_advancing_the_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassD *test_page = new StoryboardPageTestClassD;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   EXPECT_EQ(false, storyboard_player.get_can_advance_to_next_page());
   storyboard_player.advance();
   EXPECT_EQ(true, test_page->get_finished());
   EXPECT_EQ(true, storyboard_player.get_can_advance_to_next_page());

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance__if_advancing_pages_is_permitted__will_advance_to_the_next_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page_1 = new StoryboardPageTestClassA;
   StoryboardPageTestClassA *test_page_2 = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page_1, test_page_2 };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   ASSERT_EQ(0, storyboard_player.get_current_page_num());
   storyboard_player.permit_advancing_page();
   storyboard_player.advance();
   ASSERT_EQ(1, storyboard_player.get_current_page_num());

   delete test_page_1;
   delete test_page_2;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance__if_advancing_pages_is_permitted__will_deny_advancing_on_the_subsequent_pages)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page_1 = new StoryboardPageTestClassA;
   StoryboardPageTestClassA *test_page_2 = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page_1, test_page_2 };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   storyboard_player.permit_advancing_page();
   storyboard_player.advance();
   EXPECT_EQ(false, storyboard_player.get_can_advance_to_next_page());

   delete test_page_1;
   delete test_page_2;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance__if_advancing_pages_is_permitted__will_call_start_on_the_subsequent_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page_1 = new StoryboardPageTestClassA;
   StoryboardPageTestClassA *test_page_2 = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page_1, test_page_2 };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   storyboard_player.permit_advancing_page();
   storyboard_player.advance();
   ASSERT_EQ(1, test_page_2->start_count);

   delete test_page_1;
   delete test_page_2;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   advance__while_on_the_last_page__and_can_advance_to_the_next_page__will_finish_the_storyboard_and_return_true)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   ASSERT_EQ(true, storyboard_player.permit_advancing_page());
   EXPECT_EQ(true, storyboard_player.advance());
   EXPECT_EQ(true, storyboard_player.get_finished());

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   reset__will_set_the_current_page_number_to_zero)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page_1 = new StoryboardPageTestClassA;
   StoryboardPageTestClassA *test_page_2 = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page_1, test_page_2 };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   storyboard_player.permit_advancing_page();
   storyboard_player.advance();

   storyboard_player.reset();
   ASSERT_EQ(0, storyboard_player.get_current_page_num());

   delete test_page_1;
   delete test_page_2;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   reset__will_call_start_on_the_first_page)
{
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(nullptr, pages);

   storyboard_player.reset();
   ASSERT_EQ(1, test_page->start_count);

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   reset__will_set_finished_to_false)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   storyboard_player.permit_advancing_page();
   storyboard_player.advance(); // storyboard should now be finished
   ASSERT_EQ(true, storyboard_player.get_finished());

   storyboard_player.reset();
   EXPECT_EQ(false, storyboard_player.get_finished());

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   reset__will_deny_advancing_to_the_next_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   StoryboardPageTestClassA *test_page = new StoryboardPageTestClassA;
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   storyboard_player.permit_advancing_page();
   storyboard_player.reset();
   ASSERT_EQ(false, storyboard_player.get_can_advance_to_next_page());

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   VISUAL__render__will_render_the_current_page)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   ALLEGRO_FONT *font = font_bin["Inter-Regular.ttf -60"];
   StoryboardPageTestClassB *test_page = new StoryboardPageTestClassB(font, "This is the test page text.");
   std::vector<AllegroFlare::Elements::StoryboardPages::Base *> pages = { test_page };
   AllegroFlare::Elements::Storyboard storyboard_player(&font_bin, pages);

   for (int passes=0; passes<=20; passes++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0.05, 0.05, 0.055, 1});
      storyboard_player.update();
      storyboard_player.render();
      al_flip_display();
   }

   delete test_page;
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   VISUAL__render__when_advancing_is_permitted__will_display_a_NEXT_button)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_StoryboardTestWithAllegroRenderingFixture,
   VISUAL__render__when_at_the_end_of_the_storyboard__will_display_a_FINISH_button)
{
   // TODO
}



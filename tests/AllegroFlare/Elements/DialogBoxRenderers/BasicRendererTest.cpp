
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#ifdef _WIN32
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
#else
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
#endif

#include <AllegroFlare/Elements/DialogBoxRenderers/BasicRenderer.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>

class AllegroFlare_Elements_DialogBoxRenderers_BasicRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer you_got_an_item_renderer;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__when_the_dialog_box_is_finished__renders_special_empty_text)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   //AllegroFlare::Placement2D place{ 1920/2, 1080/5*4, 1920/5*3, 1080/4 };
   AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text("This dialog is finished");
   dialog_box_renderer.set_is_finished(true);
   
   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };
   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__draws_multiline_dialog)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::string page_text =
      "This is some dialog test text. In this case, there's a lot of text that will need to fit on multiple lines.";
   AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };
   al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest,
   render__will_show_a_reveal_animation_respecting_age)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::string page_text =
      "This is some dialog test text. In this case, there's a lot of text that will need to fit on multiple lines.";
   AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&font_bin);
   dialog_box_renderer.set_current_page_text(page_text);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height() };

   float started_at = al_get_time();
   for (int passes=0; passes<60; passes++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});

      place.start_transform();
      dialog_box_renderer.set_age(al_get_time() - started_at);
      dialog_box_renderer.render();
      place.restore_transform();
      al_flip_display();

      sleep_for_frame();
   }
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_propertly_render_num_revealed_characters)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::string page_text = "Some test dialog text that will reveal characters sequentially when rendering.";

   int num_revealed_characters = 0;
   for (unsigned i=0; i<page_text.size(); i++)
   {
      num_revealed_characters++;

      AllegroFlare::Elements::DialogBoxRenderers::BasicRenderer dialog_box_renderer(&font_bin);
      dialog_box_renderer.set_current_page_text(page_text);
      dialog_box_renderer.set_num_revealed_characters(num_revealed_characters);

      AllegroFlare::Placement2D place{
         1920/2, 1080/2, dialog_box_renderer.get_width(), dialog_box_renderer.get_height()
      };

      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      place.start_transform();
      dialog_box_renderer.render();
      place.restore_transform();

      //al_flip_display();
      //std::this_thread::sleep_for(std::chrono::microseconds(10000)); // add sleep for more obvious visual delay
   }
   al_flip_display();
}



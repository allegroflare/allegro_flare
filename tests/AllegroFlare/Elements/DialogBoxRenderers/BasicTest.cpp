
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

#include <AllegroFlare/Elements/DialogBoxRenderers/Basic.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <allegro5/allegro_primitives.h>
#include <chrono>
#include <thread>

class AllegroFlare_Elements_DialogBoxRenderers_BasicTest : public ::testing::Test {};
class AllegroFlare_Elements_DialogBoxRenderers_BasicWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::Basic you_got_an_item_renderer;
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicWithAllegroRenderingFixtureTest,
   render__renders_the_dialog_box)
{
}

TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicWithAllegroRenderingFixtureTest,
   render__when_the_dialog_box_is_finished__renders_special_empty_text)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   AllegroFlare::Placement2D place{ 1920/2, 1080/5*4, 1920/5*3, 1080/4 };
   AllegroFlare::Elements::DialogBoxRenderers::Basic dialog_box_renderer(
      &font_bin,
      place.size.x,
      place.size.y,
      "",
      999,
      true
   );
   
   place.start_transform();
   dialog_box_renderer.render();
   place.restore_transform();
   al_flip_display();
   std::this_thread::sleep_for(std::chrono::seconds(1));
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicTest, render__draws_multiline_dialog)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   //AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   std::string dialog_box_page_text =
      "This is some dialog test text. In this case, there's a lot of text that will need to fit on multiple lines.";
   AllegroFlare::Elements::DialogBoxRenderers::Basic dialog_box_renderer(&font_bin);

   //dialog_box.reveal_all_characters();

   dialog_box_renderer.render();
   al_flip_display();
   //std::this_thread::sleep_for(std::chrono::seconds(1));

   al_destroy_display(display);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_BasicTest, render__will_propertly_render_revealing_text)
{
   al_init();
   al_init_primitives_addon();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path(TEST_FIXTURE_FONT_FOLDER);
   //AllegroFlare::Elements::DialogBoxes::Basic dialog_box;
   std::string page_text = "Some test dialog text that will reveal characters sequentially when rendering.";
   //dialog_box.set_pages({ page_text });
   AllegroFlare::Elements::DialogBoxRenderers::Basic dialog_box_renderer(&font_bin);

   int num_revealed_characters = 0;
   for (unsigned i=0; i<page_text.size(); i++)
   {
      num_revealed_characters++;
      //dialog_box.update();
      dialog_box_renderer.render();
      //al_flip_display();
      //std::this_thread::sleep_for(std::chrono::microseconds(10000)); // add sleep for more obvious visual delay
   }
   //std::this_thread::sleep_for(std::chrono::milliseconds(500));

   al_destroy_display(display);
   al_uninstall_system();
}



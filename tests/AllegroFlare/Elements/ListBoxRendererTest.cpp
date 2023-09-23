
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ListBoxRenderer.hpp>

#include <allegro5/allegro_primitives.h>


TEST(AllegroFlare_Elements_ListBoxTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ListBox list_box;
}


// TODO: Modify the tests below to make a list box


#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }



#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#ifdef _WIN32
#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/fonts/"
#else
#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/fonts/"
#endif


class AllegroFlare_Elements_ListBoxRendererTest : public ::testing::Test {};
class AllegroFlare_Elements_ListBoxRendererWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Elements_ListBoxRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::ListBoxRenderer list_box_renderer;
}


TEST_F(AllegroFlare_Elements_ListBoxRendererTest, render__without_a_list_box__throws_an_exception)
{
   al_init();
   al_init_primitives_addon();
   AllegroFlare::Elements::ListBoxRenderer list_box_renderer;
   std::string expected_error_message = "ListBoxRenderer::render: error: guard \"list_box\" not met";
   ASSERT_THROW_WITH_MESSAGE(list_box_renderer.render(), std::runtime_error, expected_error_message);
   al_shutdown_primitives_addon();
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_ListBoxRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__renders_the_elements)
{
   get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "I'm searching for the ancient lost treasure said to be hidden here.", "find_treasure" },
     { "I heard rumors of strange occurrences, so I came to investigate.",    "investigate_rumors" },
     { "I got lost while on a journey and ended up here by accident.",        "lost" },
   };
   AllegroFlare::Elements::ListBox list_box;
   list_box.set_items(choice_options);

   AllegroFlare::Elements::ListBoxRenderer list_box_renderer(
      &get_font_bin_ref(),
      &get_bitmap_bin_ref(),
      &list_box
   );
   list_box_renderer.set_height_to_fit_content();

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, list_box_renderer.get_width(), list_box_renderer.get_height() };

   list_box.move_cursor_down();
   //list_box.move_cursor_down();

   place.start_transform();
   list_box_renderer.render();
   place.restore_transform();
   al_flip_display();
   //sleep_for(1);

   SUCCEED();
}


TEST_F(AllegroFlare_Elements_ListBoxRendererWithAllegroRenderingFixtureTest,
   CAPTURE__render__when_a_selection_cursor_box_is_present__renders_it)
{
   get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "I'm searching for the ancient lost treasure said to be hidden here.", "find_treasure" },
     { "I heard rumors of strange occurrences, so I came to investigate.",    "investigate_rumors" },
     { "I got lost while on a journey and ended up here by accident.",        "lost" },
   };
   AllegroFlare::Elements::ListBox list_box;
   list_box.set_items(choice_options);
   list_box.set_wrap_at_edges(true);

   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;

   AllegroFlare::Elements::ListBoxRenderer list_box_renderer(
      &get_font_bin_ref(),
      &get_bitmap_bin_ref(),
      &list_box,
      &selection_cursor_box
   );
   list_box_renderer.set_height_to_fit_content();

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, list_box_renderer.get_width(), list_box_renderer.get_height() };

   int passes = 240;
   for (int i=0; i<passes; i++)
   { 
      if (i % (passes / 3) == (passes / 3) / 2) list_box.move_cursor_down();

      clear();
      place.start_transform();
      list_box_renderer.render();
      place.restore_transform();
      al_flip_display();
   }

   //sleep_for(1);

   SUCCEED();
}




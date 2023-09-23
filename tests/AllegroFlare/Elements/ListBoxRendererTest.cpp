
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/ListBoxRenderer.hpp>

#include <AllegroFlare/Elements/ListBox.hpp>
#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <allegro5/allegro_primitives.h>


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
      list_box.get_item_labels()
   );
   list_box_renderer.set_height_to_fit_content();

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, list_box_renderer.get_width(), list_box_renderer.get_height() };

   list_box.move_cursor_down();

   place.start_transform();
   list_box_renderer.render();
   place.restore_transform();
   al_flip_display();
   //sleep_for(1);
}


TEST_F(AllegroFlare_Elements_ListBoxRendererWithAllegroRenderingFixtureTest,
   CAPTURE__calculate_dimensions_for_list_item_at_position__returns_dimensions_that_match_the_current_selected_object)
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
      list_box.get_item_labels()
   );
   list_box_renderer.set_height_to_fit_content();

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, list_box_renderer.get_width(), list_box_renderer.get_height() };

   list_box.move_cursor_down();

   // Build an (ephemeral) cursor box
   std::tuple<float, float, float, float> current_selection_dimensions =
      list_box_renderer.calculate_dimensions_for_list_item_at_position(1);
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
   float current_selection_width = std::get<2>(current_selection_dimensions);
   float current_selection_height = std::get<3>(current_selection_dimensions);
   selection_cursor_box.set_size(current_selection_width, current_selection_height);
   selection_cursor_box.render();

   place.start_transform();
   list_box_renderer.render();
   place.restore_transform();
   al_flip_display();
   //sleep_for(1);
}


/*
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
      list_box.get_item_labels(),
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
*/




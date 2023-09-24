
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
   CAPTURE__VISUAL__calculate_dimensions_for_list_item_at_position__returns_dimensions_that_match_the_current_\
selected_object)
{
   std::vector<std::pair<std::string, std::string>> choice_options = {
     { "I'm searching for the ancient lost treasure said to be hidden here.", "find_treasure" },
     { "I heard rumors of strange occurrences, so I came to investigate.",    "investigate_rumors" },
     { "I got lost while on a journey and ended up here by accident.",        "lost" },
   };
   AllegroFlare::Elements::ListBox list_box;
   list_box.set_items(choice_options);
   list_box.set_wrap_at_edges(true);

   AllegroFlare::Elements::ListBoxRenderer list_box_renderer(
      &get_font_bin_ref(),
      &get_bitmap_bin_ref(),
      list_box.get_item_labels()
   );
   list_box_renderer.set_height_to_fit_content();

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, list_box_renderer.get_width(), list_box_renderer.get_height() };
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;

   list_box_renderer.set_cursor_position(list_box.get_cursor_position());

   // Init the cursor position to the current selection
   std::tuple<float, float, float, float> current_selection_dimensions =
      list_box_renderer.calculate_dimensions_for_list_item_at_position(list_box.get_cursor_position());
   float current_selection_x = std::get<0>(current_selection_dimensions);
   float current_selection_y = std::get<1>(current_selection_dimensions);
   float current_selection_width = std::get<2>(current_selection_dimensions);
   float current_selection_height = std::get<3>(current_selection_dimensions);
   selection_cursor_box.set_position(current_selection_x, current_selection_y);
   selection_cursor_box.set_size(current_selection_width, current_selection_height);

   int passes = 240;
   int cursor_presses = 2;
   for (int i=0; i<passes; i++)
   { 
      bool move_cursor_in_this_pass = false;
      if (i % (passes / cursor_presses) == (passes / cursor_presses) / 2) move_cursor_in_this_pass = true;
     
      if (move_cursor_in_this_pass)
      {
         // Move the cursor in the list
         list_box.move_cursor_down();

         // Update the cursor position in the renderer (currently only used to highlight the selected option text)
         // TODO: Consider an alternative where elements in the list can have selected states, selected, unselected,
         // selected_at, etc.
         list_box_renderer.set_cursor_position(list_box.get_cursor_position());

         // As a consequence to teh above, update the cursor selection box rendering position
         // (Build an ephemeral cursor box:)
         std::tuple<float, float, float, float> current_selection_dimensions =
            list_box_renderer.calculate_dimensions_for_list_item_at_position(list_box.get_cursor_position());
         float current_selection_x = std::get<0>(current_selection_dimensions);
         float current_selection_y = std::get<1>(current_selection_dimensions);
         float current_selection_width = std::get<2>(current_selection_dimensions);
         float current_selection_height = std::get<3>(current_selection_dimensions);
         selection_cursor_box.reposition_to(current_selection_x, current_selection_y);
         selection_cursor_box.resize_to(current_selection_width, current_selection_height);
      }

      // Update the selection_cursor_box
      selection_cursor_box.update();

      // Render the objects
      clear();
      place.start_transform();
      list_box_renderer.render();
      selection_cursor_box.render();
      place.restore_transform();
      al_flip_display();
   }
}


TEST_F(AllegroFlare_Elements_ListBoxRendererWithAllegroRenderingFixtureTest,
   CAPTURE__VISUAL__render__wil_fit_lists_of_various_sizes_and_styles)
{
   // TODO: Include more styles and/or contents of the list

   AllegroFlare::Elements::ListBox list_box;
   list_box.set_items({
     { "searching for treasure", "find_treasure" },
     { "investigate rumors",    "investigate_rumors" },
     { "here by accident",       "lost" },
   });
   list_box.set_wrap_at_edges(true);

   AllegroFlare::Elements::ListBoxRenderer list_box_renderer(
      &get_font_bin_ref(),
      &get_bitmap_bin_ref(),
      list_box.get_item_labels()
   );
   list_box_renderer.set_height_to_fit_content();



   AllegroFlare::Placement2D place{ 1920/2, 1080/2, list_box_renderer.get_width(), list_box_renderer.get_height() };
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;

   list_box_renderer.set_cursor_position(list_box.get_cursor_position());

   // Init the cursor position to the current selection
   std::tuple<float, float, float, float> current_selection_dimensions =
      list_box_renderer.calculate_dimensions_for_list_item_at_position(list_box.get_cursor_position());
   float current_selection_x = std::get<0>(current_selection_dimensions);
   float current_selection_y = std::get<1>(current_selection_dimensions);
   float current_selection_width = std::get<2>(current_selection_dimensions);
   float current_selection_height = std::get<3>(current_selection_dimensions);
   selection_cursor_box.set_position(current_selection_x, current_selection_y);
   selection_cursor_box.set_size(current_selection_width, current_selection_height);

   int passes = 240;
   int cursor_presses = 2;
   for (int i=0; i<passes; i++)
   {
      bool move_cursor_in_this_pass = false;
      if (i % (passes / cursor_presses) == (passes / cursor_presses) / 2) move_cursor_in_this_pass = true;

      if (move_cursor_in_this_pass)
      {
         // Move the cursor in the list
         list_box.move_cursor_down();

         // Update the cursor position in the renderer (currently only used to highlight the selected option text)
         // TODO: Consider an alternative where elements in the list can have selected states, selected, unselected,
         // selected_at, etc.
         list_box_renderer.set_cursor_position(list_box.get_cursor_position());

         // As a consequence to teh above, update the cursor selection box rendering position
         // (Build an ephemeral cursor box:)
         std::tuple<float, float, float, float> current_selection_dimensions =
            list_box_renderer.calculate_dimensions_for_list_item_at_position(list_box.get_cursor_position());
         float current_selection_x = std::get<0>(current_selection_dimensions);
         float current_selection_y = std::get<1>(current_selection_dimensions);
         float current_selection_width = std::get<2>(current_selection_dimensions);
         float current_selection_height = std::get<3>(current_selection_dimensions);
         selection_cursor_box.reposition_to(current_selection_x, current_selection_y);
         selection_cursor_box.resize_to(current_selection_width, current_selection_height);
      }

      // Update the selection_cursor_box
      selection_cursor_box.update();

      // Render the objects
      clear();
      place.start_transform();
      list_box_renderer.render();
      selection_cursor_box.render();
      place.restore_transform();
      al_flip_display();
   }
}



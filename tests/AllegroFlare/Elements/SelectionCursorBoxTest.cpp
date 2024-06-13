#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_Elements_SelectionCursorBoxTest : public ::testing::Test {};
class AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/SelectionCursorBox.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
   EXPECT_THROW_GUARD_ERROR(
      selection_cursor_box.render(),
      "AllegroFlare::Elements::SelectionCursorBox::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
   EXPECT_THROW_GUARD_ERROR(
      selection_cursor_box.render(),
      "AllegroFlare::Elements::SelectionCursorBox::render",
      "al_is_primitives_addon_initialized()"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
   selection_cursor_box.render();
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   CAPTURE__render__will_draw_the_box_as_expected)
{
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
   AllegroFlare::Placement2D showcased_placement = build_centered_placement();

   clear();
   showcased_placement.start_transform();
   selection_cursor_box.render();
   showcased_placement.restore_transform();
   al_flip_display();

   sleep_for(1);
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_position__will_set_the_position_of_the_cursor)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_position__will_set_the_position_destination_of_the_cursor)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_position__will_set_the_last_repositioned_at_to_the_time)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_position_quietly__will_set_the_position_of_the_cursor)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_position_quietly__will_set_the_position_destination_of_the_cursor)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_position_quietly__will_not_set_the_last_repositioned_at_to_the_time)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_size__will_set_the_size_of_the_cursor)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_size__will_set_the_size_destination_of_the_cursor)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_size__will_set_the_last_repositioned_at_to_the_time)
   // TODO: Update this to be a "last_resized_at"
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_size_quietly__will_set_the_size_of_the_cursor)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_size_quietly__will_set_the_size_destination_of_the_cursor)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTestWithAllegroRenderingFixture,
   set_size_quietly__will_not_set_the_last_repositioned_at_to_the_time)
   // TODO: Update this to be a "last_resized_at"
{
   // TODO
}



#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


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
   std::string expected_error_message =
      "SelectionCursorBox::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(selection_cursor_box.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_SelectionCursorBoxTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::Elements::SelectionCursorBox selection_cursor_box;
   std::string expected_error_message =
      "SelectionCursorBox::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(selection_cursor_box.render(), std::runtime_error, expected_error_message);
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



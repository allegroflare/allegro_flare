
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <allegro5/allegro_primitives.h>


class AllegroFlare_Prototypes_FixedRoom2D_CursorTest : public ::testing::Test
{};

class AllegroFlare_Prototypes_FixedRoom2D_CursorTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/FixedRoom2D/Cursor.hpp>


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_CursorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::Cursor cursor;
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_CursorTest, draw__without_a_font_bin__raises_an_error)
{
   AllegroFlare::Prototypes::FixedRoom2D::Cursor cursor;
   std::string expected_error_message =
      "Cursor::draw: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(cursor.draw(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_CursorTestWithAllegroRenderingFixture, draw__will_not_blow_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::Cursor cursor(&get_font_bin_ref());
   cursor.draw();
   SUCCEED();
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_CursorTestWithAllegroRenderingFixture,
   CAPTURE__draw__will_have_a_properly_offset_pointer_icon_that_points_to_the_cursor_x_y)
{
   AllegroFlare::Prototypes::FixedRoom2D::Cursor cursor(&get_font_bin_ref());
   cursor.clear_info_text();

   cursor.draw();
   draw_crosshair(cursor.get_x(), cursor.get_y());

   cursor.move(200, 100);

   cursor.set_cursor_to_grab();
   cursor.draw();
   draw_crosshair(cursor.get_x(), cursor.get_y());

   al_flip_display();
   sleep_for(1);
   SUCCEED();
}



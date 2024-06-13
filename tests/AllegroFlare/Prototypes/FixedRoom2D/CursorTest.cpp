
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
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
   EXPECT_THROW_GUARD_ERROR(
      cursor.draw(),
      "AllegroFlare::Prototypes::FixedRoom2D::Cursor::draw",
      "font_bin"
   );
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
   //sleep_for(1);
   SUCCEED();
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_CursorTestWithAllegroRenderingFixture,
   DISABLED__clamp__when_min_x_is_greater_than_max_x__throws_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_CursorTestWithAllegroRenderingFixture,
   DISABLED__clamp__when_min_y_is_greater_than_max_y__throws_an_exception)
{
   // TODO
}


TEST_F(AllegroFlare_Prototypes_FixedRoom2D_CursorTestWithAllegroRenderingFixture,
   clamp__will_constrain_the_x_and_y_values_to_the_ranges)
{
   AllegroFlare::Prototypes::FixedRoom2D::Cursor cursor;

   std::vector<
      std::tuple<
         std::pair<float, float>,                // initial cursor position
         std::tuple<float, float, float, float>, // min and max values
         std::pair<float, float>                 // expected cursor position after clamp
      >
   > test_datas = {
      { { 2910, 1803 },     { 0, 0, 1920, 1080 },     { 1920, 1080 } },
      { { 1920, 1080},      { 0, 0, 1920, 1080 },     { 1920, 1080 } },
      { { 800,  1200},      { 0, 0, 1920, 1080 },     {  800, 1080 } },
      { { -200, 1200},      { 0, 0, 1920, 1080 },     {    0, 1080 } },
      { { -200,   -1},      { 0, 0, 1920, 1080 },     {    0,     0} },
      { {    0,    0},      { 0, 0, 1920, 1080 },     {    0,     0} },
   };

   for (auto &test_data : test_datas)
   {
      // Collate test data
      std::pair<float, float> initial_cursor_position = std::get<0>(test_data);
      std::tuple<float, float, float, float> range_values = std::get<1>(test_data);
      std::pair<float, float> expected_cursor_position_after_clamp = std::get<2>(test_data);

      float initial_cursor_x = initial_cursor_position.first;
      float initial_cursor_y = initial_cursor_position.second;
      float min_x = std::get<0>(range_values);
      float min_y = std::get<1>(range_values);
      float max_x = std::get<2>(range_values);
      float max_y = std::get<3>(range_values);
      float expected_cursor_position_after_clamp_x = expected_cursor_position_after_clamp.first;
      float expected_cursor_position_after_clamp_y = expected_cursor_position_after_clamp.second;

      // Set the cursor position
      cursor.move_to(initial_cursor_x, initial_cursor_y);

      ASSERT_EQ(initial_cursor_x, cursor.get_x());
      ASSERT_EQ(initial_cursor_y, cursor.get_y());

      cursor.clamp(min_x, min_y, max_x, max_y);
      EXPECT_EQ(expected_cursor_position_after_clamp_x, cursor.get_x());
      EXPECT_EQ(expected_cursor_position_after_clamp_y, cursor.get_y());
   }
}



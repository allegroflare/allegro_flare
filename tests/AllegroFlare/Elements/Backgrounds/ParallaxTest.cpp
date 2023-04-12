

#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_Backgrounds_ParallaxTest : public ::testing::Test
{};

class AllegroFlare_Elements_Backgrounds_ParallaxTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Backgrounds/Parallax.hpp>


#include <cmath>


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::Parallax parallax;
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxTest, TYPE__has_the_expected_value)
{
   EXPECT_EQ("AllegroFlare/Elements/Backgrounds/Parallax", AllegroFlare::Elements::Backgrounds::Parallax::TYPE);
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::Parallax parallax_background;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::Parallax::TYPE, parallax_background.get_type());
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Backgrounds::Parallax parallax;
   std::string expected_error_message =
      "Parallax::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(parallax.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::Backgrounds::Parallax parallax;
   parallax.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_Backgrounds_ParallaxTestWithAllegroRenderingFixture,
   render__will_draw_the_background_layers_in_the_expected_positions)
{
   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   AllegroFlare::Elements::Backgrounds::Parallax parallax(
      {
         {0, 0, 0.1, bitmap_bin["backgrounds/Sky3.png"]},
         {0, 0, 0.4, bitmap_bin["backgrounds/Cloud3a.png"]},
         {0, 0, 0.8, bitmap_bin["backgrounds/Cloud3b.png"]},
      }
   );

   int passes = 60;
   for (int i=0; i<passes; i++)
   {
      // update
      parallax.set_offset_x(i * 8);
      parallax.set_offset_y(sin((float)i/passes * 6.28) * 100);

      // draw
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});
      parallax.render();
      al_flip_display();

      // flip
      sleep_for_frame();
   }

   //sleep_for(1);

   SUCCEED();
}




#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Elements/Backgrounds/IconPattern.hpp>

#ifdef _WIN32
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
#else
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
#endif

#include <AllegroFlare/Color.hpp>
#include <chrono>
#include <thread>

class AllegroFlare_Elements_Backgrounds_IconPatternTest : public ::testing::Test {};
class AllegroFlare_Elements_Backgrounds_IconPatternWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST(AllegroFlare_Elements_Backgrounds_IconPatternTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::IconPattern icon_pattern_background;
}


TEST(AllegroFlare_Elements_Backgrounds_IconPatternTest, TYPE__has_the_expected_value)
{
   std::string expected_TYPE = "AllegroFlare/Elements/Backgrounds/IconPattern";
   std::string actual_TYPE = AllegroFlare::Elements::Backgrounds::IconPattern::TYPE;
   EXPECT_EQ(expected_TYPE, actual_TYPE);
}


TEST(AllegroFlare_Elements_Backgrounds_IconPatternTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::IconPattern icon_pattern_background;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::IconPattern::TYPE, icon_pattern_background.get_type());
}


TEST_F(AllegroFlare_Elements_Backgrounds_IconPatternWithAllegroRenderingFixtureTest,
   CAPTURE__render__will_render_in_motion)
{
   get_bitmap_bin_ref().set_full_path(TEST_FIXTURE_BITMAP_FOLDER);

   AllegroFlare::Elements::Backgrounds::IconPattern icon_pattern_background(&get_font_bin_ref());
   icon_pattern_background.set_background_color(AllegroFlare::Color::Pink);

   int frames = 60*1;
   for (unsigned i=0; i<frames; i++)
   {
      //update
      icon_pattern_background.update();

      // render
      //al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      icon_pattern_background.render();
      al_flip_display();
      sleep_for_frame();
   }
}



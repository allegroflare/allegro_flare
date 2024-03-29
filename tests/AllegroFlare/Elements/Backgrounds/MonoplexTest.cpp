
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#include <AllegroFlare/Elements/Backgrounds/Monoplex.hpp>

#ifdef _WIN32
#define TEST_FIXTURE_BITMAP_FOLDER "/msys64/home/Mark/Repos/allegro_flare/bin/data/bitmaps/"
#else
#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/bin/data/bitmaps/"
#endif

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <chrono>
#include <thread>

class AllegroFlare_Elements_Backgrounds_MonoplexTest : public ::testing::Test {};
class AllegroFlare_Elements_Backgrounds_MonoplexWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST(AllegroFlare_Elements_Backgrounds_MonoplexTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::Monoplex monoplex;
}


TEST(AllegroFlare_Elements_Backgrounds_MonoplexTest, TYPE__has_the_expected_value)
{
   std::string expected_type = "AllegroFlare/Elements/Backgrounds/Monoplex";
   std::string actual_type = AllegroFlare::Elements::Backgrounds::Monoplex::TYPE;
   EXPECT_EQ(expected_type, actual_type);
}


TEST(AllegroFlare_Elements_Backgrounds_MonoplexTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::Monoplex monoplex_background;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::Monoplex::TYPE, monoplex_background.get_type());
}


TEST_F(AllegroFlare_Elements_Backgrounds_MonoplexWithAllegroRenderingFixtureTest, render__will_render_in_motion)
{
   get_bitmap_bin_ref().set_full_path(TEST_FIXTURE_BITMAP_FOLDER);

   AllegroFlare::Elements::Backgrounds::Monoplex monoplex(&get_bitmap_bin_ref());

   int frames = 60*1;
   for (unsigned i=0; i<frames; i++)
   {
      //update
      monoplex.update();

      // render
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      monoplex.render();
      al_flip_display();
      sleep_for_frame();
   }
}



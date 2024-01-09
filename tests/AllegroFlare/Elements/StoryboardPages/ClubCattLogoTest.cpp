
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/StoryboardPages/ClubCattLogo.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/RenderSurfaces/DisplayBackbuffer.hpp>


class AllegroFlare_Elements_StoryboardPages_ClubCattLogoTest : public ::testing::Test
{};

class AllegroFlare_Elements_StoryboardPages_ClubCattLogoTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Elements_StoryboardPages_ClubCattLogoTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::ClubCattLogo club_catt_logo;
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ClubCattLogoTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/StoryboardPages/ClubCattLogo",
     AllegroFlare::Elements::StoryboardPages::ClubCattLogo::TYPE
   );
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ClubCattLogoTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::StoryboardPages::ClubCattLogo club_catt_logo;
   EXPECT_EQ(AllegroFlare::Elements::StoryboardPages::ClubCattLogo::TYPE, club_catt_logo.get_type());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_ClubCattLogoTestWithAllegroRenderingFixture,
   VISUAL__will_appear_as_expected)
{
   AllegroFlare::RenderSurfaces::DisplayBackbuffer render_surface;
   render_surface.set_display(get_display()); // TODO: Not sure how this should be destroyed
   render_surface.initialize();

   AllegroFlare::ModelBin model_bin;
   model_bin.set_path(get_fixtures_path() + "models");

   AllegroFlare::Elements::StoryboardPages::ClubCattLogo clubcatt_logo_element;
   clubcatt_logo_element.set_render_surface(&render_surface);
   clubcatt_logo_element.set_bitmap_bin(&get_bitmap_bin_ref());
   clubcatt_logo_element.set_model_bin(&model_bin);
   clubcatt_logo_element.initialize();

   clubcatt_logo_element.start();

   //float number_of_seconds = 6.0f;
   //int loops = (int)(number_of_seconds * 60.0f);
   float started_at = al_get_time();
   float max_seconds_before_abort_test = 10.0f;
   bool abort = false;
   while (!(clubcatt_logo_element.get_finished()) && !abort)
   {
      float time_now = al_get_time();
      clubcatt_logo_element.update();
      clubcatt_logo_element.render();

      al_flip_display();

      float test_duration = time_now - started_at;
      if (test_duration > max_seconds_before_abort_test) abort = true;
   }

   // TODO: Improve this error message
   EXPECT_NE(true, abort) << "The test had to be automatically exited because the expected finish path did not occour.";
}



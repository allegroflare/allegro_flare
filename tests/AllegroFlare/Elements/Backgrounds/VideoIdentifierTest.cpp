
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Backgrounds/VideoIdentifier.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_Backgrounds_VideoIdentifierTest : public ::testing::Test
{};

class AllegroFlare_Elements_Backgrounds_VideoTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Elements_Backgrounds_VideoIdentifierTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::VideoIdentifier video_identifier_background;
}


TEST_F(AllegroFlare_Elements_Backgrounds_VideoIdentifierTest, TYPE__has_the_expected_value)
{
   EXPECT_EQ(
      "AllegroFlare/Elements/Backgrounds/VideoIdentifier",
      AllegroFlare::Elements::Backgrounds::VideoIdentifier::TYPE
   );
}


TEST_F(AllegroFlare_Elements_Backgrounds_VideoIdentifierTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::VideoIdentifier video_identifier_background;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::VideoIdentifier::TYPE, video_identifier_background.get_type());
}


TEST_F(AllegroFlare_Elements_Backgrounds_VideoTestWithAllegroRenderingFixture, render__will_render_the_video)
{
   // NOTE: This test is flakey. On shutdown, it appears to crash. On the several iterations that I tested it through,
   // the problem only seems to occur during shutdown, either through repeat (e.g. "--gtest_repeat=20" on one out of 3
   // or 4 runs), or through multiple dulpications of the test.  Note the problem *does not* seem to happen when a loop
   // is wrapped around the body of this test, indicating that the crash does not appear to happen as a result of
   // code within this test body.

   // After more test, the failure occurs at the *beginning* of a subsequent setup, before the first function calls
   // in the test body.

   // TODO: Fix this flakey test

   al_install_audio();
   al_reserve_samples(1);

   EXPECT_EQ(false, al_is_video_addon_initialized());
   ASSERT_EQ(true, al_init_video_addon());

   AllegroFlare::VideoBin video_bin;
   video_bin.set_full_path(get_fixtures_path() + "videos/");
   std::string video_identifier = "file_example_OGG_480_1_7mg.ogg";

   AllegroFlare::Elements::Backgrounds::VideoIdentifier video_identifier_background(&video_bin, video_identifier);
   video_identifier_background.initialize();

   video_identifier_background.activate();

   int num_frames = 30;
   for (int i=0; i<num_frames; i++)
   {
      video_identifier_background.render();
      al_flip_display();
      sleep_for_frame();
   }

   al_shutdown_video_addon();
}



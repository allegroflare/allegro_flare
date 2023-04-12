
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
   al_init_video_addon();
   AllegroFlare::VideoBin video_bin;
   video_bin.set_full_path(get_fixtures_path() + "videos/");
   std::string video_identifier = "file_example_OGG_480_1_7mg.ogg";

   AllegroFlare::Elements::Backgrounds::VideoIdentifier video_identifier_background(&video_bin, video_identifier);
   video_identifier_background.render();
   al_shutdown_video_addon();
}



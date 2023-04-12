
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
   AllegroFlare::Elements::Backgrounds::VideoIdentifier video_identifier;
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
   AllegroFlare::Elements::Backgrounds::VideoIdentifier video_identifier;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::VideoIdentifier::TYPE, video_identifier.get_type());
}



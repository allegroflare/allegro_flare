
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Backgrounds/VideoIdentifier.hpp>


TEST(AllegroFlare_Elements_Backgrounds_VideoIdentifierTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Backgrounds::VideoIdentifier video_identifier;
}


TEST(AllegroFlare_Elements_Backgrounds_VideoIdentifierTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Elements::Backgrounds::VideoIdentifier video_identifier;
   EXPECT_EQ("AllegroFlare/Elements/Backgrounds/VideoIdentifier", video_identifier.get_type());
}


TEST(AllegroFlare_Elements_Backgrounds_VideoIdentifierTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::Backgrounds::VideoIdentifier video_identifier;
   EXPECT_EQ(AllegroFlare::Elements::Backgrounds::VideoIdentifier::TYPE, video_identifier.get_type());
}



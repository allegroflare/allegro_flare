

#include <gtest/gtest.h>


#include <AllegroFlare/Version.hpp>


TEST(AllegroFlare_VersionTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Version version;
}


TEST(AllegroFlare_VersionTest, get_allegro_version_string__returns_the_expected_result)
{
   AllegroFlare::Version version;
   EXPECT_EQ("5.2.10-prerelease", version.get_allegro_version_string());
}


TEST(AllegroFlare_VersionTest, get_allegro_flare_version_string__returns_the_expected_result)
{
   AllegroFlare::Version version;
   EXPECT_EQ("0.8.11wip", version.get_allegro_flare_version_string());
}



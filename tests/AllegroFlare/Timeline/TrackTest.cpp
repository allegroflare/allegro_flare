
#include <gtest/gtest.h>

#include <AllegroFlare/Timeline/Track.hpp>


TEST(AllegroFlare_Timeline_TrackTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Timeline::Track track;
}


TEST(AllegroFlare_Timeline_TrackTest, run__returns_the_expected_response)
{
   AllegroFlare::Timeline::Track track;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, track.run());
}


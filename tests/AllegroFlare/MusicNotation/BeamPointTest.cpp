
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/BeamPoint.hpp>


TEST(AllegroFlare_MusicNotation_BeamPointTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::BeamPoint beam_point;
}


TEST(AllegroFlare_MusicNotation_BeamPointTest, run__returns_the_expected_response)
{
   AllegroFlare::MusicNotation::BeamPoint beam_point;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, beam_point.run());
}


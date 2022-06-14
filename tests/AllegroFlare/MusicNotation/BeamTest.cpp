
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/Beam.hpp>


TEST(AllegroFlare_MusicNotation_BeamTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::Beam beam;
}


TEST(AllegroFlare_MusicNotation_BeamTest, run__returns_the_expected_response)
{
   AllegroFlare::MusicNotation::Beam beam;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, beam.run());
}


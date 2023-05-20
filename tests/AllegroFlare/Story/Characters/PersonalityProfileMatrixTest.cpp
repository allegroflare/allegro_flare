
#include <gtest/gtest.h>

#include <AllegroFlare/Story/Characters/PersonalityProfileMatrix.hpp>


TEST(AllegroFlare_Story_Characters_PersonalityProfileMatrixTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Story::Characters::PersonalityProfileMatrix personality_profile_matrix;
}


TEST(AllegroFlare_Story_Characters_PersonalityProfileMatrixTest, run__returns_the_expected_response)
{
   AllegroFlare::Story::Characters::PersonalityProfileMatrix personality_profile_matrix;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, personality_profile_matrix.run());
}




#include <gtest/gtest.h>

#include <AllegroFlare/Story/Characters/PersonalityProfileDimension.hpp>


TEST(AllegroFlare_Story_Characters_PersonalityProfileDimensionTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Story::Characters::PersonalityProfileDimension personality_profile_dimension;
}


TEST(AllegroFlare_Story_Characters_PersonalityProfileDimensionTest,
   get_scoring_normalized__returns_the_score_on_this_dimension_normalized)
{
   AllegroFlare::Story::Characters::PersonalityProfileDimension personality_profile_dimension;
   personality_profile_dimension.set_scoring(5);
   personality_profile_dimension.set_scoring_max(8);
   EXPECT_EQ(0.625, personality_profile_dimension.get_scoring_normalized());
}



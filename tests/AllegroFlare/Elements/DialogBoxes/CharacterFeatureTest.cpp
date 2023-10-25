
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/CharacterFeature.hpp>


TEST(AllegroFlare_Elements_DialogBoxes_CharacterFeatureTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::CharacterFeature character_feature;
}


TEST(AllegroFlare_Elements_DialogBoxes_CharacterFeatureTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/DialogBoxes/CharacterFeature",
     AllegroFlare::Elements::DialogBoxes::CharacterFeature::TYPE
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_CharacterFeatureTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::DialogBoxes::CharacterFeature character_feature;
   EXPECT_EQ(AllegroFlare::Elements::DialogBoxes::CharacterFeature::TYPE, character_feature.get_type());
}




#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/BasicCentered.hpp>


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_BasicCenteredTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered basic_centered;
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_BasicCenteredTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/CharacterStagingLayouts/BasicCentered",
     AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_BasicCenteredTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered basic_centered;
   EXPECT_EQ(AllegroFlare::DialogSystem::CharacterStagingLayouts::BasicCentered::TYPE, basic_centered.get_type());
}



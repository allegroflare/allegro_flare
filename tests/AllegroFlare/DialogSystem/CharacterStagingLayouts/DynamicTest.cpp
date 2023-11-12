
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Dynamic.hpp>


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic dynamic;
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/CharacterStagingLayouts/Dynamic",
     AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic dynamic;
   EXPECT_EQ(AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::TYPE, dynamic.get_type());
}



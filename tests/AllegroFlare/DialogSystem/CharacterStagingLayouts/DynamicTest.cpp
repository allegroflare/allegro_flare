
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
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging;
   EXPECT_EQ(AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::TYPE, staging.get_type());
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest,
   add_staged_characer__will_add_the_character_to_the_staging)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging;
   staging.add_staged_character(
      "HUGO",
      {
         "hugo.png",
         AllegroFlare::Placement3D(0, 0, 0)
      }
   );
   ASSERT_EQ(1, staging.num_staged_characters());
   EXPECT_EQ(true, staging.staged_character_exists("HUGO"));
}



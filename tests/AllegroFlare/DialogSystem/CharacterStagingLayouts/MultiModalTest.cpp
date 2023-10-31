
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/MultiModal.hpp>


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_MultiModalTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal multi_modal;
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_MultiModalTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/CharacterStagingLayouts/MultiModal",
     AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_CharacterStagingLayouts_MultiModalTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal multi_modal;
   EXPECT_EQ(AllegroFlare::DialogSystem::CharacterStagingLayouts::MultiModal::TYPE, multi_modal.get_type());
}



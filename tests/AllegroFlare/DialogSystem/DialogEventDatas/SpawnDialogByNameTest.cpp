
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/DialogEventDatas/SpawnDialogByName.hpp>


TEST(AllegroFlare_DialogSystem_DialogEventDatas_SpawnDialogByNameTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::DialogEventDatas::SpawnDialogByName spawn_dialog_by_name;
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_SpawnDialogByNameTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/DialogEventDatas/SpawnDialogByName",
     AllegroFlare::DialogSystem::DialogEventDatas::SpawnDialogByName::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_SpawnDialogByNameTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::DialogEventDatas::SpawnDialogByName spawn_dialog_by_name;
   EXPECT_EQ(AllegroFlare::DialogSystem::DialogEventDatas::SpawnDialogByName::TYPE, spawn_dialog_by_name.get_type());
}



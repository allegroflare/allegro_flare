
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogYAMLFile.hpp>


TEST(AllegroFlare_DialogSystem_DialogEventDatas_LoadDialogYAMLFileTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogYAMLFile load_dialog_yamlfile;
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_LoadDialogYAMLFileTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogYAMLFile",
     AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogYAMLFile::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_LoadDialogYAMLFileTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogYAMLFile load_dialog_yamlfile;
   EXPECT_EQ(AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogYAMLFile::TYPE, load_dialog_yamlfile.get_type());
}



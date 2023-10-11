
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogNodeBankFromFile.hpp>


TEST(AllegroFlare_DialogSystem_DialogEventDatas_LoadDialogNodeBankFromFileTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogNodeBankFromFile load_dialog_yamlfile;
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_LoadDialogNodeBankFromFileTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/DialogEventDatas/LoadDialogNodeBankFromFile",
     AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogNodeBankFromFile::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_LoadDialogNodeBankFromFileTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogNodeBankFromFile load_dialog_yamlfile;
   EXPECT_EQ(AllegroFlare::DialogSystem::DialogEventDatas::LoadDialogNodeBankFromFile::TYPE, load_dialog_yamlfile.get_type());
}



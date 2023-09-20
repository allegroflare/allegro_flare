
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotEvidenceDialog.hpp>


TEST(AllegroFlare_DialogSystem_DialogEventDatas_CreateYouGotEvidenceDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotEvidenceDialog create_you_got_evidence_dialog;
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_CreateYouGotEvidenceDialogTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/DialogEventDatas/CreateYouGotEvidenceDialog",
     AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotEvidenceDialog::TYPE
   );
}


TEST(AllegroFlare_DialogSystem_DialogEventDatas_CreateYouGotEvidenceDialogTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotEvidenceDialog create_you_got_evidence_dialog;
   EXPECT_EQ(AllegroFlare::DialogSystem::DialogEventDatas::CreateYouGotEvidenceDialog::TYPE, create_you_got_evidence_dialog.get_type());
}




#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/DialogEventDatas/CreateYouGotEvidenceDialog.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_DialogEventDatas_CreateYouGotEvidenceDialogTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotEvidenceDialog create_you_got_evidence_dialog;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_DialogEventDatas_CreateYouGotEvidenceDialogTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotEvidenceDialog create_you_got_evidence_dialog;
   EXPECT_EQ("DialogEventDatas/CreateYouGotEvidenceDialog", create_you_got_evidence_dialog.get_type());
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_DialogEventDatas_CreateYouGotEvidenceDialogTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotEvidenceDialog create_you_got_evidence_dialog;
   EXPECT_EQ(AllegroFlare::Prototypes::FixedRoom2D::DialogEventDatas::CreateYouGotEvidenceDialog::TYPE, create_you_got_evidence_dialog.get_type());
}



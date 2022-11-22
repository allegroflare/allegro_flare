
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/YouGotEvidence.hpp>


TEST(AllegroFlare_Elements_DialogBoxes_YouGotEvidenceTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::YouGotEvidence you_got_evidence;
}


TEST(AllegroFlare_Elements_DialogBoxes_YouGotEvidenceTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Elements::DialogBoxes::YouGotEvidence you_got_evidence;
   EXPECT_EQ("DialogBoxes/YouGotEvidence", you_got_evidence.get_type());
}


TEST(AllegroFlare_Elements_DialogBoxes_YouGotEvidenceTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::DialogBoxes::YouGotEvidence you_got_evidence;
   EXPECT_EQ(AllegroFlare::Elements::DialogBoxes::YouGotEvidence::TYPE, you_got_evidence.get_type());
}



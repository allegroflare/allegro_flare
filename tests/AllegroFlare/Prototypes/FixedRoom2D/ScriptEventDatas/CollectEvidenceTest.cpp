
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectEvidence.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_CollectEvidenceTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectEvidence collect_evidence;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_CollectEvidenceTest, has_the_expected_type)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectEvidence collect_evidence;
   EXPECT_EQ("CollectEvidence", collect_evidence.get_type());
}


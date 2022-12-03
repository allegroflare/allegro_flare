
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptEventDatas/CollectItem.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_CollectItemTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectItem collect_item;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_ScriptEventDatas_CollectItemTest, has_the_expected_type)
{
   AllegroFlare::Prototypes::FixedRoom2D::ScriptEventDatas::CollectItem collect_item;
   EXPECT_EQ("ScriptEventDatas/CollectItem", collect_item.get_type());
}



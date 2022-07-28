
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/CollectItemEventData.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_CollectItemEventDataTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::CollectItemEventData collect_item_event_data;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_CollectItemEventDataTest, has_the_expected_type)
{
   AllegroFlare::Prototypes::FixedRoom2D::CollectItemEventData collect_item_event_data;
   EXPECT_EQ("CollectItemEventData", collect_item_event_data.get_type());
}




#include <gtest/gtest.h>

#include <AllegroFlare/GameEventDatas/VirtualControllerAxisChangeEventData.hpp>


TEST(AllegroFlare_GameEventDatas_VirtualControllerAxisChangeEventDataTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameEventDatas::VirtualControllerAxisChangeEventData virtual_controller_axis_change_event_data;
}


TEST(AllegroFlare_GameEventDatas_VirtualControllerAxisChangeEventDataTest, TYPE__has_the_expected_value)
{
   AllegroFlare::GameEventDatas::VirtualControllerAxisChangeEventData virtual_controller_axis_change_event_data;
   EXPECT_EQ("AllegroFlare/GameEventDatas/VirtualControllerAxisChangeEventData", virtual_controller_axis_change_event_data.get_type());
}


TEST(AllegroFlare_GameEventDatas_VirtualControllerAxisChangeEventDataTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameEventDatas::VirtualControllerAxisChangeEventData virtual_controller_axis_change_event_data;
   EXPECT_EQ(AllegroFlare::GameEventDatas::VirtualControllerAxisChangeEventData::TYPE, virtual_controller_axis_change_event_data.get_type());
}



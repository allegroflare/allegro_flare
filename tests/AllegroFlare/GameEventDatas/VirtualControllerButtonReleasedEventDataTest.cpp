
#include <gtest/gtest.h>

#include <AllegroFlare/GameEventDatas/VirtualControllerButtonReleasedEventData.hpp>


TEST(AllegroFlare_GameEventDatas_VirtualControllerButtonReleasedEventDataTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData virtual_controller_button_released_event_data;
}


TEST(AllegroFlare_GameEventDatas_VirtualControllerButtonReleasedEventDataTest, TYPE__has_the_expected_value)
{
   AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData virtual_controller_button_released_event_data;
   EXPECT_EQ(
      "AllegroFlare/GameEventDatas/VirtualControllerButtonReleasedEventData",
      virtual_controller_button_released_event_data.get_type()
   );
}


TEST(AllegroFlare_GameEventDatas_VirtualControllerButtonReleasedEventDataTest,
   type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData virtual_controller_button_released_event_data;
   EXPECT_EQ(
      AllegroFlare::GameEventDatas::VirtualControllerButtonReleasedEventData::TYPE,
      virtual_controller_button_released_event_data.get_type()
   );
}



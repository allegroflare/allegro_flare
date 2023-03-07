
#include <gtest/gtest.h>

#include <AllegroFlare/GameEventDatas/VirtualControllerButtonPressedEventData.hpp>


TEST(AllegroFlare_GameEventDatas_VirtualControllerButtonPressedEventDataTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData virtual_controller_button_pressed_event_data;
}


TEST(AllegroFlare_GameEventDatas_VirtualControllerButtonPressedEventDataTest, TYPE__has_the_expected_value)
{
   AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData virtual_controller_button_pressed_event_data;
   EXPECT_EQ("AllegroFlare/GameEventDatas/VirtualControllerButtonPressedEventData", virtual_controller_button_pressed_event_data.get_type());
}


TEST(AllegroFlare_GameEventDatas_VirtualControllerButtonPressedEventDataTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData virtual_controller_button_pressed_event_data;
   EXPECT_EQ(AllegroFlare::GameEventDatas::VirtualControllerButtonPressedEventData::TYPE, virtual_controller_button_pressed_event_data.get_type());
}



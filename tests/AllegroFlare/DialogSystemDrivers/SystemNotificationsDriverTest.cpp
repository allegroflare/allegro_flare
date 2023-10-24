
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystemDrivers/SystemNotificationsDriver.hpp>


TEST(AllegroFlare_DialogSystemDrivers_SystemNotificationsDriverTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver system_notifications_driver;
}


TEST(AllegroFlare_DialogSystemDrivers_SystemNotificationsDriverTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystemDrivers/SystemNotificationsDriver",
     AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver::TYPE
   );
}


TEST(AllegroFlare_DialogSystemDrivers_SystemNotificationsDriverTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver system_notifications_driver;
   EXPECT_EQ(AllegroFlare::DialogSystemDrivers::SystemNotificationsDriver::TYPE, system_notifications_driver.get_type());
}




#include <gtest/gtest.h>

#include <AllegroFlare/Notifications.hpp>


class NotificationTestClass : public AllegroFlare::Elements::Notifications::Base
{
private:
   static int destroyed_count;
public:
   NotificationTestClass() : AllegroFlare::Elements::Notifications::Base("NotificationTestClass") {}
   ~NotificationTestClass() { destroyed_count++; }
   static int get_destroyed_count() { return destroyed_count; }
};
int NotificationTestClass::destroyed_count = 0;


TEST(AllegroFlare_NotificationsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Notifications notifications;
}


TEST(AllegroFlare_NotificationsTest, add__will_add_a_notification_to_the_list)
{
   AllegroFlare::Notifications notifications;
   notifications.add(new NotificationTestClass());
   EXPECT_EQ(1, notifications.size());
   notifications.add(new NotificationTestClass());
   EXPECT_EQ(2, notifications.size());
}


TEST(AllegroFlare_NotificationsTest, destroy_all__will_destroy_the_notifications_and_clear_the_list)
{
   AllegroFlare::Notifications notifications({
      new NotificationTestClass(),
      new NotificationTestClass(),
      new NotificationTestClass(),
   });

   int previous_destroyed_count = NotificationTestClass::get_destroyed_count();
   notifications.destroy_all();
   int subsequent_destroyed_count = NotificationTestClass::get_destroyed_count();
   int num_destroyed_records = subsequent_destroyed_count - previous_destroyed_count;
   EXPECT_EQ(3, num_destroyed_records);
}




#include <gtest/gtest.h>

#include <AllegroFlare/Elements/Notifications/Base.hpp>


class NotificationsBaseTestClass : public AllegroFlare::Elements::Notifications::Base
{
public:
   NotificationsBaseTestClass()
      : AllegroFlare::Elements::Notifications::Base("NotificationsBaseTestClass")
   {}
};


TEST(AllegroFlare_Elements_Notifications_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Notifications::Base base;
}


TEST(AllegroFlare_Elements_Notifications_BaseTest, has_the_expected_type)
{
   AllegroFlare::Elements::Notifications::Base base;
   EXPECT_EQ("Base", base.get_type());
}


TEST(AllegroFlare_Elements_Notifications_BaseTest, derived_classes_will_have_the_expected_type)
{
   NotificationsBaseTestClass test_class;
   EXPECT_EQ("NotificationsBaseTestClass", test_class.get_type());
}



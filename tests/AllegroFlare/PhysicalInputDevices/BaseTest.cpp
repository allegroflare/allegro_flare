
#include <gtest/gtest.h>

#include <AllegroFlare/PhysicalInputDevices/Base.hpp>


class PhysicalInputDeviceBaseTestClass : public AllegroFlare::PhysicalInputDevices::Base
{
public:
   PhysicalInputDeviceBaseTestClass()
      : AllegroFlare::PhysicalInputDevices::Base("PhysicalInputDeviceBaseTestClass")
   {}
};


TEST(AllegroFlare_PhysicalInputDevices_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PhysicalInputDevices::Base base;
}


TEST(AllegroFlare_PhysicalInputDevices_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::PhysicalInputDevices::Base base;
   EXPECT_EQ("PhysicalInputDevice/Base", base.get_type());
}


TEST(AllegroFlare_PhysicalInputDevices_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::PhysicalInputDevices::Base base;
   EXPECT_EQ(AllegroFlare::PhysicalInputDevices::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_PhysicalInputDevices_BaseTest, derived_classes_will_have_the_expected_type)
{
   PhysicalInputDeviceBaseTestClass test_class;
   EXPECT_EQ("PhysicalInputDeviceBaseTestClass", test_class.get_type());
}



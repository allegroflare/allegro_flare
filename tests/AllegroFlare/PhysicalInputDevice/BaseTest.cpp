
#include <gtest/gtest.h>

#include <AllegroFlare/PhysicalInputDevice/Base.hpp>


class PhysicalInputDeviceBaseTestClass : public AllegroFlare::PhysicalInputDevice::Base
{
public:
   PhysicalInputDeviceBaseTestClass()
      : AllegroFlare::PhysicalInputDevice::Base("PhysicalInputDeviceBaseTestClass")
   {}
};


TEST(AllegroFlare_PhysicalInputDevice_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PhysicalInputDevice::Base base;
}


TEST(AllegroFlare_PhysicalInputDevice_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::PhysicalInputDevice::Base base;
   EXPECT_EQ("PhysicalInputDevice/Base", base.get_type());
}


TEST(AllegroFlare_PhysicalInputDevice_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::PhysicalInputDevice::Base base;
   EXPECT_EQ(AllegroFlare::PhysicalInputDevice::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_PhysicalInputDevice_BaseTest, derived_classes_will_have_the_expected_type)
{
   PhysicalInputDeviceBaseTestClass test_class;
   EXPECT_EQ("PhysicalInputDeviceBaseTestClass", test_class.get_type());
}



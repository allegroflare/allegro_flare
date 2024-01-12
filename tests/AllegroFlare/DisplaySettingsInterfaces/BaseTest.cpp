
#include <gtest/gtest.h>

#include <AllegroFlare/DisplaySettingsInterfaces/Base.hpp>


class DisplaySettingsInterfacesBaseTestClass : public AllegroFlare::DisplaySettingsInterfaces::Base
{
public:
   DisplaySettingsInterfacesBaseTestClass()
      : AllegroFlare::DisplaySettingsInterfaces::Base("DisplaySettingsInterfacesBaseTestClass")
   {}
};


TEST(AllegroFlare_DisplaySettingsInterfaces_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DisplaySettingsInterfaces::Base base;
}


TEST(AllegroFlare_DisplaySettingsInterfaces_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DisplaySettingsInterfaces/Base",
     AllegroFlare::DisplaySettingsInterfaces::Base::TYPE
   );
}


TEST(AllegroFlare_DisplaySettingsInterfaces_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DisplaySettingsInterfaces::Base base;
   EXPECT_EQ(AllegroFlare::DisplaySettingsInterfaces::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_DisplaySettingsInterfaces_BaseTest, derived_classes_will_have_the_expected_type)
{
   DisplaySettingsInterfacesBaseTestClass test_class;
   EXPECT_EQ("DisplaySettingsInterfacesBaseTestClass", test_class.get_type());
}



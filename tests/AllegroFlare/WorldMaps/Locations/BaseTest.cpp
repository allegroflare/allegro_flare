
#include <gtest/gtest.h>

#include <AllegroFlare/WorldMaps/Locations/Base.hpp>


class LocationsBaseTestClass : public AllegroFlare::WorldMaps::Locations::Base
{
public:
   LocationsBaseTestClass()
      : AllegroFlare::WorldMaps::Locations::Base("LocationsBaseTestClass")
   {}
};


TEST(AllegroFlare_WorldMaps_Locations_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::WorldMaps::Locations::Base base;
}


TEST(AllegroFlare_WorldMaps_Locations_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/WorldMaps/Locations/Base",
     AllegroFlare::WorldMaps::Locations::Base::TYPE
   );
}


TEST(AllegroFlare_WorldMaps_Locations_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::WorldMaps::Locations::Base base;
   EXPECT_EQ(AllegroFlare::WorldMaps::Locations::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_WorldMaps_Locations_BaseTest, derived_classes_will_have_the_expected_type)
{
   LocationsBaseTestClass test_class;
   EXPECT_EQ("LocationsBaseTestClass", test_class.get_type());
}


